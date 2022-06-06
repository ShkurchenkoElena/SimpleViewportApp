#ifndef UTILS_H
#define UTILS_H

#include "float.h"
#include <QList>
#include <QVector>
#include <QVector3D>


namespace KDTree {
namespace Utils {

void findPointsRange(const QList<int> &pointIndices, const QVector<QVector3D> &points, QVector3D &min, QVector3D &max);
int findLargestComponentInd(const QVector3D &v);

void splitPointsByPlane(
        const QList<int> &pointIndices, const QVector<QVector3D> &points,
        const int planeAxis, const float planePos,
        QList<int> &leftPointIndices, QList<int> &rightPointIndices);

QList<int> buildEnumeratedList(int nElements);

const QVector<float> MAX_POINT = QVector<float>() << 1e25 << 1e25 << 1e25;
const QVector<float> MIN_POINT = QVector<float>() << -1e25 << -1e25 << -1e25;

}
}


#endif // UTILS_H
