#ifndef RENDERTHREAD_H
#define RENDERTHREAD_H

#include <QMutex>
#include <QSize>
#include <QThread>
#include <QWaitCondition>
#include "Complex.h"

QT_BEGIN_NAMESPACE
class QImage;
QT_END_NAMESPACE

//! [0]
class RenderThread : public QThread
{
    Q_OBJECT

public:
    RenderThread(QObject *parent = nullptr);
    ~RenderThread();

    void render(double centerX, double centerY, double scaleFactor, QSize resultSize);

    void ChangeColor(double r_, double g_, double b_) {
        type_b = b_;
        type_g = g_;
        type_r = r_;
        reloadColorMap();
    }

    void reloadColorMap();

    void SetDefaultColor() {
        type_b = start_b;
        type_g = start_g;
        type_r = start_r;
        reloadColorMap();
    }

signals:
    void renderedImage(const QImage &image, double scaleFactor);

protected:
    void run() override;

private:
    const double DefaultCenterX = -0.637011f;
    const double DefaultCenterY = -0.0395159f;
    const double DefaultScale = 0.00403897f;

    const double ZoomInFactor = 0.8f;
    const double ZoomOutFactor = 1 / ZoomInFactor;
    const int ScrollStep = 20;

    const double start_r = 0.3;
    const double start_g = 2;
    const double start_b = 1;


    uint rgbFromWaveLength(double wave);

    QMutex mutex;
    QWaitCondition condition;
    double centerX;
    double centerY;
    double scaleFactor;
    QSize resultSize;
    bool restart;
    bool abort;

    double type_b;
    double type_g;
    double type_r;

    enum { ColormapSize = 512 };
    uint colormap[ColormapSize];
};
//! [0]

#endif // RENDERTHREAD_H
