#ifndef NODE_LEAF_H
#define NODE_LEAF_H

#include "node.h"
#include <QList>

namespace KDTree {

class NodeLeaf : public Node
{
public:
    explicit NodeLeaf(const QList<int> &pointIndices, const QVector<QVector3D> &points);
    explicit NodeLeaf(const NodeLeaf &other);
    ~NodeLeaf() = default;

    const QVector<int> pointIndices;
    QVector<QVector3D> subsettedPoints;

    void findNearestPoint(const QVector3D &point, const QVector<QVector3D> &points, int &nearestPointInd, float &nearestPointDistSquared) const override;
    int findNearestPointInd(const QVector3D &point, const QVector<QVector3D> &points, float *nearestPointDistSquared = nullptr) const override;
    void findNearestPoint(int pointInd, const QVector<QVector3D> &points, int &nearestPointInd, float &nearestPointDistSquared) const override;
    int findNearestPointInd(int pointInd, const QVector<QVector3D> &points, float *nearestPointDistSquared = nullptr) const override;

    void findNearestPointInRadius(const QVector3D &point, const QVector<QVector3D> &points, int &nearestPointInd, float &nearestPointDistSquared,const QVector3D &center,float &radius, float distToCenter) const override;
    int findNearestPointIndInRadius(const QVector3D &point, const QVector<QVector3D> &points, const QVector3D &center,float &radius,float distToCenter, float *nearestPointDistSquared=nullptr) const override;
   // void findNearestPointInRadius(int pointInd, const QVector<QVector3D> &points, int &nearestPointInd, float &nearestPointDistSquared,const QVector3D &center,float &radius,float distToCenter) const override;
    int memUsage() const override;
    Node *copy() const override;
};

}

#endif // NODE_LEAF_H
