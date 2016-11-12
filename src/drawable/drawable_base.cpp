#include <QPen>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QDebug>
#include <QGraphicsObject>

#include "drawable_base.h"

ADrawableBase::ADrawableBase(QObject *parent) :
    AndromedaObject(parent),
    QGraphicsItem()
{
    setObjectName(OBJECT_NAME::A_DRAWABLE_BASE);

    // Bounding Box Pen
    bounding_box_pen_.setColor(SYMBOL_BB_COLOR);
    bounding_box_pen_.setWidthF(0.5);
    //bounding_box_pen_.setCosmetic(true);
    bounding_box_pen_.setJoinStyle(Qt::RoundJoin);
    bounding_box_pen_.setCapStyle(Qt::RoundCap);
    bounding_box_pen_.setStyle(Qt::DashLine);
}

void ADrawableBase::setLayer(int layer)
{
    //TODO probably need some better logic here
    layer_ = layer;

    emit layerChanged(layer);
}

void ADrawableBase::drawBoundingBox(QPainter *painter)
{
    if (nullptr == painter) return;

    painter->setPen(bounding_box_pen_);
    painter->setBrush(Qt::NoBrush);

    painter->drawRect(boundingRect());
}

void ADrawableBase::encode(AJsonObject &data, bool hideDefaults) const
{
    AndromedaObject::encode(data, hideDefaults);

    // Layer
    data[OBJ_KEY::ITEM_LAYER] = layer();

    // Position
    data.addPoint(OBJ_KEY::POS, pos());

    // Orientation
    //TODO - orientation could be encoded as a string
    //e.g. left/right/up/down
    //OR as an actual angle (eg 270)
    data[OBJ_KEY::ORIENTATION] = (int) orientation();
}

void ADrawableBase::decode(AJsonObject &data, bool undoable)
{
    AndromedaObject::decode(data, undoable);

    QPointF point;
    int i;

    if (data.getPoint(OBJ_KEY::POS, point))
        setPos(point);

    if (data.getInt(OBJ_KEY::ORIENTATION, i))
    {
        setOrientation(i);
    }

    //TODO
}

void ADrawableBase::setPos(QPointF point)
{
    // Ignore the same position
    if (point == pos()) return;

    //TODO - remove hard coded action title
    addUndoAction("Move",
                  OBJ_KEY::POS,
                  AJsonObject::fromPoint(pos()),
                  AJsonObject::fromPoint(point));

    QGraphicsItem::setPos(point);
}

void ADrawableBase::setPos(double x, double y)
{
    setPos(QPointF(x,y));
}

void ADrawableBase::setX(double x)
{
    setPos(x, this->y());
}

void ADrawableBase::setY(double y)
{
    setPos(this->x(), y);
}

/**
 * @brief ASymbolPin::rotate
 * Rotates the pin in the specified direction
 * @param ccw is bool, true = counter-clockwise (default), false = clockwise
 */
void ADrawableBase::rotate(bool ccw)
{
    unsigned int orient = orientation();

    orient += ccw ? 1 : -1;

    orient = (orient % (int) Orientation::INVALID);

    setOrientation(orient);
}

void ADrawableBase::setOrientation(unsigned int orientation)
{
    // Ignore same value
    if (orientation == orientation_) return;


    //TODO - some more complex functionality here?
    switch (orientation)
    {
    case (int) Orientation::LEFT:
    case (int) Orientation::DOWN:
    case (int) Orientation::RIGHT:
    case (int) Orientation::UP:
        //TODO - apply inverse action
        orientation_ = orientation;
        break;
    default:
        // Invalid
        return;
    }

    prepareGeometryChange();
}
