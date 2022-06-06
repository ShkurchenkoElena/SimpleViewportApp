#ifndef NAVIGATION_H
#define NAVIGATION_H
#include"camera.h"
#include <QOpenGLWidget>


class Navigation:public QObject
{
    Q_OBJECT

public:
    enum class NavigationState {
        None = 0,
        Pan = 1,
        Zoom = 2,
        Rotate = 3
    };
    Navigation(Camera *camera);

    float aspectRatio(QOpenGLWidget *obj) const;
    QVector3D unprojectScreenPointToEye(const QPoint &pos, float depth, const QMatrix4x4 &projectionMatrix, const QSize &screenSize);
    void doZoom(const QPoint &dstPos);
    void doWheelZoom(float delta);
    void doRotate(const QPoint &dstPos);
    void doPan(QOpenGLWidget *obj,const QPoint &dstPos);

    NavigationState m_navigationState = NavigationState::None;
    Camera *m_camera = nullptr;
    QPoint m_srcPos;
    QQuaternion m_cameraRotation;
};

#endif // NAVIGATION_H
