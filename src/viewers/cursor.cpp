#include <QPainter>

#include "src/layers/layer_defines.h"

#include "cursor.h"

ACursorItem::ACursorItem() : QGraphicsItem()
{
    setFlag( ItemIgnoresTransformations, true );
    setFlag( ItemIsSelectable, false );

    setSize( 15 );

    // Put the cursor at the top of the scene
    setZValue( (int) LAYER_ID::CURSOR );

    // Configure the pen
    pen_.setWidth(2);
    pen_.setColor(QColor(0, 0, 0, 200));
}

void ACursorItem::setSize(int size)
{
    if (size <= 0) return;

    size_ = size;

    bb_ = QRectF(-size,
                 -size,
                 size * 2,
                 size * 2);

    prepareGeometryChange();
}

QRectF ACursorItem::boundingRect() const
{
    return bb_;
}

void ACursorItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(pen_);
    painter->drawLine(-size_, 0, size_, 0);
    painter->drawLine(0, -size_, 0, size_);
}
