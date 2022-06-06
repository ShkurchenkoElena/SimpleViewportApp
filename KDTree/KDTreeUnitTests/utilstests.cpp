#include "utilstests.h"
#include "KDTree/utils.h"
using namespace KDTree;

UtilsTests::UtilsTests(QObject *parent) : QObject(parent)
{}

void UtilsTests::testFindPointsRange01()
{
    QVector<QVector3D> points = QVector<QVector3D>() << QVector3D(0,-1,2) << QVector3D(1,-2,2);
    QVector3D min;
    QVector3D max;
    Utils::findPointsRange(QList<int>() << 0 << 1, points, min, max);
    QCOMPARE(min,QVector3D(0, -2, 2));
    QCOMPARE(max,QVector3D(1, -1, 2));
}

void UtilsTests::testSplitPointsByPlane01()
{
    QVector<QVector3D> points = QVector<QVector3D>() << QVector3D(0,0,0) << QVector3D(2,0,0);
    QList<int> pointIndices = QList<int>() << 0 << 1;
    QList<int> leftPointIndices;
    QList<int> rightPointIndices;
    Utils::splitPointsByPlane(pointIndices, points, 0 , 1, leftPointIndices, rightPointIndices);
    QCOMPARE(leftPointIndices, QList<int>() << 0);
    QCOMPARE(rightPointIndices, QList<int>() << 1);
    Utils::splitPointsByPlane(pointIndices, points, 1, 0, leftPointIndices, rightPointIndices);
    QCOMPARE(leftPointIndices, QList<int>());
    QCOMPARE(rightPointIndices, QList<int>() << 0 << 1);
    Utils::splitPointsByPlane(pointIndices, points, 0, 3, leftPointIndices, rightPointIndices);
    QCOMPARE(leftPointIndices, QList<int>() << 0 << 1);
    QCOMPARE(rightPointIndices, QList<int>());
}
