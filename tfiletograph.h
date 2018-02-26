#ifndef TFILETOGRAPH_H
#define TFILETOGRAPH_H

#ifdef _MSC_VER //just for MSVC
   #pragma warning (push)
   #pragma warning (disable: 4068)
      #include <ogdf/fileformats/GraphIO.h>
   #pragma warning (pop)
#elif ...// other compilers
#endif

#include <tgraph.h>
#include <QString>
#include <QFile>
#include <QVector>
#include <QFileInfo>
#include <QDir>

#include <ogdf/energybased/dtree/GalaxyLevel.h>
#include <ogdf/basic/GraphAttributes.h>
#include <ogdf/fileformats/GraphIO.h>
#include <ogdf/layered/SugiyamaLayout.h>
#include <ogdf/layered/OptimalRanking.h>
#include <ogdf/layered/MedianHeuristic.h>
#include <ogdf/layered/OptimalHierarchyLayout.h>
#include <ogdf/graphalg/ShortestPathWithBFM.h>


class TFileToGraph
{

public:
    TFileToGraph();
    TFileToGraph(QStringList files, QString saveSvgPath, bool isLM, int q, bool draw, bool makeTGraphs);
    TGraph getTGraph(int index);
    QVector<TGraph> getTGraphsVect();
    void drawCritWays(QVector<QVector<int>> crWays, QVector<QVector<int>> fixedPair, int fi);
    int getErr();

private:
    int Make(QStringList files, bool isLM, int q, bool draw, bool makeTGraphs);
    void drawGraph(int fileNum, ogdf::GraphAttributes GA);
    QVector<TGraph> TGraphsVect;
    QStringList fileZ;
    QString path;
    ogdf::Graph G;
    ogdf::GraphAttributes GA;
    int err;
};

#endif // TFILETOGRAPH_H
