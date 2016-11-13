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

    data[OBJ_KEY::THICKNESS] = lineWidth();
    data[OBJ_KEY::FILL_STYLE] = fillStyle();
}

void ADrawablePrimitive::decode(AJsonObject &data, bool undoable)
{
    ADrawableBase::decode(data, undoable);

    double lw;
    int fs;

    if ( data.getDouble( OBJ_KEY::THICKNESS, lw ) )
        setLineWidth( lw );

    if ( data.getInt( OBJ_KEY::FILL_STYLE, fs ) )
        setFillStyle( fs );
}

void ADrawablePrimitive::setFillStyle(int style)
{
    if ( style == fill_style_ ) return;

    switch ( style )
    {
    case FillStyle::FILL_NONE:
    case FillStyle::FILL_BACKGROUND:
    case FillStyle::FILL_FOREGROUND:
        break;
    default:
        return;
    }

    addUndoAction( "SetFillStyle", OBJ_KEY::FILL_STYLE, fill_style_, style );

    fill_style_ = style;
}

void ADrawablePrimitive::setLineWidth(double lineWidth)
{
    if ( lineWidth < SYMBOL_LINE_WIDTH_MIN ) return;
    if ( lineWidth > SYMBOL_LINE_WIDTH_MAX ) return;

    //TODO float comparisons are bad
    if ( lineWidth == line_width_ ) return;

    //TODO - more logic needed perhaps?
    addUndoAction( "SetLineWidth", OBJ_KEY::WIDTH, line_width_, lineWidth );

    line_width_ = lineWidth;
}

QPen ADrawablePrimitive::pen(const QStyleOptionGraphicsItem *option)
{
    QColor color = SYMBOL_LINE_COLOR;

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
    pen.setCapStyle(Qt::RoundCap);
    pen.setJoinStyle(Qt::RoundJoin);

    return pen;
}

QBrush ADrawablePrimitive::brush(const QStyleOptionGraphicsItem *option)
{
    QColor color;

    switch ( fill_style_ )
    {
    default:
    case FillStyle::FILL_NONE:
        return QBrush( Qt::NoBrush );
    case FillStyle::FILL_FOREGROUND:
        color = SYMBOL_FILL_FG;
        break;
    case FillStyle::FILL_BACKGROUND:
        color = SYMBOL_FILL_BG;
        break;
    }

    if ( isSelected() )
    {
        color = color.darker( 110 );
    }
    if ( ( nullptr != option ) &&
        ( option->state & QStyle::State_MouseOver ) )
    {
        color = color.lighter( 120 );
    }

    QBrush b( color );

    return b;
}
