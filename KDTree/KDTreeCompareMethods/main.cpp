#include <QCoreApplication>
#include "KDTreeUnitTests/kdtreetests.h"
#include "KDTreeUnitTests/utilstests.h"
#include "timetester.h"

int main(int argc, char *argv[])
{
    using namespace KDTree;
    QCoreApplication a(argc, argv);

    KDTreeTests kdtreeTests;
    UtilsTests utilsTests;

    QStringList args;
    args << "" << "-silent";
    QTest::qExec(&utilsTests, args);
    QTest::qExec(&kdtreeTests, args);

//    TimeTester::testName("fileName", ...)

    return 0;
}
