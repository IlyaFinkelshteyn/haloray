#pragma once
#include <QOpenGLWidget>
#include <QWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QOpenGLFunctions_4_4_Core>
#include <QSize>
#include <memory>
#include "../simulation/simulationEngine.h"
#include "../opengl/textureRenderer.h"

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_4_4_Core
{
    Q_OBJECT

    typedef std::shared_ptr<HaloSim::SimulationEngine> enginePtr;

public:
    explicit OpenGLWidget(QWidget *parent = 0);
    void setEngine(enginePtr engine);
    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

public slots:
    void toggleRendering();
    void setBrightness(double brightness);
    void setMaxIterations(unsigned int maxIterations);

signals:
    void fieldOfViewChanged(double fieldOfView);
    void cameraOrientationChanged(double pitch, double yaw);
    void nextIteration(unsigned int iteration);
    void maxRaysPerFrameChanged(unsigned int maxRays);

protected:
    void paintGL() override;
    void resizeGL(int w, int h) override;
    void initializeGL() override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

    void wheelEvent(QWheelEvent *event) override;

private:
    enginePtr mEngine;
    std::unique_ptr<OpenGL::TextureRenderer> mTextureRenderer;
    bool mDragging;
    QPoint mPreviousDragPoint;
    float mExposure;
    unsigned int mMaxIterations;
};
