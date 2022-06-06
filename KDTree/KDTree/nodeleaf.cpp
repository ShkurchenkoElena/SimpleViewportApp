#include "nodeleaf.h"
#include "utils.h"
#include<cmath>
using namespace KDTree;

NodeLeaf::NodeLeaf(const QList<int> &pointIndices, const QVector<QVector3D> &points) :
    Node(),
    pointIndices(pointIndices.toVector())
{
    const int nSubsettedPoints = pointIndices.size();
    subsettedPoints.resize(nSubsettedPoints);
    for (int pointInd = 0; pointInd < nSubsettedPoints; ++pointInd)
        subsettedPoints[pointInd] = points[pointIndices[pointInd]];
}

NodeLeaf::NodeLeaf(const NodeLeaf &other) :
    Node(other),
    pointIndices(other.pointIndices),
    subsettedPoints(other.subsettedPoints)
{}

void NodeLeaf::findNearestPoint(const QVector3D &point, const QVector<QVector3D> &points, int &nearestPointInd, float &nearestPointDistSquared) const
{
    Q_UNUSED(points)
    const int nSubsettedPoints = pointIndices.size();
    for (int pointInd = 0; pointInd < nSubsettedPoints; ++pointInd) {
        const float distSquared = (subsettedPoints[pointInd] - point).lengthSquared();
        if (distSquared < nearestPointDistSquared) {
            nearestPointDistSquared = distSquared;
            nearestPointInd = pointIndices[pointInd];
        }
    }
}

int NodeLeaf::findNearestPointInd(const QVector3D &point, const QVector<QVector3D> &points, float *nearestPointDistSquared) const
{
    int nearestPointInd = -1;
    float distSquared = 1e25;
    findNearestPoint(point, points, nearestPointInd, distSquared);
    if (nearestPointDistSquared)
        *nearestPointDistSquared = distSquared;
    return nearestPointInd;
}

void NodeLeaf::findNearestPoint(int pointInd, const QVector<QVector3D> &points, int &nearestPointInd, float &nearestPointDistSquared) const
{
    const QVector3D &point = points[pointInd];
    const int nSubsettedPoints = pointIndices.size();
    for (int otherPointInd = 0; otherPointInd < nSubsettedPoints; ++otherPointInd) {
        if (pointIndices[otherPointInd] == pointInd)
            continue;

        const float distSquared = (subsettedPoints[otherPointInd] - point).lengthSquared();
        if (distSquared < nearestPointDistSquared) {
            nearestPointDistSquared = distSquared;
            nearestPointInd = pointIndices[otherPointInd];
        }
    }
}

int NodeLeaf::findNearestPointInd(int pointInd, const QVector<QVector3D> &points, float *nearestPointDistSquared) const
{
    int nearestPointInd = -1;
    float distSquared = 1e25;
    findNearestPoint(pointInd, points, nearestPointInd, distSquared);
    if (nearestPointDistSquared)
        *nearestPointDistSquared = distSquared;
    return nearestPointInd;
}

void NodeLeaf::findNearestPointInRadius(const QVector3D &point, const QVector<QVector3D> &points, int &nearestPointInd, float &nearestPointDistSquared,const QVector3D &center,float &radius, float distToCenter) const{
    Q_UNUSED(points)
    const int nSubsettedPoints = pointIndices.size();
    for (int pointInd = 0; pointInd < nSubsettedPoints; ++pointInd) {
        distToCenter = (subsettedPoints[pointInd] - center).lengthSquared();
        const float distSquared = (subsettedPoints[pointInd] - point).lengthSquared();

        if ((distToCenter<=radius*radius)&&(distSquared < nearestPointDistSquared)) {
            nearestPointDistSquared = distSquared;
            nearestPointInd = pointIndices[pointInd];
        }
    }
}
int NodeLeaf::findNearestPointIndInRadius(const QVector3D &point, const QVector<QVector3D> &points, const QVector3D &center,float &radius,float distToCenter, float *nearestPointDistSquared) const{
    int nearestPointInd = 0;
    float distSquared = 1e25;
    //float distToCenter=1e25;
    findNearestPointInRadius(point, points, nearestPointInd, distSquared,center,radius,distToCenter);
    if (nearestPointDistSquared)
        *nearestPointDistSquared = distSquared;
    if(distToCenter>radius*radius)
        return -1;
    return nearestPointInd;
}

/*void NodeLeaf::findNearestPointInRadius(int pointInd, const QVector<QVector3D> &points, int &nearestPointInd, float &nearestPointDistSquared,const QVector3D &center,float &radius,float distToCenter) const
{
    const QVector3D &point = points[pointInd];
    const int nSubsettedPoints = pointIndices.size();
    for (int otherPointInd = 0; otherPointInd < nSubsettedPoints; ++otherPointInd) {
        if (pointIndices[otherPointInd] == pointInd)
            continue;

        const float distSquared = (subsettedPoints[otherPointInd] - point).lengthSquared();
        distToCenter = (subsettedPoints[pointInd] - center).lengthSquared();

        if ((distSquared < nearestPointDistSquared)&&(distToCenter<=radius*radius)) {
            nearestPointDistSquared = distSquared;
            nearestPointInd = pointIndices[otherPointInd];
        }
    }
}*/

int NodeLeaf::memUsage() const
{
    return pointIndices.count() * static_cast<int>(sizeof(float)) + subsettedPoints.count() * static_cast<int>(sizeof(QVector3D));
}

Node *NodeLeaf::copy() const
{
    return new NodeLeaf(*this);
}
