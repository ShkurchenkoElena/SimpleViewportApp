#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QInputDialog>
#include <QMainWindow>
#include "viewport.h"
#include "progressnotifier.h"
#include "drawablemesh.h"
#include "objreader.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Viewport *viewport, QWidget *parent = nullptr);
    ~MainWindow() override;
    QSize sizeHint() const override;
protected:
    ObjReadingTools::ObjData objData;
    QVector3D m_color;
    DrawableMesh *m_drawableMesh = nullptr;
    Camera *m_camera = nullptr;
    Viewport *m_viewport = nullptr;
    AbstractProgressNotifier *m_progressNotifier = nullptr;

    QVector<float> convertColorVector();
protected slots:
    void loadMesh();
    void saveObj();
    void chooseColor();
    void normalMapON();
    void normalMapOFF();
};

#endif // MAINWINDOW_H
