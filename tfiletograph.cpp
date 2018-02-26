#include "tfiletograph.h"
#include <qdebug.h>

using namespace ogdf;
using ogdf::energybased::dtree::GalaxyLevel;

TFileToGraph::TFileToGraph()
{

}

TFileToGraph::TFileToGraph(QStringList files, QString saveSvgPath, bool isLM, int q, bool draw, bool makeTGraphs)
{
    fileZ = files;
    path = saveSvgPath;
    TGraphsVect.clear();
    err = Make(files,isLM,q,draw,makeTGraphs);


}


int TFileToGraph::Make(QStringList files, bool isLM, int q, bool draw, bool makeTGraphs)
{
    internal::GraphObjectContainer<NodeElement>::iterator LnIter;
    internal::GraphObjectContainer<NodeElement>::iterator ColIter;
    QString str;
    QStringList lst;
    edge newE;
    QString WeightN;
    QStringList WeightNLst;


    for (int fi = 0; fi < files.count(); fi++)
    {

        QFile file(files[fi]);
        try
        {
            if(file.open(QIODevice::ReadOnly |QIODevice::Text))
            {

                G.clear();
                GA.init( G, GraphAttributes::nodeGraphics |
                         GraphAttributes::edgeGraphics |
                         GraphAttributes::nodeLabel |
                         GraphAttributes::edgeLabel |
                         GraphAttributes::nodeStyle |
                         GraphAttributes::nodeId |
                         GraphAttributes::edgeType |
                         GraphAttributes::edgeArrow |
                         GraphAttributes::edgeStyle |
                         GraphAttributes::nodeWeight |
                         GraphAttributes::edgeIntWeight); // Create graph attributes for this graph
                GalaxyLevel Gw(G);
                int NodeNums;

                NodeNums = QString(file.readLine()).toInt();
                if (NodeNums == 0)
                { file.close(); return 1;}
                for(int in=0;in<NodeNums;in++)
                    G.newNode(in);

                LnIter = G.nodes.begin();
                ColIter = G.nodes.begin();


                for(int i=0;i<NodeNums;i++)
                {
                    str = file.readLine();       //читаем строку матрицы смежности
                    lst = str.split(" ");    //Делим строку на слова разделенные пробелом
                    if (lst.count() < NodeNums)
                    { file.close(); return 2;}

                    for(int j=0;j<NodeNums;j++)
                    {

                        if(QString(lst.at(j)).toInt()>0)
                        {
                            int wei = QString(lst.at(j)).toInt();
                            newE = G.newEdge(*LnIter,*ColIter);
                            Gw.setEdgeWeight(newE,wei);
                            GA.intWeight(newE) = wei;
                        }
                        (j==NodeNums-1)? ColIter = G.nodes.begin() : ColIter++;
                    }

                    (i==NodeNums-1)? LnIter = G.nodes.begin()  : LnIter++;
                }

                LnIter = G.nodes.begin();
                WeightN = file.readLine();       //читаем строку
                WeightNLst = WeightN.split(" ");    //Делим строку на слова разделенные пробелом
                if (WeightNLst.count() < NodeNums)
                { file.close(); return 2;}

                for(int i=0;i<NodeNums;i++)
                {
                    int wei = QString(WeightNLst.at(i)).toInt();
                    Gw.setWeight(*LnIter,wei);
                    GA.weight(*LnIter) = wei;
                    (i==NodeNums)? LnIter = G.nodes.begin()   : LnIter++;
                }

                WeightN = file.readLine();
                WeightNLst = WeightN.split(" ");
                if (WeightNLst.count() > 2)
                { file.close(); return 2;}


                for(node v : GA.constGraph().nodes)
                {
                    GA.fillColor( v ) = Color( "#fff855" ); // set node color to yellow
                    GA.height( v ) = 20.0; // set the height to 20.0
                    GA.width( v ) = 35.0; // set the width to 35.0
                    GA.shape(v) = Shape::Ellipse;
                    std::string s =std::to_string(v->index()+1) +" (" + std::to_string(int(GA.weight(v))) +")";
                    GA.label( v ) = s;

                }
                for(edge e : GA.constGraph().edges)
                {
                    GA.bends(e);
                    GA.strokeColor(e) = Color("#1234FF");
                    GA.strokeWidth(e) = 0.5;
                    GA.label(e) = std::to_string(GA.intWeight(e));
                }

                if (draw)
                    drawGraph(fi, GA);
                if (makeTGraphs)
                    TGraphsVect << TGraph(Gw,fi,isLM,q);
                if (TGraphsVect.last().getErr() == 1)
                { file.close(); return 4;}

            }
            else
            {
                return 3;
            }
            file.close();
        } catch(...)
        {
            file.close();
            return 1;
        }
    }
    return 0;
}


void TFileToGraph::drawGraph(int fileNum, GraphAttributes GA)
{

    SugiyamaLayout SL; //Compute a hierarchical drawing of G (using SugiyamaLayout)
    SL.setRanking( new OptimalRanking );
    SL.setCrossMin( new MedianHeuristic );
    SL.setLayout(new OptimalHierarchyLayout);
    SL.call( GA );
    QDir().mkdir(path + "/GraphsSVG");
    QString outsvg = path + "/GraphsSVG/Output" + QFileInfo(fileZ[fileNum]).fileName() + ".svg";
    GraphIO::drawSVG( GA, outsvg.toLocal8Bit().toStdString() );
}

TGraph TFileToGraph::getTGraph(int index)
{
    return TGraphsVect[index];
}

QVector<TGraph> TFileToGraph::getTGraphsVect()
{
    return TGraphsVect;
}

void TFileToGraph::drawCritWays(QVector<QVector<int> > crWays, QVector<QVector<int>> fixedPair, int fi)
{
    QFile file(fileZ[fi]);
    if(file.open(QIODevice::ReadOnly |QIODevice::Text))
    {
        node v;
        node w;
        edge e;
        GA = GraphAttributes();
        Make(QStringList(fileZ[fi]), false, 1, false, false);
        GraphAttributes GAcr = GA;
        for (int i = 0; i < crWays.count(); i++)
            for (int j = 0; j < crWays[i].count() - 1; j++)
            {
                v = GAcr.constGraph().firstNode();
                for (int it = 0; it < crWays[i][j] - 1; it++)
                    v = v->succ();
                w = GAcr.constGraph().firstNode();
                for (int it = 0; it < crWays[i][j+1] - 1; it++)
                    w = w->succ();
                e = GAcr.constGraph().searchEdge(v,w);
                GAcr.strokeColor(e) = Color("#ff5533");
                GAcr.strokeWidth(e) = 1.0;
            }

        for (int i = 0; i < fixedPair.count(); i++)
        {
            v = GAcr.constGraph().firstNode();
            for (int it = 0; it <  fixedPair[i][0] - 1; it++)
                v = v->succ();
            w = GAcr.constGraph().firstNode();
            for (int it = 0; it < fixedPair[i][1] - 1; it++)
                w = w->succ();

            e = GAcr.constGraph().searchEdge(v,w);
            GAcr.strokeColor(e) = Color(uint8_t(GAcr.strokeColor(e).red() - 10),uint8_t(GAcr.strokeColor(e).green() + 90),uint8_t(GAcr.strokeColor(e).blue() - 30),uint8_t(220));
            GAcr.intWeight(e) = 0;
            GAcr.label(e) = std::to_string(GAcr.intWeight(e));
        }

        drawGraph(fi, GAcr);
    }
    file.close();
}

int TFileToGraph::getErr()
{
    return err;
}
