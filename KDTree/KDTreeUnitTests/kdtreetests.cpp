#include "kdtreetests.h"
#include "KDTree/kdtree.h"
using namespace KDTree;

KDTreeTests::KDTreeTests(QObject *parent) : QObject(parent)
{}

void KDTreeTests::testBuildTree01()
{
    QVector<QVector3D> points = QVector<QVector3D>() << QVector3D(0,0,0) << QVector3D(2,0,0) << QVector3D(2,1,0) << QVector3D(2,1,0);
    QList<int> pointIndices = QList<int>() << 0 << 1 << 2 << 3;
    Node *node = buildTree(pointIndices,points,1);
    QCOMPARE(((NodeLeaf*)((NodeInner*)node)->childLeft)->pointIndices.toList(),QList<int>() << 0);
    QCOMPARE(((NodeLeaf*)((NodeInner*)((NodeInner*)node)->childRight)->childRight)->pointIndices.toList(),QList<int>() << 2 << 3);
    delete node;
    node = nullptr;
}

void KDTreeTests::testFindNearestPoint01()
{
    Node *node = buildTree(QList<int>(), QVector<QVector3D>(), 1);
    QCOMPARE(node->findNearestPointInd(QVector3D(0,0,0), QVector<QVector3D>()), -1);
    delete node;
    node = nullptr;
}

void KDTreeTests::testFindNearestPoint02()
{
    QVector<QVector3D> points = QVector<QVector3D>() << QVector3D(0,0,0) << QVector3D(0.9,0,0) << QVector3D(2,0,0);
    Node *node = buildTree(points,1);
    float nearestPointDistSquared = 0.0;
    QCOMPARE(node->findNearestPointInd(QVector3D(1.1,0,0), points, &nearestPointDistSquared), 1);
    QVERIFY(qAbs(nearestPointDistSquared - 0.2 * 0.2) < 1e-6);
    delete node;
    node = nullptr;
}

void KDTreeTests::testFindNearestPoint03()
{
    QVector<QVector3D> points = QVector<QVector3D>() << QVector3D(0,0,0) << QVector3D(-2,0,0);
    Node *node = buildTree(points, 1);
    float nearestPointDistSquared = 0.0;
    QCOMPARE(node->findNearestPointInd(QVector3D(-1,0,0), points, &nearestPointDistSquared), 0);
    QVERIFY(qAbs(nearestPointDistSquared - 1 * 1) < 1e-6);
}

void KDTreeTests::testFindNearestPoint04()
{
    QVector<QVector3D> points = QVector<QVector3D>() << QVector3D(0,0,0) << QVector3D(0,0,0);
    Node *node = buildTree(points);
    float nearestPointDistSquared = 0.0;
    QCOMPARE(node->findNearestPointInd(QVector3D(1,0,0), points, &nearestPointDistSquared), 0);
    QVERIFY(qAbs(nearestPointDistSquared - 1 * 1) < 1e-6);
    QCOMPARE(node->findNearestPointInd(QVector3D(0,0,0), points, &nearestPointDistSquared), 0);
    QVERIFY(qAbs(nearestPointDistSquared) < 1e-6);
    delete node;
    node = nullptr;
}

void KDTreeTests::testFindNearestPoint05()
{
    QVector<QVector3D> points = QVector<QVector3D>() << QVector3D(-3,0,0) << QVector3D(-0.9,0,0) << QVector3D(1,0,0) << QVector3D(3,0,0);
    Node *node = buildTree(points);
    float nearestPointDistSquared = 0.0;
    QCOMPARE(node->findNearestPointInd(2, points, &nearestPointDistSquared), 1);
    QVERIFY(qAbs(nearestPointDistSquared - 1.9 * 1.9) < 1e-6);
    delete node;
    node = nullptr;
}
void KDTreeTests::testFindNearestPoint06()
{
    QVector<QVector3D> points = QVector<QVector3D>() << QVector3D(-10,0,0) <<QVector3D(1,0,1)<<QVector3D(1,1,1) <<QVector3D(15,0,0) << QVector3D(-20,0,0) << QVector3D(12,0,0);
    Node *node = buildTree(points);
    float nearestPointDistSquared = 0.0;
    //QVector3D point(1,0,0);
    QVector3D center(2,0,0);
    float radius=3;
    float distToCenter=1e25;
    QCOMPARE(node->findNearestPointIndInRadius(QVector3D(0,0,0), points,center,radius,distToCenter, &nearestPointDistSquared), 1);
    QVERIFY(qAbs(nearestPointDistSquared -2) < 1e-6);
    delete node;
    node = nullptr;
}
void KDTreeTests::testFindNearestPoint07()
{
    QVector<QVector3D> points = QVector<QVector3D>() << QVector3D(-10,0,0) <<QVector3D(-5,0,0) <<QVector3D(10,0,0) << QVector3D(7,0,0) << QVector3D(15,0,0);
    Node *node = buildTree(points);
    float nearestPointDistSquared = 0.0;
    //QVector3D point(1,0,0);
    QVector3D center(3,0,0);
    float radius=2;
    float distToCenter=1e25;
    QCOMPARE(node->findNearestPointIndInRadius(QVector3D(2,0,0), points,center,radius,distToCenter, &nearestPointDistSquared), -1);
    delete node;
    node = nullptr;
}

