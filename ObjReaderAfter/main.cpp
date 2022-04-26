#include <QCoreApplication>
#include "objreader.h"
#include "objreadertests.h"
#include "meshtooltests.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

   ObjReaderTests readerTests;
   QTest::qExec(&readerTests);
   MeshToolTests meshToolTests;
   QTest::qExec(&meshToolTests);

    QString fileName = "C:/Users/Admin/Desktop/sphere.obj";
    ObjReadingTools::ObjData objData;
    QString errorMsg;
    if (!ObjReadingTools::read(fileName, objData, errorMsg)) {
        qDebug() << errorMsg;
        return -1;
    }
    qDebug() << "Done";
    return 0;
}
