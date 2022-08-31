#ifndef MANDELBROTWIDGET_H
#define MANDELBROTWIDGET_H

#include <QPixmap>
#include <QWidget>
#include "renderthread.h"
#include <qmenu.h>
#include <QMenuBar>
#include "notifymessagebox.h"
#include "rubberband.h"
#include <qtooltip.h>
#include <QRubberBand>
#include <QPaintEvent>
#include "dialoginformation.h"
#include "typesavescale.h"
#include <iostream>
#include <ctime>


//! [0]
class MandelbrotWidget : public QWidget
{
    Q_OBJECT

public:
    MandelbrotWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
#if QT_CONFIG(wheelevent)
    void wheelEvent(QWheelEvent *event) override;
#endif
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private slots:
    void updatePixmap(const QImage &image, double scaleFactor);
    void zoom(double zoomFactor);

private:
    short int TYPE_SCALE = 0; // {0} мышь; {1} выделение областей 
    const double DefaultCenterX = -0.2;
    const double DefaultCenterY = -0.2;
    const double DefaultScale = 0.00403897f;

    const double ZoomInFactor = 0.8f;
    const double ZoomOutFactor = 1 / ZoomInFactor;
    const int ScrollStep = 20;

    QString HIN_USE_ZOOM_MOUSE = u8"Для маштабирования используйте колесико мыши или + -. Для перемешения используйте курсор или стрелочки";

    QString HIN_USE_ZOOM_OBL = u8"Для маштабирования выделите область. Для перемешения стрелочки";

    QString HINT_CREATE_IMAGE = u8"Создание изображение. Пожалуйста подождите...";

    QString HINT_MOOD_MOUSE = u8"Режим управления мышью";
    QString HINT_MOOD_OBL = u8"Режим выделения областей";
    void scroll(int deltaX, int deltaY);

    RenderThread thread;
    QPixmap pixmap;
    QPoint pixmapOffset;
    QPoint lastDragPos;
    double centerX;
    double centerY;
    double pixmapScale;
    double curScale;

    RubberBand *rubberband;

    std::vector<TypeSaveScale> save_last_status_of_fractal;
};
//! [0]

#endif // MANDELBROTWIDGET_H
