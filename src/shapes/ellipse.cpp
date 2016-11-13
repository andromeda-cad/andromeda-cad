#include "ellipse.h"

#include <math.h>

AEllipse::AEllipse(QObject *parent) : ADrawablePrimitive(parent)
{
    setObjectName(OBJECT_NAME::A_DRAWABLE_ELLIPSE);

    setRadius(0);
}

void AEllipse::decode(AJsonObject &data, bool undoable)
{
    ADrawablePrimitive::decode(data, undoable);

    //TODO

    /*
    // Decode radius
    QJsonValue jRadius = data[OBJ_KEY::RADIUS];

    // Extract ellipse radius

    // Single value indicates circle
    if (jRadius.isDouble())
    {
        setRadius(jRadius.toDouble());
    }
    else if (jRadius.isObject())
    {
        // Radius supplied as x/y pair
        QJsonObject jRxy = jRadius.toObject();

        QJsonValue rx = jRxy[OBJ_KEY::RADIUS_X];
        QJsonValue ry = jRxy[OBJ_KEY::RADIUS_Y];

        if (rx.isDouble() && ry.isDouble())
            setRadius(rx.toDouble(), ry.toDouble());
    }
    */
}

void AEllipse::encode(AJsonObject &data, bool hideDefaults) const
{
    ADrawablePrimitive::encode(data, hideDefaults);

    data[OBJ_KEY::THICKNESS] = lineWidth();
    data[OBJ_KEY::FILLED] = isFilled();
    //TODO only encode one radius value if the ellipse is circular

    data.addPoint(OBJ_KEY::RADIUS, QPointF(rx(), ry()));
}

QRectF AEllipse::boundingRect() const
{
    return bb_;
}

QPainterPath AEllipse::shape() const
{
    QPainterPath path;

    path.addEllipse(QPointF(0,0), rx_, ry_);

    return path;
}

void AEllipse::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setPen(pen(option));
    painter->setBrush(brush(option));

    painter->drawEllipse(QPointF(0,0), rx_, ry_);

    //if (draw_bounding_box_)
        drawBoundingBox(painter);

}

void AEllipse::setRadius(double rx, double ry)
{
    // Ignore same values
    if ((rx == rx_) && (ry == ry_)) return;

    //TODO - make this action undoable
    //addUndoAction(OBJ_KEY::RADIUS, );

    if (rx != 0)
        rx_ = qFabs(rx);

    if (ry != 0)
        ry_ = qFabs(ry);

    bb_.setTopLeft(QPointF(-rx, -ry));
    bb_.setWidth(rx * 2);
    bb_.setHeight(ry * 2);

    double o = line_width_ / 2;

    bb_.adjust(-o,-o,o,o);

    prepareGeometryChange();

    update();
}
