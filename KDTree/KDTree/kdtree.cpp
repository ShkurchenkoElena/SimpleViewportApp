#include "kdtree.h"
#include "utils.h"
using namespace KDTree;

Node *KDTree::buildTree(const QList<int> &pointIndices, const QVector<QVector3D> &points, int nPointsInLeaf)
{
    if (pointIndices.count() <= nPointsInLeaf)
        return new NodeLeaf(pointIndices, points);

    QVector3D minPoint;
    QVector3D maxPoint;
    Utils::findPointsRange(pointIndices,points,minPoint,maxPoint);
    const QVector3D sizes = maxPoint - minPoint;
    const int splitAxis = Utils::findLargestComponentInd(sizes);
    const float splitPos = minPoint[splitAxis] + sizes[splitAxis] / 2.0f;

    QList<int> leftPointIndices;
    QList<int> rightPointIndices;
    Utils::splitPointsByPlane(pointIndices,points,splitAxis,splitPos,leftPointIndices,rightPointIndices);
    if (leftPointIndices.isEmpty())
        return new NodeLeaf(pointIndices, points);

    const Node *childLeft = buildTree(leftPointIndices,points,nPointsInLeaf);
    const Node *childRight = buildTree(rightPointIndices,points,nPointsInLeaf);
    return new NodeInner(childLeft,childRight,splitAxis,splitPos);
}

Node *KDTree::buildTree(const QVector<QVector3D> &points, int nPointsInLeaf)
{
    QList<int> pointIndices = Utils::buildEnumeratedList(points.count());
    return buildTree(pointIndices,points,nPointsInLeaf);
}


