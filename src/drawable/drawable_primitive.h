#ifndef DRAWABLE_PRIMITIVE_H
#define DRAWABLE_PRIMITIVE_H

#include "drawable_base.h"

#include <QColor>

/**
 * @brief The ADrawablePrimitive class describes simple shapes that should be displayed as separate items
 * These shapes can either be added to a scene "as-is",
 * or they can comprise more complex shapes (e.g. symbols and footprints)
 */
class ADrawablePrimitive : public ADrawableBase
{
    Q_OBJECT

public:
    ADrawablePrimitive(QObject *parent = 0);

    Q_PROPERTY( int fillStyle READ fillStyle WRITE setFillStyle )
    Q_PROPERTY( double lineWidth READ lineWidth WRITE setLineWidth )

    // Property getters
    double lineWidth(void) const { return line_width_; }
    int fillStyle(void) const { return fill_style_; }

    virtual void encode(AJsonObject &data, bool hideDefaults = false) const override;
    virtual void decode(AJsonObject &data, bool undoable = true) override;

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override
    {
        Q_UNUSED( painter );
        Q_UNUSED( option );
        Q_UNUSED( widget );
    }

    virtual QRectF boundingRect() const override { return QRectF(); }

    enum FillStyle
    {
        FILL_NONE,
        FILL_BACKGROUND,
        FILL_FOREGROUND
    };

public slots:
    void setFillStyle( int style );
    void setLineWidth( double lineWidth );

protected:
    // Properties unique to ADrawablePrimitive
    int fill_style_ = FillStyle::FILL_BACKGROUND;
    double line_width_  = SYMBOL_LINE_WIDTH_DEFAULT;
    QPen pen(const QStyleOptionGraphicsItem *option = nullptr);
    QBrush brush(const QStyleOptionGraphicsItem *option = nullptr);
};

#endif // DRAWABLE_PRIMITIVE_H

