#ifndef TNODE_H
#define TNODE_H
#include <QVector>
#include <ogdf/energybased/dtree/GalaxyLevel.h>
#include <structs.h>
class TProc;
class TGraph;


class TNode
{

public:
    TNode();
    TNode(ogdf::energybased::dtree::GalaxyLevel Gw, TGraph* myGraph, int index);
    int getNodeNumber() const;
    int getNodeTime() const;
    QVector<TNodeEdge> getPredNodes() const;  //predecessors
    QVector<TNodeEdge> getSuccNodes() const;  //successors
    int getInWeights() const;
    int getOutWeights() const;
    int getSuccEdgeWeight(int nodeNum) const;

    NStat getStatusNode() const;
    void setStatusNode(NStat statOfNode);

    TProc* getExecTProc() const;
    void setExecTProc(TProc* execProc);

    int getPredFixNodeNum() const;
    void setPredFixNodeNum(int predFix);

    int getSuccFixNodeNum() const;
    void setSuccFixNodeNum(int succFix);

    bool isFinal() const;
    bool hasPredFix() const;
    bool hasSuccFix() const;

    double getTMin() const;
    void setTMin(double tMin);

    double getTMax() const;
    void setTMax(double tMax);

    TGraph* getMyTGraph() const;
    void setMyTGraph(TGraph* myTGraph);
    
private:
    int NodeNumber;
    int NodeTime;
    QVector<TNodeEdge> PredNodes;
    QVector<TNodeEdge> SuccNodes;
    int InWeights;
    int OutWeights;

    NStat StatusNode;
    TProc* ExecTProc;
    int PredFixNodeNum;
    int SuccFixNodeNum;
    double TMin;
    double TMax;
    TGraph* MyTGraph;
};

#endif // TNODE_H
