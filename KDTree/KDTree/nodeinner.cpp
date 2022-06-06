#include "nodeinner.h"
#include "math.h"
#include "utils.h"
using namespace KDTree;

NodeInner::NodeInner(const Node *childLeft, const Node *childRight, int splitAxis, float splitPos) :
    Node(),
    childLeft(childLeft),
    childRight(childRight),
    splitAxis(splitAxis),
    splitPos(splitPos)
{}

NodeInner::NodeInner(const NodeInner &other) :
    Node(other),
    childLeft(other.childLeft->copy()),
    childRight(other.childRight->copy()),
    splitAxis(other.splitAxis),
    splitPos(other.splitPos)
{}

NodeInner::~NodeInner()
{
    delete childLeft;
    childLeft = nullptr;
    delete childRight;
    childRight = nullptr;
}

const Node *NodeInner::child(Child child) const
{
    if (child == Child_Left)
        return childLeft;
    else if (child == Child_Right)
        return childRight;

    Q_ASSERT(false);
    return nullptr;
}

void NodeInner::findNearestPoint(const QVector3D &point, const QVector<QVector3D> &points, int &nearestPointInd, float &nearestPointDistSquared) const
{
    const Child childToSearch = point[splitAxis] < splitPos ? Child_Left : Child_Right;
    child(childToSearch)->findNearestPoint(point, points, nearestPointInd, nearestPointDistSquared);

    const float distToSplitPlaneSquared = float(pow(splitPos - point[splitAxis], 2));
    if (distToSplitPlaneSquared > nearestPointDistSquared)
        return;
    const Child otherChild = static_cast<Child>((childToSearch + 1) % 2);
    child(otherChild)->findNearestPoint(point, points, nearestPointInd, nearestPointDistSquared);
}

int NodeInner::findNearestPointInd(const QVector3D &point, const QVector<QVector3D> &points, float *nearestPointDistSquared) const
{
    int nearestPointInd = -1;
    float distSquared = 1e25;
    findNearestPoint(point,points,nearestPointInd,distSquared);
    if (nearestPointDistSquared)
        *nearestPointDistSquared = distSquared;
    return nearestPointInd;
}

void NodeInner::findNearestPoint(int pointInd, const QVector<QVector3D> &points, int &nearestPointInd, float &nearestPointDistSquared) const
{
    const QVector3D &point = points[pointInd];

    const Child childToSearch = point[splitAxis] < splitPos ? Child_Left : Child_Right;
    child(childToSearch)->findNearestPoint(pointInd, points, nearestPointInd, nearestPointDistSquared);

    if (nearestPointInd != -1) {
        const float distToSplitPlaneSquared = float(pow(splitPos - point[splitAxis], 2));
        if (distToSplitPlaneSquared > nearestPointDistSquared)
            return;
    }
    const Child otherChild = static_cast<Child>((childToSearch + 1) % 2);
    child(otherChild)->findNearestPoint(pointInd, points, nearestPointInd, nearestPointDistSquared);
}

int NodeInner::findNearestPointInd(int pointInd, const QVector<QVector3D> &points, float *nearestPointDistSquared) const
{
    int nearestPointInd = -1;
    float distSquared = 1e25;
    findNearestPoint(pointInd, points, nearestPointInd, distSquared);
    if (nearestPointDistSquared)
        *nearestPointDistSquared = distSquared;
    return nearestPointInd;
}


void NodeInner::findNearestPointInRadius(const QVector3D &point, const QVector<QVector3D> &points, int &nearestPointInd, float &nearestPointDistSquared,const QVector3D &center,float &radius,float distToCenter) const{
    const Child childToSearch = center[splitAxis]>splitPos ? Child_Right : Child_Left;
    child(childToSearch)->findNearestPointInRadius(point, points, nearestPointInd, nearestPointDistSquared,center,radius,distToCenter);
 if (nearestPointInd != -1){
    distToCenter=pow((points[nearestPointInd].x()-center.x()),2)+pow((points[nearestPointInd].y()-center.y()),2)+
            pow((points[nearestPointInd].z()-center.z()),2);}

    if ((abs(center[splitAxis]-splitPos)>radius)&&distToCenter<=radius*radius)
        return;
    const Child otherChild = static_cast<Child>((childToSearch + 1) % 2);
    child(otherChild)->findNearestPointInRadius(point, points, nearestPointInd, nearestPointDistSquared,center,radius,distToCenter);


}
int NodeInner::findNearestPointIndInRadius(const QVector3D &point, const QVector<QVector3D> &points, const QVector3D &center,float &radius, float distToCenter,float *nearestPointDistSquared) const
{
    int nearestPointInd =-1;
    float distSquared = 1e25;
    //float distToCenter=1e25;
    findNearestPointInRadius(point,points,nearestPointInd,distSquared,center,radius,distToCenter);
    if (nearestPointDistSquared)
        *nearestPointDistSquared = distSquared;
    return nearestPointInd;
}

/*void NodeInner::findNearestPointInRadius(int pointInd, const QVector<QVector3D> &points, int &nearestPointInd, float &nearestPointDistSquared,const QVector3D &center,float &radius,float distToCenter) const{
    const Child childToSearch = center[splitAxis]>splitPos ? Child_Right : Child_Left;
    child(childToSearch)->findNearestPointInRadius(pointInd, points, nearestPointInd, nearestPointDistSquared,center,radius,distToCenter);
    distToCenter=pow((points[nearestPointInd].x()-center.x()),2)+pow((points[nearestPointInd].y()-center.y()),2)+
            pow((points[nearestPointInd].z()-center.z()),2);

    if ((abs(center[splitAxis]-splitPos)>radius)&&distToCenter<=radius*radius)
        return;
    const Child otherChild = static_cast<Child>((childToSearch + 1) % 2);
    child(otherChild)->findNearestPointInRadius(pointInd, points, nearestPointInd, nearestPointDistSquared,center,radius,distToCenter);

    const QVector3D &point = points[pointInd];
    float min=1e25;
        for(int i=0;i<points.size();i++){
            distToCenter=sqrt(pow((points[i].x()-center.x()),2)+pow((points[i].y()-center.y()),2)+
                    pow((points[i].z()-center.z()),2));
            float distToPoint=sqrt(pow((point.x()-points[i].x()),2)+pow((point.y()-points[i].y()),2)+
                    pow((point.z()-points[i].z()),2));
            if((distToCenter<=radius)&&(distToPoint<=min))
            {       min=distToPoint;
                    nearestPointInd=i;
                    nearestPointDistSquared=distToPoint;
            }
}
}

int NodeInner::findNearestPointIndInRadius(int pointInd, const QVector<QVector3D> &points, const QVector3D &center,float &radius, float distToCenter,float *nearestPointDistSquared) const
{
    int nearestPointInd =-1;
    float distSquared = 1e25;
    findNearestPointInRadius(pointInd,points,nearestPointInd,distSquared,center,radius,distToCenter);
    if (nearestPointDistSquared)
        *nearestPointDistSquared = distSquared;
    return nearestPointInd;
}*/
int NodeInner::memUsage() const
{
    return childLeft->memUsage() + childRight->memUsage();
}

Node *NodeInner::copy() const
{
    return new NodeInner(*this);
}
