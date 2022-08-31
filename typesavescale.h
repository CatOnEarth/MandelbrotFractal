#ifndef TYPESAVESCALE_H
#define TYPESAVESCALE_H

#include <QPoint>

class TypeSaveScale
{
public:
    TypeSaveScale(double, double, double, double, QPoint);

    QPoint getPixmapof_set() const;
    void setPixmapof_set(const QPoint &value);

    double getCentY() const;
    void setCentY(double value);

    double getCentX() const;
    void setCentX(double value);

    double getCur_scale() const;
    void setCur_scale(double value);

    double getPixmapScale() const;
    void setPixmapScale(double value);

private:
    double cur_scale;
    double centX;
    double centY;
    double pixmapScale;
    QPoint pixmapof_set;
};

#endif // TYPESAVESCALE_H
