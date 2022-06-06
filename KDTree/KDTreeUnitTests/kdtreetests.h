#ifndef KDTREETESTS_H
#define KDTREETESTS_H

#include <QtTest>

namespace KDTree {

class KDTreeTests : public QObject
{
    Q_OBJECT
public:
    explicit KDTreeTests(QObject *parent = nullptr);
private slots:
    void testBuildTree01();

    void testFindNearestPoint01();
    void testFindNearestPoint02();
    void testFindNearestPoint03();
    void testFindNearestPoint04();
    void testFindNearestPoint05();
    void testFindNearestPoint06();
    void testFindNearestPoint07();
};

}

#endif // KDTREETESTS_H
