#include <QFontMetrics>
#include <QDebug>

#include "src/geometry/bounding_box.h"

#include "text_item.h"


ATextItem::ATextItem(QObject *parent) : ADrawablePrimitive(parent)
{
    setObjectName(OBJECT_NAME::A_DRAWABLE_TEXT);

    //static_text_.setPerformanceHint(QStaticText::AggressiveCaching);

    font_.setPointSize(20);
    font_.setFamily( "Roboto Mono" );
}

void ATextItem::setAlignment(int alignment)
{
    if ( alignment == alignment_ ) return;

    switch ( alignment )
    {
    default:
        return;
    case Alignment::LEFT:
    case Alignment::RIGHT:
    case Alignment::CENTER:
        break;
    }

    addUndoAction( "SetAlignment", OBJ_KEY::ALIGNMENT, alignment_, alignment );

    alignment_ = alignment;
}

void ATextItem::setText(QString text)
{
    if ( text == text_ ) return;

    if ( text.isEmpty() ) return;

    if ( !allow_multiline_ )
    {
        if ( text.contains( '\n') )
            text = text.split( '\n' ).first();
    }

    //TODO - perform any checks here?

    addUndoAction( "SetText", OBJ_KEY::TEXT, text_, text );

    text_ = text;

    // Update text width and height
    updateFont();
}

void ATextItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED( widget );

    qreal lod = 1;

    if ( nullptr != option )
    {
         lod = option->levelOfDetailFromTransform(painter->worldTransform());

         // If the text is too small, display a filled rectangle instead
        if (lod < 0.05)
        {
            return;
        }
    }

    painter->setBrush( Qt::NoBrush );

    painter->setFont(font_);
    painter->setPen(pen());

    if (lod < 0.1)
    {
        painter->fillRect(boundingRect(), pen().color());
    }
    else
    {
        //painter->drawStaticText(0, 0, static_text_);
        painter->drawText(boundingRect(), Qt::AlignLeft, text_);
    }

    drawBoundingBox(painter);
}

void ATextItem::updateFont()
{
    QFontMetrics fm(font_);

    width_ = fm.width(text_);
    height_ = fm.height();

    static_text_.setText(text_);

    updateBoundingBox();
}

void ATextItem::updateBoundingBox()
{
    bounding_box_.setWidth( width_ );
    bounding_box_.setHeight( height_ );

    prepareGeometryChange();
}

void ATextItem::encode(AJsonObject &data, bool hideDefaults) const
{
    ADrawablePrimitive::encode(data, hideDefaults);

    data[OBJ_KEY::TEXT] = text_;
}

void ATextItem::decode(AJsonObject &data, bool undoable)
{
    ADrawablePrimitive::decode(data, undoable);

    QString txt;

    if (data.getString(OBJ_KEY::TEXT, txt))
    {
        setText(txt);
    }
}
