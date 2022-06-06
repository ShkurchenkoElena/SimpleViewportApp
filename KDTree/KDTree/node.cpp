#include "node.h"
#include <QDebug>
using namespace KDTree;

Node::Node(const Node &other)
{
    Q_UNUSED(other)
}

void Node::findNearestPoint(const QVector3D &point, const QVector<QVector3D> &points, int &nearestPointInd, float &nearestPointDistSquared) const
{
    qDebug() << "Calling virtual method Node::findNearestPoint";
    Q_ASSERT(false);
    Q_UNUSED(point)
    Q_UNUSED(points)
    Q_UNUSED(nearestPointInd)
    Q_UNUSED(nearestPointDistSquared)
}

int Node::findNearestPointInd(const QVector3D &point, const QVector<QVector3D> &points, float *nearestPointDistSquared) const
{
    qDebug() << "Calling virtual method Node::findNearestPointInd";
    Q_ASSERT(false);
    Q_UNUSED(point)
    Q_UNUSED(points)
    Q_UNUSED(nearestPointDistSquared)
    return -1;
}

void Node::findNearestPoint(int pointInd, const QVector<QVector3D> &points, int &nearestPointInd, float &nearestPointDistSquared) const
{
    qDebug() << "Calling virtual method Node::findNearestPoint";
    Q_ASSERT(false);
    Q_UNUSED(pointInd)
    Q_UNUSED(points)
    Q_UNUSED(nearestPointInd)
    Q_UNUSED(nearestPointDistSquared)
}

int Node::findNearestPointInd(int pointInd, const QVector<QVector3D> &points, float *nearestPointDistSquared) const
{
    qDebug() << "Calling virtual method Node::findNearestPointInd";
    Q_ASSERT(false);
    Q_UNUSED(pointInd)
    Q_UNUSED(points)
    Q_UNUSED(nearestPointDistSquared)
    return -1;
}

void Node::findNearestPointInRadius(const QVector3D &point, const QVector<QVector3D> &points, int &nearestPointInd, float &nearestPointDistSquared,const QVector3D &center,float &radius, float distToCenter) const
{
    qDebug() << "Calling virtual method Node::findNearestPointinRadius";
    Q_ASSERT(false);
    Q_UNUSED(point)
    Q_UNUSED(points)
    Q_UNUSED(nearestPointInd)
    Q_UNUSED(nearestPointDistSquared)
    Q_UNUSED(center)
    Q_UNUSED(radius)
    Q_UNUSED( distToCenter)
}
int Node::findNearestPointIndInRadius(const QVector3D &point, const QVector<QVector3D> &points,const QVector3D &center,float &radius, float distToCenter,float *nearestPointDistSquared) const{
    qDebug() << "Calling virtual method Node::findNearestPointInd";
    Q_ASSERT(false);
    Q_UNUSED(point)
    Q_UNUSED(points)
    Q_UNUSED(nearestPointDistSquared)
    Q_UNUSED(center)
    Q_UNUSED(radius)
    Q_UNUSED( distToCenter)
    return -1;
}
/*void Node::findNearestPointInRadius(int pointInd, const QVector<QVector3D> &points, int &nearestPointInd, float &nearestPointDistSquared,const QVector3D &center,float &radius,float distToCenter) const {
    qDebug() << "Calling virtual method Node::findNearestPointinRadius";
    Q_ASSERT(false);
    Q_UNUSED(pointInd)
    Q_UNUSED(points)
    Q_UNUSED(nearestPointInd)
    Q_UNUSED(nearestPointDistSquared)
    Q_UNUSED(center)
    Q_UNUSED(radius)
    Q_UNUSED( distToCenter)
}
int Node::findNearestPointIndInRadius(int pointInd, const QVector<QVector3D> &points, const QVector3D &center,float &radius, float distToCenter,float *nearestPointDistSquared) const{
    qDebug() << "Calling virtual method Node::findNearestPointInd";
    Q_ASSERT(false);
    Q_UNUSED(pointInd)
    Q_UNUSED(points)
    Q_UNUSED(nearestPointDistSquared)
    Q_UNUSED(center)
    Q_UNUSED(radius)
    Q_UNUSED( distToCenter)
    return -1;
}*/
int Node::memUsage() const
{
    Q_ASSERT_X(false,"Calling virtual method memUsage()","");
    return -1;
}

Node *Node::copy() const
{
    Q_ASSERT_X(false,"Node::copy()","Calling virtual method");
    return nullptr;
}
