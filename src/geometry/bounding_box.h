#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include <QRectF>
#include <QLineF>

/**
 * @brief The ABoundingBox class
 * Extends the functionality of QRectF to provide extra bounding box features
 */

class ABoundingBox : public QRectF
{
public:
    ABoundingBox(QPointF point) : QRectF(point, QSizeF(0,0)) {}
    ABoundingBox(qreal x, qreal y) : ABoundingBox(QPointF(x,y)) {}

    void start(QPointF point);

    void add(QPointF point);
    void add(QLineF line);

    void expand(qreal offset);

    //TODO something is wrong here
    //ABoundingBox operator+(const QPointF point);
    //inline ABoundingBox &operator+=(const QPointF point);

    //TODO Add functions to "rotate" a bounding box

};

#endif // BOUNDING_BOX_H

