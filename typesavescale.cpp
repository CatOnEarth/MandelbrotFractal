#include "typesavescale.h"

TypeSaveScale::TypeSaveScale(double cur, double cX, double cY, double pixmapsc, QPoint pixset) {
    cur_scale = cur;
    centX = cX;
    centY = cY;
    pixmapScale = pixmapsc;
    pixmapof_set = pixset;
}

QPoint TypeSaveScale::getPixmapof_set() const
{
    return pixmapof_set;
}

void TypeSaveScale::setPixmapof_set(const QPoint &value)
{
    pixmapof_set = value;
}

double TypeSaveScale::getCentY() const
{
    return centY;
}

void TypeSaveScale::setCentY(double value)
{
    centY = value;
}

double TypeSaveScale::getCentX() const
{
    return centX;
}

void TypeSaveScale::setCentX(double value)
{
    centX = value;
}

double TypeSaveScale::getCur_scale() const
{
    return cur_scale;
}

void TypeSaveScale::setCur_scale(double value)
{
    cur_scale = value;
}

double TypeSaveScale::getPixmapScale() const
{
    return pixmapScale;
}

void TypeSaveScale::setPixmapScale(double value)
{
    pixmapScale = value;
}
