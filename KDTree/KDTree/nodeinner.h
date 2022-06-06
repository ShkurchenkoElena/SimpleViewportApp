#ifndef NODE_INNER_H
#define NODE_INNER_H

#include "node.h"

namespace KDTree {

enum Child {
    Child_Left = 0,
    Child_Right = 1
};

class NodeInner : public Node
{
public:
    explicit NodeInner(const Node *childLeft, const Node *childRight, int splitAxis, float splitPos);
    explicit NodeInner(const NodeInner &other);
    ~NodeInner();

    const Node *childLeft;
    const Node *childRight;
    int splitAxis;
    float splitPos;
    const Node *child(Child child) const;

    void findNearestPoint(const QVector3D &point, const QVector<QVector3D> &points, int &nearestPointInd, float &nearestPointDistSquared) const override;
    int findNearestPointInd(const QVector3D &point, const QVector<QVector3D> &points, float *nearestPointDistSquared = nullptr) const override;
    void findNearestPoint(int pointInd, const QVector<QVector3D> &points, int &nearestPointInd, float &nearestPointDistSquared) const override;
    int findNearestPointInd(int pointInd, const QVector<QVector3D> &points, float *nearestPointDistSquared = nullptr) const override;

    void findNearestPointInRadius(const QVector3D &point, const QVector<QVector3D> &points, int &nearestPointInd, float &nearestPointDistSquared,const QVector3D &center,float &radius,float distToCenter) const override;
    int findNearestPointIndInRadius(const QVector3D &point, const QVector<QVector3D> &points, const QVector3D &center,float &radius,float distToCenter, float *nearestPointDistSquared=nullptr) const override;
   // void findNearestPointInRadius(int pointInd, const QVector<QVector3D> &points, int &nearestPointInd, float &nearestPointDistSquared,const QVector3D &center,float &radius,float distToCenter) const override;
   // int findNearestPointIndInRadius(int pointInd, const QVector<QVector3D> &points, const QVector3D &center,float &radius, float distToCenter,float *nearestPointDistSquared) const override;
    int memUsage() const override;
    Node *copy() const override;
};

}

#endif // NODE_INNER_H
