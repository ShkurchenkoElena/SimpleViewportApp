#ifndef UTILSTEST_H
#define UTILSTEST_H

#include <QtTest>

namespace KDTree {

class UtilsTests : public QObject
{
    Q_OBJECT
public:
    explicit UtilsTests(QObject *parent = nullptr);
private slots:
    void testFindPointsRange01();
    void testSplitPointsByPlane01();
};

}

#endif // UTILSTEST_H
