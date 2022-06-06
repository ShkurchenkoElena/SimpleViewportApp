#include "navigation.h"

Navigation::Navigation(Camera *camera): m_camera(camera)
{
}
float Navigation::aspectRatio(QOpenGLWidget *obj) const
{
    Q_ASSERT(obj->height() != 0);
    return obj->width() / float(obj->height());
}

QVector3D Navigation::unprojectScreenPointToEye(const QPoint &pos, float depth, const QMatrix4x4 &projectionMatrix, const QSize &screenSize)
{
    QPointF normPos = Camera::screenPointToNormScreenPoint(pos, screenSize);
    return Camera::unproject(projectionMatrix, normPos, depth);
}

void Navigation::doZoom(const QPoint &dstPos)
{
    const QPoint diff = dstPos - m_srcPos;
    float shift = -diff.x() - diff.y();
    QVector3D origin = m_camera->origin() * (1 + shift * 1e-3);
    m_camera->setOrigin(origin);
    m_srcPos = dstPos;
    //update();
}

void Navigation::doRotate(const QPoint &dstPos)
{
    QPoint shift = dstPos - m_srcPos;
    float rotationSpeed = 0.1f;
    float angleX = -shift.y() * rotationSpeed;
    float angleY = -shift.x() * rotationSpeed;
    QQuaternion srcRotation = m_cameraRotation;
    QQuaternion dstRotationX = QQuaternion::fromAxisAndAngle(1, 0, 0, angleX);
    QQuaternion dstRotationY = QQuaternion::fromAxisAndAngle(0, 1, 0, angleY);
    QQuaternion dstRotation = dstRotationY * srcRotation * dstRotationX;
    m_cameraRotation = dstRotation;
    m_camera->setRotation(dstRotation);
    m_srcPos = dstPos;
    //update();
}

void Navigation::doPan(QOpenGLWidget *obj,const QPoint &dstPos)
{
    QMatrix4x4 projectionMatrix = m_camera->projectionMatrix(aspectRatio(obj));
    float depth = m_camera->origin().z();
    QVector3D srcPos3D = unprojectScreenPointToEye(m_srcPos, depth, projectionMatrix, obj->size());
    QVector3D dstPos3D = unprojectScreenPointToEye(dstPos, depth, projectionMatrix, obj->size());
    QVector3D shift = dstPos3D - srcPos3D;
    m_camera->setOrigin(m_camera->origin() - shift);
    m_srcPos = dstPos;
   // update();
}

void Navigation::doWheelZoom(float delta)
{
    QVector3D origin = m_camera->origin();
    float speed = 1e-3f;
    origin += -delta * origin * speed;
    m_camera->setOrigin(origin);
    //update();
}

