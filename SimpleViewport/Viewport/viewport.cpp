#include "viewport.h"
#include <QOpenGLContext>
#include <QDebug>
#include <QMouseEvent>
#include "meshtools.h"

Viewport::Viewport(Camera *camera, QWidget *parent) :
    QOpenGLWidget(parent),m_navigate(camera)/*,
    m_camera(camera)*/
{ //!!!
   //qApp->installEventFilter(this);
}

Viewport::~Viewport()
{
}

void Viewport::addObject(DrawableObject *drawableObject)
{
    m_drawableObjects.append(drawableObject);
}

void Viewport::removeObject(DrawableObject *drawableObject)
{
    int index = m_drawableObjects.indexOf(drawableObject);
    Q_ASSERT(index != -1);
    m_drawableObjects.removeAt(index);
}

void Viewport::clearObjects()
{
    m_drawableObjects.clear();
}

void Viewport::initializeGL()
{
}

void Viewport::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
}

void Viewport::paintGL()
{
    qglClearColor(m_backgroundColor);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (DrawableObject *drawableObject : m_drawableObjects)
        drawableObject->draw( m_navigate.m_camera->viewMatrix(),  m_navigate.m_camera->projectionMatrix( m_navigate.aspectRatio(this)));
}


void Viewport::qglClearColor(const QColor &color)
{
    glClearColor(color.redF(), color.greenF(), color.blueF(), color.alphaF());
}

void Viewport::mousePressEvent(QMouseEvent *event)
{
    bool altPressed = (event->modifiers() == Qt::AltModifier);
    bool startPanning = (event->buttons() == Qt::MiddleButton) && altPressed;
    bool startRotating = (event->buttons() == Qt::LeftButton) && altPressed;
    if (startPanning) {
        m_navigate.m_navigationState =Navigation::NavigationState::Pan;
        m_navigate.m_srcPos = event->pos();
    }
    bool startZooming = (event->buttons() == Qt::RightButton) && altPressed;
    if (startZooming) {
        m_navigate.m_navigationState =Navigation::NavigationState::Zoom;
        m_navigate.m_srcPos = event->pos();
    }
    if (startRotating) {
        m_navigate.m_navigationState = Navigation::NavigationState::Rotate;
        m_navigate.m_srcPos = event->pos();
        m_navigate.m_cameraRotation = m_navigate.m_camera->rotation();
    }
}

void Viewport::mouseMoveEvent(QMouseEvent *event)
{
    if (m_navigate.m_navigationState == Navigation::NavigationState::Zoom)
       { m_navigate.doZoom(event->pos());
        update();}
    if (m_navigate.m_navigationState == Navigation::NavigationState::Rotate)
       { m_navigate.doRotate(event->pos());
        update();}
    if (m_navigate.m_navigationState == Navigation::NavigationState::Pan)
       { m_navigate.doPan(this,event->pos());
        update();}
}

void Viewport::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    m_navigate.m_navigationState = Navigation::NavigationState::None;
}

void Viewport::wheelEvent(QWheelEvent *event)
{
    m_navigate.doWheelZoom(event->delta());
}


//!!!!
/*bool Viewport::eventFilter(QObject *obj, QMouseEvent *event){

     QObject::eventFilter(obj,event);
}*/
