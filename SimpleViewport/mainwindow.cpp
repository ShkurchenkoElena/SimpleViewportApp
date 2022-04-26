#include "mainwindow.h"
#include "objreader.h"
#include "meshtools.h"
#include <QMenu>
#include <QMenuBar>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QProgressBar>
#include <QStatusBar>
#include "visualprogressnotifier.h"
#include "consoleprogressnotifier.h"

MainWindow::MainWindow(Viewport *viewport, QWidget *parent)
    : QMainWindow(parent),
      m_viewport(viewport)
{
    setCentralWidget(m_viewport);

    QMenu *fileMenu = new QMenu("File");
    QMenu *toolMenu = new QMenu("Tools");
    /*QAction *normalMap = new QAction("Normal Map", this);
       normalMap->setCheckable(true);
       normalMap->setChecked(false);
       connect(normalMap, SIGNAL(triggered()), this, SLOT(normalMap()));
       */
    fileMenu->addAction("Load mesh", this, &MainWindow::loadMesh, QKeySequence::Open);
    fileMenu->addAction("Save", this, &MainWindow::saveObj,  Qt::CTRL + Qt::Key_S);
    toolMenu->addAction("Color", this, &MainWindow::chooseColor, Qt::CTRL + Qt::Key_C);
    toolMenu->addAction("Normal map ON", this, &MainWindow::normalMapON, Qt::CTRL + Qt::Key_Y);
    toolMenu->addAction("Normal map OFF", this, &MainWindow::normalMapOFF, Qt::CTRL + Qt::Key_N);
   // toolMenu->addAction(normalMap);
    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(toolMenu);


    QProgressBar *progressBar = new QProgressBar();
    statusBar()->addPermanentWidget(progressBar);
    progressBar->hide();
    m_progressNotifier = new VisualProgressNotifier(progressBar);
   //m_progressNotifier = new ConsoleProgressNotifier();
}

MainWindow::~MainWindow()
{
    delete m_progressNotifier;
}

QSize MainWindow::sizeHint() const
{
    return QSize(1024, 768);
}
QVector<float> MainWindow::convertColorVector()
{
    QVector<int> polygonVertexIndices = MeshTools::buildPolygonVertexIndicesVector(objData.m_polygonVertexIndices);
    QVector<int> polygonNormalIndices = MeshTools::buildPolygonVertexIndicesVector(objData.m_polygonNormalIndices);
    QVector<int> polygonStart = MeshTools::buildPolygonStartVector(objData.m_polygonVertexIndices);

    QVector<int> triangleVertexIndices = MeshTools::buildTriangleVertexIndices(polygonVertexIndices, polygonStart);
        QVector<float> triangleVertexCoords = MeshTools::packTriangleVertexCoords(objData.m_vertices, triangleVertexIndices);
        int dataSize = triangleVertexCoords.size() * static_cast<int>(sizeof(float));
    QVector<float>color;

        for(int i = 0; i < dataSize; i+=3)
        {
            QVector3D triad = m_color;
            color.push_back(triad.x());
            color.push_back(triad.y());
            color.push_back(triad.z());
        }
        return color;
}


void MainWindow::loadMesh()
{
    //QString fileName = "../ObjReaderAfter/Teapot.obj";
    QString fileName = QFileDialog::getOpenFileName(this, "Select a mesh", "../ObjReaderAfter", "OBJ file (*.obj)");
    if (fileName.isEmpty())
        return;
    //ObjReadingTools::ObjData objData;
    QString errorMsg;
    if (!ObjReadingTools::read(fileName, objData, errorMsg, m_progressNotifier)) {
        QMessageBox::warning(this, "Failed to load mesh", errorMsg);
        return;
    }
    bool hasNormals = !objData.m_normals.isEmpty() && !objData.m_polygonNormalIndices.isEmpty();
    if (!hasNormals) {
        QMessageBox::warning(this, "Can\'t use this mesh", "The mesh doesn\'t contain normals");
        return;
    }
    QVector<int> polygonVertexIndices = MeshTools::buildPolygonVertexIndicesVector(objData.m_polygonVertexIndices);
    QVector<int> polygonNormalIndices = MeshTools::buildPolygonVertexIndicesVector(objData.m_polygonNormalIndices);
    QVector<int> polygonStart = MeshTools::buildPolygonStartVector(objData.m_polygonVertexIndices);
    m_viewport->makeCurrent();
    if (m_drawableMesh) {
        m_viewport->removeObject(m_drawableMesh);
        delete m_drawableMesh;
    }
    m_color={1.0,0.0,1.0};

    m_drawableMesh = new DrawableMesh(convertColorVector(),objData.m_vertices, polygonVertexIndices, polygonStart, objData.m_normals, polygonNormalIndices);
    //m_viewport->setRotationAngles(QVector3D(90, 0, 0));
    m_viewport->addObject(m_drawableMesh);
    m_viewport->update();
}

void MainWindow::chooseColor()
{   bool bOk;
    float red = float(QInputDialog::getInt( 0, "Input","Red",0,0,255,1,&bOk))/255;
    if (!bOk) {
        red=0;

    }
    float green = float(QInputDialog::getInt( 0, "Input","Green",0,0,255,1,&bOk))/255;
    if (!bOk) {
        green=1;
    }
    float blue = float(QInputDialog::getInt( 0, "Input","Blue",0,0,255,1,&bOk))/255;
    if (!bOk) {
        blue=0;

    }
    m_color={red,green,blue};

    QVector<int> polygonVertexIndices = MeshTools::buildPolygonVertexIndicesVector(objData.m_polygonVertexIndices);
    QVector<int> polygonNormalIndices = MeshTools::buildPolygonVertexIndicesVector(objData.m_polygonNormalIndices);
    QVector<int> polygonStart = MeshTools::buildPolygonStartVector(objData.m_polygonVertexIndices);
    m_viewport->makeCurrent();
    if (m_drawableMesh) {
        m_viewport->removeObject(m_drawableMesh);
        delete m_drawableMesh;
    }

 //QVector3D color(1.0,1.0,0.0);

 m_drawableMesh = new DrawableMesh(convertColorVector(),objData.m_vertices, polygonVertexIndices, polygonStart, objData.m_normals, polygonNormalIndices);
 //m_viewport->setRotationAngles(QVector3D(90, 0, 0));
 m_viewport->addObject(m_drawableMesh);
 m_viewport->update();
}


void MainWindow::normalMapON()
{
        QVector<int> polygonVertexIndices = MeshTools::buildPolygonVertexIndicesVector(objData.m_polygonVertexIndices);
        QVector<int> polygonNormalIndices = MeshTools::buildPolygonVertexIndicesVector(objData.m_polygonNormalIndices);
        QVector<int> polygonStart = MeshTools::buildPolygonStartVector(objData.m_polygonVertexIndices);
        m_viewport->makeCurrent();
        if (m_drawableMesh) {
            m_viewport->removeObject(m_drawableMesh);
            delete m_drawableMesh;
        }
        QVector<int> triangleNormalIndices = MeshTools::buildTriangleVertexIndices(polygonNormalIndices, polygonStart);
        QVector<float> triangleNormalCoords = MeshTools::packTriangleVertexCoords(objData.m_normals, triangleNormalIndices);

        m_drawableMesh = new DrawableMesh(triangleNormalCoords,objData.m_vertices, polygonVertexIndices, polygonStart, objData.m_normals, polygonNormalIndices);
        m_viewport->addObject(m_drawableMesh);
        m_viewport->update();

}
void MainWindow::normalMapOFF(){
    QVector<int> polygonVertexIndices = MeshTools::buildPolygonVertexIndicesVector(objData.m_polygonVertexIndices);
    QVector<int> polygonNormalIndices = MeshTools::buildPolygonVertexIndicesVector(objData.m_polygonNormalIndices);
    QVector<int> polygonStart = MeshTools::buildPolygonStartVector(objData.m_polygonVertexIndices);
    m_viewport->makeCurrent();
    if (m_drawableMesh) {
        m_viewport->removeObject(m_drawableMesh);
        delete m_drawableMesh;
    }


 m_drawableMesh = new DrawableMesh(convertColorVector(),objData.m_vertices, polygonVertexIndices, polygonStart, objData.m_normals, polygonNormalIndices);
 //m_viewport->setRotationAngles(QVector3D(90, 0, 0));
 m_viewport->addObject(m_drawableMesh);
 m_viewport->update();
}
void MainWindow::saveObj(){
    bool bOk;
    QString fileName =QInputDialog::getText( 0, "Input","Enter File Name",QLineEdit::Normal,
                                            "New file",&bOk);
    if (!bOk) {
      fileName="New file";
    }

    QString errorMsg;
    ObjReadingTools::save(fileName,objData,errorMsg);

}

