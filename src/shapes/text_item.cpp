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

void ATextItem::setText(QString text)
{
    if (text == text_) return;

    if (!allow_multiline_)
    {
        if (text.contains('\n'))
            text = text.split('\n').first();
    }

    //TODO - perform any checks here?

    //TODO - make the action invertible
    //addUndoAction();

    text_ = text;

    // Update text width and height
    updateFont();
}

QRectF ATextItem::boundingRect() const
{
    QRectF r;

    r.setWidth(width_); //static_text_.size().width());
    r.setHeight(height_); //static_text_.size().height());

    //TODO - Bounding Rect is calculating incorrectly
    //TODO - because it is based on the static_text_ item...

    //qDebug() << r.normalized();

    return r.normalized();

    /*

    double w = width();
    double h = height();

    ABoundingBox box(QPointF(0,0));

    //TOOD - update baesd on the alignment of the text

    //TODO - update based on text orientation

    /*
    double dx, dy;
    switch (orientation_)
    {
    default:
    case Orientation::LEFT:
        dx = w;
        dy = h;
        break;
    }

    box.add(QPointF(w, -h));

    box.expand(1);

    return box.normalized();
    */
}

void ATextItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    qreal lod = 1;

    if (nullptr != option)
    {
         lod = option->levelOfDetailFromTransform(painter->worldTransform());
    }

    painter->setBrush(Qt::NoBrush);

    painter->setFont(font_);
    painter->setPen(pen());

    // If the text is too small, display a filled rectangle instead
    if (lod < 0.01)
    {
    }
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

    //setCacheMode(QGraphicsItem::ItemCoordinateCache, QSize(2*width_, 2*height_));
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
