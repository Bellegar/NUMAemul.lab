#include "tnode.h"
using namespace ogdf;

TNode::TNode()
{

}

TNode::TNode(ogdf::energybased::dtree::GalaxyLevel Gw, TGraph* myGraph, int index)
{
    NodeNumber = index + 1;
    //GraphNumber = myGraph + 1;
    MyTGraph = myGraph;
    node v = Gw.graph().firstNode();
    for (int i = 0;i < index;i++)
        v = v->succ();
    NodeTime = int(Gw.weight(v));
    edge e;
    TNodeEdge destNE;
    List<edge> elist;

    int inW = 0;
    v->inEdges(elist);
    int Ecount = elist.size();
    for (int i = 0; i < Ecount; i++)
    {
        e = elist.popBackRet();
        destNE.DestNodeNum = e->source()->index()+1;
        destNE.EWeight = int(Gw.edgeWeight(e));
        inW += destNE.EWeight;
        PredNodes.push_front(destNE);
    }

    int outW = 0;
    v->outEdges(elist);
    Ecount = elist.size();
    for (int i = 0; i < Ecount; i++)
    {
        e = elist.popBackRet();
        destNE.DestNodeNum = e->target()->index()+1;
        destNE.EWeight = int(Gw.edgeWeight(e));
        outW += destNE.EWeight;
        SuccNodes.push_front(destNE);
    }

    StatusNode = NotReady;
    PredFixNodeNum = NodeNumber;
    SuccFixNodeNum = NodeNumber;
    TMin = 0;
    TMax = 0;
    InWeights = inW;
    OutWeights = outW;
}

int TNode::getNodeNumber() const
{
    return NodeNumber;
}

int TNode::getNodeTime() const
{
    return NodeTime;
}

QVector<TNodeEdge> TNode::getPredNodes() const
{
    return PredNodes;
}

QVector<TNodeEdge> TNode::getSuccNodes() const
{
    return SuccNodes;
}

int TNode::getInWeights() const
{
    return InWeights;
}

int TNode::getOutWeights() const
{
    return OutWeights;
}

int TNode::getSuccEdgeWeight(int nodeNum) const
{
    QVectorIterator<TNodeEdge> i(SuccNodes);
    TNodeEdge ine;

    while (i.hasNext())
    {
        ine = i.next();
        if (ine.DestNodeNum == nodeNum)
            return ine.EWeight;
    }
    return 100000;
}

NStat TNode::getStatusNode() const
{
    return StatusNode;
}

void TNode::setStatusNode(NStat statOfNode)
{
    StatusNode = statOfNode;
}

TProc* TNode::getExecTProc() const
{
    return ExecTProc;
}

void TNode::setExecTProc(TProc* execProc)
{
    ExecTProc = execProc;
}

int TNode::getPredFixNodeNum() const
{
    return PredFixNodeNum;
}

void TNode::setPredFixNodeNum(int predFix)
{
    PredFixNodeNum = predFix;
    QMutableVectorIterator<TNodeEdge> i(PredNodes);
    while (i.hasNext())
    {
        if (i.next().DestNodeNum == predFix)
            i.setValue({predFix,0});
    }

}

int TNode::getSuccFixNodeNum() const
{
    return SuccFixNodeNum;
}

void TNode::setSuccFixNodeNum(int succFix)
{
    SuccFixNodeNum = succFix;
    QMutableVectorIterator<TNodeEdge> i(SuccNodes);
    while (i.hasNext())
    {
        if (i.next().DestNodeNum == succFix)
            i.setValue({succFix,0});
    }

}

bool TNode::isFinal() const
{
    return (SuccNodes.count() == 0) ? true : false;
}

bool TNode::hasPredFix() const
{
    return PredFixNodeNum != NodeNumber;
}

bool TNode::hasSuccFix() const
{
    return SuccFixNodeNum != NodeNumber;
}

double TNode::getTMin() const
{
    return TMin;
}

void TNode::setTMin(double tMin)
{
    TMin = tMin;
}

double TNode::getTMax() const
{
    return TMax;
}

void TNode::setTMax(double tMax)
{
    TMax = tMax;
}

TGraph *TNode::getMyTGraph() const
{
    return MyTGraph;
}

void TNode::setMyTGraph(TGraph *myTGraph)
{
    MyTGraph = myTGraph;
}
