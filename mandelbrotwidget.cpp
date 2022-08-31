#include "mandelbrotwidget.h"
#include <QPainter>
#include <QKeyEvent>
#include <cmath>



MandelbrotWidget::MandelbrotWidget(QWidget *parent)
    : QWidget(parent)
{
    srand(time(0)); // автоматическая рандомизация
    centerX = DefaultCenterX;
    centerY = DefaultCenterY;
    pixmapScale = DefaultScale;
    curScale = DefaultScale;
    save_last_status_of_fractal.clear();

    connect(&thread, &RenderThread::renderedImage,
            this, &MandelbrotWidget::updatePixmap);

    setWindowTitle(u8"Бутерброд");
#ifndef QT_NO_CURSOR
    setCursor(Qt::CrossCursor);
#endif
    resize(550, 400);

    rubberband = new RubberBand(QRubberBand::Rectangle, this);

    DialogInformation *dialog = new DialogInformation();
    dialog->setFixedSize(dialog->size());
    dialog->setModal(true);
    dialog->show();
}


void MandelbrotWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.fillRect(rect(), Qt::black);

    if (pixmap.isNull()) {
        return;
    }

    if (curScale == pixmapScale) {
        painter.drawPixmap(pixmapOffset, pixmap);
    } else {
        double scaleFactor = pixmapScale / curScale;
        int newWidth = int(pixmap.width() * scaleFactor);
        int newHeight = int(pixmap.height() * scaleFactor);
        int newX = pixmapOffset.x() + (pixmap.width() - newWidth) / 2;
        int newY = pixmapOffset.y() + (pixmap.height() - newHeight) / 2;

        painter.save();
        painter.translate(newX, newY);
        painter.scale(scaleFactor, scaleFactor);

        QRectF exposed = painter.transform().inverted().mapRect(rect()).adjusted(-1, -1, 1, 1);
        painter.drawPixmap(exposed, pixmap, exposed);
        painter.restore();
    }

    QFontMetrics metrics = painter.fontMetrics();
    int textWidth;
    if (TYPE_SCALE == 0) {
        textWidth = metrics.horizontalAdvance(HIN_USE_ZOOM_MOUSE);
    }
    else if (TYPE_SCALE == 1) {
        textWidth = metrics.horizontalAdvance(HIN_USE_ZOOM_OBL);
    }
    

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(0, 0, 0, 127));
    painter.drawRect((width() - textWidth) / 2 - 5, 0, textWidth + 10, metrics.lineSpacing() + 5);
    painter.setPen(Qt::white);
    if (TYPE_SCALE == 0) {
        painter.drawText((width() - textWidth) / 2, metrics.leading() + metrics.ascent(), HIN_USE_ZOOM_MOUSE);
    }
    else if (TYPE_SCALE == 1) {
        painter.drawText((width() - textWidth) / 2, metrics.leading() + metrics.ascent(), HIN_USE_ZOOM_OBL);
    }
}


void MandelbrotWidget::resizeEvent(QResizeEvent * /* event */) {
    NotifyMessageBox::showMessage(HINT_CREATE_IMAGE, 1500, this);
    thread.render(centerX, centerY, curScale, size());
}


void MandelbrotWidget::keyPressEvent(QKeyEvent *event) {
    double r_;
    double b_;
    double g_;
    switch (event->key()) {
    case Qt::Key_Plus:
        zoom(ZoomInFactor);
        NotifyMessageBox::showMessage(HINT_CREATE_IMAGE, 1500, this);
        break;
    case Qt::Key_Minus:
        zoom(ZoomOutFactor);
        NotifyMessageBox::showMessage(HINT_CREATE_IMAGE, 1500, this);
        break;
    case Qt::Key_Left:
        scroll(-ScrollStep, 0);
        NotifyMessageBox::showMessage(HINT_CREATE_IMAGE, 1500, this);
        break;
    case Qt::Key_Right:
        scroll(+ScrollStep, 0);
        NotifyMessageBox::showMessage(HINT_CREATE_IMAGE, 1500, this);
        break;
    case Qt::Key_Down:
        scroll(0, -ScrollStep);
        NotifyMessageBox::showMessage(HINT_CREATE_IMAGE, 1500, this);
        break;
    case Qt::Key_Up:
        scroll(0, +ScrollStep);
        NotifyMessageBox::showMessage(HINT_CREATE_IMAGE, 1500, this);
        break;
    case Qt::Key_V: // режим мыши
        TYPE_SCALE = 0;
        NotifyMessageBox::showMessage(HINT_MOOD_MOUSE, 500, this);
        save_last_status_of_fractal.clear();
        update();
        break;
    case Qt::Key_C: // режим выделения областей
        TYPE_SCALE = 1;
        NotifyMessageBox::showMessage(HINT_MOOD_OBL, 500, this);
        update();
        break;
    case Qt::Key_R: // сброс в начальное положение
        centerX = DefaultCenterX;
        centerY = DefaultCenterY;
        curScale = DefaultScale;
        pixmapScale = DefaultScale;
        pixmapOffset = QPoint();
        thread.SetDefaultColor();
        if (TYPE_SCALE == 1 && !save_last_status_of_fractal.empty()) {
            save_last_status_of_fractal.clear();
        }
        NotifyMessageBox::showMessage(HINT_CREATE_IMAGE, 1500, this);
        scroll(0, 0);
        zoom(1);
        update();
        break;
    case Qt::Key_Z:// 
        if (!save_last_status_of_fractal.empty() && TYPE_SCALE == 1) {
            TypeSaveScale saved_scale = save_last_status_of_fractal.back();
            save_last_status_of_fractal.pop_back();

            centerX = saved_scale.getCentX();
            centerY = saved_scale.getCentY();
            pixmapScale = saved_scale.getPixmapScale();
            pixmapOffset = saved_scale.getPixmapof_set();
            curScale = saved_scale.getCur_scale();
            NotifyMessageBox::showMessage(HINT_CREATE_IMAGE, 1500, this);
            thread.SetDefaultColor();
            scroll(0, 0);
            zoom(1);
            update();
            break;
        }
        break;
    case Qt::Key_P:// рандомные цвета
        
        r_ = 0.1 + std::rand() / (double)(std::rand() + RAND_MAX);
        g_ = 0.2 + std::rand() / (double)(std::rand() + RAND_MAX);
        b_ = 0.3 + std::rand() / (double)(std::rand() + RAND_MAX);
        thread.ChangeColor(r_, g_, b_);
        NotifyMessageBox::showMessage(HINT_CREATE_IMAGE, 1500, this);
        scroll(0, 0);
        zoom(1);
        break;
    case Qt::Key_I: // окно информации
        DialogInformation* dialog = new DialogInformation();
        dialog->setFixedSize(dialog->size());
        dialog->setModal(true);
        dialog->show();
        break;
    }
}


#if QT_CONFIG(wheelevent)
void MandelbrotWidget::wheelEvent(QWheelEvent *event) {
    if (TYPE_SCALE == 0) {
        int numDegrees = event->angleDelta().y() / 8;
        double numSteps = numDegrees / 15.0f;
        zoom(pow(ZoomInFactor, numSteps));
        NotifyMessageBox::showMessage(HINT_CREATE_IMAGE, 1500, this);
    }
    else if (TYPE_SCALE == 1) {

    }
}
#endif


void MandelbrotWidget::mousePressEvent(QMouseEvent *event) {
    if (TYPE_SCALE == 0) {
        if (event->button() == Qt::LeftButton) {
            lastDragPos = event->pos();
        }
    }
    else if (TYPE_SCALE == 1) {
        if (event->button() == Qt::LeftButton) {
            lastDragPos = event->pos();
            rubberband->setGeometry(QRect(lastDragPos, QSize()));
            rubberband->show();
        }
    }
}


void MandelbrotWidget::mouseMoveEvent(QMouseEvent* event) {
    if (TYPE_SCALE == 0) {
        if (event->buttons() & Qt::LeftButton) {
            pixmapOffset += event->pos() - lastDragPos;
            lastDragPos = event->pos();
            update();
        }
    }
    else if (TYPE_SCALE == 1) {
        if (event->buttons() & Qt::LeftButton) {
            rubberband->setGeometry(QRect(lastDragPos, event->pos()).normalized());
        }
    }
}


void MandelbrotWidget::mouseReleaseEvent(QMouseEvent *event) {
    if (TYPE_SCALE == 0) {
        if (event->button() == Qt::LeftButton) {
            pixmapOffset += event->pos() - lastDragPos;
            lastDragPos = QPoint();

            int deltaX = (width() - pixmap.width()) / 2 - pixmapOffset.x();
            int deltaY = (height() - pixmap.height()) / 2 - pixmapOffset.y();
            scroll(deltaX, deltaY);
            NotifyMessageBox::showMessage(HINT_CREATE_IMAGE, 1500, this);
        }
    }
    else if (TYPE_SCALE == 1) {
        if (event->button() == Qt::LeftButton) {
            rubberband->hide();

            QPoint Endpoint = event->pos();
            int new_x_centre = (std::max(Endpoint.x(), lastDragPos.x()) - std::min(Endpoint.x(), lastDragPos.x())) / 2 + 
                std::min(Endpoint.x(), lastDragPos.x());
            int new_y_centre = (std::max(Endpoint.y(), lastDragPos.y()) - std::min(Endpoint.y(), lastDragPos.y())) / 2 + 
                std::min(Endpoint.y(), lastDragPos.y());

            TypeSaveScale save_pixmap(curScale, centerX, centerY, pixmapScale, pixmapOffset);
            save_last_status_of_fractal.push_back(save_pixmap);

            QPoint delta((width() / 2 - new_x_centre), (height() / 2 - new_y_centre));
            pixmapOffset += delta;
            int deltaX = (width() - pixmap.width()) / 2 - pixmapOffset.x();
            int deltaY = (height() - pixmap.height()) / 2 - pixmapOffset.y();
            scroll(deltaX, deltaY);
            QPoint tmp_last_drag = lastDragPos;
            lastDragPos = QPoint();

            double length = std::max(Endpoint.x(), tmp_last_drag.x()) - std::min(Endpoint.x(), tmp_last_drag.x());
            double ww = std::max(Endpoint.y(), tmp_last_drag.y()) - std::min(Endpoint.y(), tmp_last_drag.y());

            double numSteps = std::max(ww / width(), length / height());
            zoom(numSteps);

            NotifyMessageBox::showMessage(HINT_CREATE_IMAGE, 1500, this);
        }
    }
}


void MandelbrotWidget::updatePixmap(const QImage &image, double scaleFactor) {
    if (!lastDragPos.isNull()) {
        return;
    }

    pixmap = QPixmap::fromImage(image);
    pixmapOffset = QPoint();
    lastDragPos = QPoint();
    pixmapScale = scaleFactor;
    update();
}


void MandelbrotWidget::zoom(double zoomFactor) {
    curScale *= zoomFactor;
    update();
    thread.render(centerX, centerY, curScale, size());
}


void MandelbrotWidget::scroll(int deltaX, int deltaY) {
    centerX += deltaX * curScale;
    centerY += deltaY * curScale;
    update();
    thread.render(centerX, centerY, curScale, size());
}
