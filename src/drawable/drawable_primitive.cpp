#include "drawable_primitive.h"

ADrawablePrimitive::ADrawablePrimitive(QObject *parent) : ADrawableBase(parent)
{
    setObjectName(OBJECT_NAME::A_DRAWABLE_PRIMITIVE);

    setFlags(ItemIsSelectable | ItemIsFocusable);
    setAcceptHoverEvents(true);
}

void ADrawablePrimitive::encode(AJsonObject &data, bool hideDefaults) const
{
    ADrawableBase::encode(data, hideDefaults);

    data.remove(OBJ_KEY::FILLED);
}

void ADrawablePrimitive::decode(AJsonObject &data, bool undoable)
{
    ADrawableBase::decode(data, undoable);


}

void ADrawablePrimitive::setLineWidth(double lineWidth)
{
    lineWidth = qMax(lineWidth, SYMBOL_LINE_WIDTH_MIN);

    //TODO - more logic needed perhaps?

    line_width_ = lineWidth;
}

QPen ADrawablePrimitive::pen(const QStyleOptionGraphicsItem *option)
{
    QColor color = line_color_;

    if (isSelected())
    {
        color = color.darker(110);
    }
    if ((nullptr != option) &&
        (option->state & QStyle::State_MouseOver))
    {
        color = color.lighter(120);
    }

    QPen pen(color);
    pen.setWidthF(line_width_);
    pen.setStyle(line_style_);
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);

    return pen;
}

QBrush ADrawablePrimitive::brush(const QStyleOptionGraphicsItem *option)
{
    //TODO change filled_ from a BOOL to an enumeration of allowable colors
    if (!isFilled())
    {
        return QBrush(Qt::NoBrush);
    }

    QColor color = fill_color_;

    if (isSelected())
    {
        color = color.darker(110);
    }
    if ((nullptr != option) &&
        (option->state & QStyle::State_MouseOver))
    {
        color = color.lighter(120);
    }

    QBrush b(color);

    //TODO anything else?

    return b;
}
