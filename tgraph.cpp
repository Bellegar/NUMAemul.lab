#include "tgraph.h"
#include <QDebug>

using namespace ogdf;
bool static sortFunc(const QVector<double> &v1, const QVector<double> &v2);

TGraph::TGraph()
{

}

TGraph::TGraph(ogdf::energybased::dtree::GalaxyLevel Gw,int index, bool isLM, int q)
{
    GLocal = Gw.graph();
    for (int i = 0; i < GLocal.numberOfNodes(); i++)
        NodeVect.push_back(TNode(Gw,this,i));
    GraphNumber = index + 1;
    MinTime = 0;
    MaxTime = 0;
    CritWays.clear();
    //IsLocalMem = false;
    IsLocalMem = isLM;
    QKoef = q;
    for (int i = 0; i < NodeVect.count(); i++)
    {
        for (int j = 0; j < NodeVect[i].getSuccNodes().count(); j++)
        {
            if (NodeVect[i].getSuccNodes()[j].DestNodeNum <= NodeVect[i].getNodeNumber())
            {
                Err = 1;
                return;
            }

        }
    }
    //setCritWays();
    fixFromBig();

}

int TGraph::getNodeCount() const
{
    return NodeVect.count();
}

TNode* TGraph::getNode(int number)
{
    return &NodeVect[number-1];
}

int TGraph::getGraphNumber() const
{
    return GraphNumber;
}

double TGraph::getMinTime() const
{
    return MinTime;
}

double TGraph::getMaxTime() const
{
    double Max = 0;
    for (TNode nd : NodeVect)
    {
        if (!IsLocalMem)
            Max += nd.getNodeTime();
        else
            Max += nd.getNodeTime() + (nd.getOutWeights()*1.0 / QKoef) * 2;
    }
    return Max;
}

QVector<QVector<TNode*>> TGraph::getCritWays()
{
    return CritWays;
}

void TGraph::setCritWays()
{
    DownTMinTimes();
    UpTMaxTimes();
    QVector<TNode*> CritOne;
    int Wi = 0;
    bool FullCrits = false;
    TNode* lastN;
    CritWays.clear();
    CritOne.push_back(&NodeVect[0]);
    CritWays.push_back(CritOne);
    QVector<TNode*> tempVN;

    do
    {
        FullCrits = true;
        while (CritWays[Wi].last()->isFinal() != true)
        {
            FullCrits = false;
            lastN = CritWays[Wi].last();
            QVectorIterator<TNodeEdge> i(lastN->getSuccNodes());
            tempVN = CritWays.takeAt(Wi);

            while (i.hasNext())
            {
                int dnum = i.next().DestNodeNum;
                if (!IsLocalMem)
                {
                    if (NodeVect[dnum-1].getTMin() == NodeVect[dnum-1].getTMax())
                        if (NodeVect[dnum-1].getTMin() == lastN->getTMin() + lastN->getNodeTime() +
                                lastN->getSuccEdgeWeight(dnum))
                        {
                            CritWays.push_back(tempVN);
                            CritWays.last().push_back(&NodeVect[dnum-1]);
                        }
                }
                else
                {
                    if (abs(NodeVect[dnum-1].getTMin() - NodeVect[dnum-1].getTMax())
                            < std::numeric_limits<double>::epsilon() * round(NodeVect[dnum-1].getTMin()) * 1000)
                        if (abs(NodeVect[dnum-1].getTMin() - (lastN->getTMin() + lastN->getNodeTime() + lastN->getSuccEdgeWeight(dnum)
                                                              + round(((lastN->getOutWeights()*1.0)/QKoef) * 1000)/1000
                                                              + round(((NodeVect[dnum-1].getInWeights()*1.0)/QKoef) * 1000)/1000))
                                < std::numeric_limits<double>::epsilon() * round(NodeVect[dnum-1].getTMin()) * 1000)
                        {

                            CritWays.push_back(tempVN);
                            CritWays.last().push_back(&NodeVect[dnum-1]);
                        }
                }
            }
        }
        Wi++;

    }
    while (Wi < CritWays.count());

}

void TGraph::fixFromBig()
{
    setCritWays();
    QVector<QVector<double>> Weights;
    QVector<double> tempW;
    QVector<double>::Iterator  WintIter;
    double Wint;
    QVector<double> Wints;
    int Wmaxind;
    bool pushed;
    do
    {

        Weights.clear();
        Wints.clear();

        for (int i = 0; i < CritWays.count(); i++)
        {
            tempW.clear();
            for (int j = 0; j < CritWays[i].count()-1; j++)
                tempW.push_back(CritWays[i][j]->getSuccEdgeWeight(CritWays[i][j+1]->getNodeNumber()));
            Weights.push_back(tempW);
        }

        for (int i = 0; i < CritWays.count(); i++)
        {
            pushed = false;
            do
            {
                WintIter = std::max_element(Weights[i].begin(),Weights[i].end());
                Wint = *WintIter;
                if (Wint != 0)
                {
                    Wmaxind = Weights[i].indexOf(Wint);
                    if (!(CritWays[i][Wmaxind]->hasSuccFix()) && !(CritWays[i][Wmaxind+1]->hasPredFix()))
                    {
                        Wints.push_back(Wint);
                        pushed = true;
                    }
                    else
                        Weights[i][Wmaxind] = 0;
                }
                else
                    Wints.push_back(0);
                //                qDebug() << i << Wmaxind << Wint << " Wint";
            } while ((pushed == false) && (Wint != 0));
            //            qDebug() << "stop search in critway";

        }

        WintIter = std::max_element(Wints.begin(),Wints.end());
        Wint = *WintIter;
        if (Wint != 0)
        {
            int WindWay = Wints.indexOf(Wint);
            int Wind = Weights[WindWay].indexOf(Wint);
            //qDebug() << CritWays[WindWay][Wind]->getNodeNumber() << CritWays[WindWay][Wind+1]->getNodeNumber() << " zero-ed";


            setFixNode(CritWays[WindWay][Wind]->getNodeNumber(),CritWays[WindWay][Wind+1]->getNodeNumber());
        }

        setCritWays();
    } while (Wint != 0);
    //qDebug() << "CritWays Zeroed";
    fixBigByAll();
}

bool static sortFunc(const QVector<double> &v1, const QVector<double> &v2)
{
    return v1.last() > v2.last();
}

void TGraph::fixBigByAll()
{
    QVector<QVector<double>> Weights;
    QVector<double> tempW;
    TNode tempNSu;
    TNodeEdge tempNPr;
    do
    {
        Weights.clear();
        QVectorIterator<TNode> iN(NodeVect);
        while (iN.hasNext())
        {
            tempNSu = iN.next();
            if (!(tempNSu.hasSuccFix()))
            {
                QVectorIterator<TNodeEdge> iS(tempNSu.getSuccNodes());
                while (iS.hasNext())
                {
                    tempNPr = iS.next();
                    tempW.clear();
                    if (!(NodeVect.at(tempNPr.DestNodeNum-1).hasPredFix()))
                    {
                        tempW << tempNSu.getNodeNumber() << tempNPr.DestNodeNum << tempNPr.EWeight;
                        Weights << tempW;
                    }
                }

            }

        }

        qSort(Weights.begin(),Weights.end(),sortFunc);
        if (!Weights.isEmpty())
        {
            setFixNode(Weights[0][0],Weights[0][1]);
            //qDebug() << Weights[0][0] << Weights[0][1] << "after Crit zero-ed";
        }
        setCritWays();

    } while (!Weights.isEmpty());
    //qDebug() << "All Zeroed";
}

QVector<QVector<int> > TGraph::getFixedPair()
{
    return FixedPair;
}

void TGraph::DownTMinTimes()
{

    Graph G = GLocal;
    NodeArray<int> shortestPathMatrix(G);
    NodeArray<edge> shortestEdges(G);
    EdgeArray<int> edgesAr(G);
    int sourceNInd;
    int targetNInd;
    //    qDebug() << "edgesAr";
    if (!IsLocalMem)
        for (edge e : G.edges)
        {
            sourceNInd = e->source()->index();
            targetNInd = e->target()->index();
            edgesAr[e] = -(NodeVect[sourceNInd].getNodeTime() + NodeVect[sourceNInd].getSuccEdgeWeight(targetNInd+1));
        }
    else
        for (edge e : G.edges)
        {
            sourceNInd = e->source()->index();
            targetNInd = e->target()->index();
            edgesAr[e] = -(NodeVect[sourceNInd].getNodeTime() + NodeVect[sourceNInd].getSuccEdgeWeight(targetNInd+1))
                    * 1000 - int(round(((NodeVect[sourceNInd].getOutWeights()*1.0)/QKoef) * 1000))
                    - int(round(((NodeVect[targetNInd].getInWeights()*1.0)/QKoef) * 1000));
            //            qDebug() << edgesAr[e];
        }

    ShortestPathWithBFM().call(G,G.firstNode(),edgesAr,shortestPathMatrix,shortestEdges);
    for (int i = 0; i< G.numberOfNodes(); i++)
        if (!IsLocalMem)
            NodeVect[i].setTMin(-shortestPathMatrix[i]);
        else
            NodeVect[i].setTMin(-shortestPathMatrix[i]/1000.0);

    if (!IsLocalMem)
        MinTime = -shortestPathMatrix[G.numberOfNodes()-1] + NodeVect.last().getNodeTime();
    else
        MinTime = -shortestPathMatrix[G.numberOfNodes()-1]/1000.0 + NodeVect.last().getNodeTime();

}

void TGraph::UpTMaxTimes()
{
    Graph GBack = GLocal;
    for (edge e : GBack.edges)
        GBack.reverseEdge(e);
    NodeArray<int> shortestPathMatrixBack(GBack);
    NodeArray<edge> shortestEdgesBack(GBack);
    EdgeArray<int> edgesArBack(GBack);
    int sourceNInd;
    int targetNInd;
    //    qDebug() << "edgesArBack";
    if (!IsLocalMem)
        for (edge e : GBack.edges)
        {
            sourceNInd = e->source()->index();
            targetNInd = e->target()->index();
            edgesArBack[e] = -(NodeVect[targetNInd].getNodeTime() + NodeVect[targetNInd].getSuccEdgeWeight(sourceNInd+1));
        }
    else
        for (edge e : GBack.edges)
        {
            sourceNInd = e->source()->index();
            targetNInd = e->target()->index();
            edgesArBack[e] = -(NodeVect[targetNInd].getNodeTime() + NodeVect[targetNInd].getSuccEdgeWeight(sourceNInd+1))
                    * 1000 - int(round(((NodeVect[targetNInd].getOutWeights()*1.0)/QKoef) * 1000))
                    - int(round(((NodeVect[sourceNInd].getInWeights()*1.0)/QKoef) * 1000));
            //            qDebug() << edgesArBack[e];
        }
    ShortestPathWithBFM().call(GBack,GBack.lastNode(),edgesArBack,shortestPathMatrixBack,shortestEdgesBack);
    for (int i = 0; i< GBack.numberOfNodes(); i++)
        if (!IsLocalMem)
            NodeVect[i].setTMax(NodeVect.last().getTMin() + shortestPathMatrixBack[i]);
        else
            NodeVect[i].setTMax(NodeVect.last().getTMin() + shortestPathMatrixBack[i]/1000.0);

}

void TGraph::setFixNode(int currNum, int targNum)
{
    NodeVect[currNum-1].setSuccFixNodeNum(targNum);
    NodeVect[targNum-1].setPredFixNodeNum(currNum);
    QVector<int> tmp;
    tmp << currNum << targNum;
    FixedPair << tmp;

}

void TGraph::setIsLocalMem(bool LocalMemFlag)
{
    IsLocalMem = LocalMemFlag;
}

void TGraph::setQKoef(int q)
{
    QKoef = q;
}

NStat TGraph::calcPredStatusNode(int nodeNum) const
{
    QVector<NStat> predStatVect;
    for (TNodeEdge predN : NodeVect[nodeNum-1].getPredNodes())
    {
        predStatVect << NodeVect[predN.DestNodeNum-1].getStatusNode();
    }
    if (predStatVect.count(Completed) == predStatVect.count())
        return Ready;
    else
        return NotReady;
}

int TGraph::getErr()
{
    return Err;
}
