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

    double dRadius;
    QPointF pRadius;

    if ( data.getDouble( OBJ_KEY::RADIUS, dRadius ) )
    {
        setRadius( dRadius );
    }
    else if ( data.getPoint( OBJ_KEY::RADIUS, pRadius ) )
    {
        setRadius( pRadius );
    }
}

/**
 * @brief AEllipse::encode
 * Encode data particular to an ellipse object
 * @param data
 * @param hideDefaults
 */
void AEllipse::encode(AJsonObject &data, bool hideDefaults) const
{
    ADrawablePrimitive::encode(data, hideDefaults);

    // If both radii are equal, save only a single parameter
    if ( rx_ == ry_ )
    {
        data[OBJ_KEY::RADIUS] = rx_;
    }
    // Otherwise, store an {x,y} pair
    else
    {
        data.addPoint(OBJ_KEY::RADIUS, QPointF(rx(), ry()));
    }
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

    updateBoundingBox();
}

void AEllipse::updateBoundingBox()
{
    bounding_box_.setTopLeft(QPointF(-rx_, -ry_));
    bounding_box_.setWidth(rx_ * 2);
    bounding_box_.setHeight(ry_ * 2);

    double o = line_width_ / 2;

    bounding_box_.adjust(-o,-o,o,o);

    prepareGeometryChange();

    update();
}
