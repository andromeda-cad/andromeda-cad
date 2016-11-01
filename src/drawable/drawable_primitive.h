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

    Q_PROPERTY( bool filled READ isFilled WRITE setFilled )
    Q_PROPERTY( double lineWidth READ lineWidth WRITE setLineWidth )
    Q_PROPERTY( QColor fillColor READ fillColor WRITE setFillColor )
    Q_PROPERTY( QColor lineColor READ lineColor WRITE setLineColor )

    // Property getters
    bool isFilled(void) const { return filled_; }
    double lineWidth(void) const { return line_width_; }
    QColor fillColor(void) const { return fill_color_; }
    QColor lineColor(void) const { return line_color_; }
    Qt::PenStyle lineStyle(void) const { return line_style_; }

    virtual void encode(AJsonObject &data, bool hideDefaults = false) const override;
    virtual void decode(AJsonObject &data, bool undoable = true) override;

public slots:
    void setFilled(bool filled) { filled_ = filled; }
    void setLineWidth(double lineWidth);
    void setLineStyle(Qt::PenStyle lineStyle) { line_style_ = lineStyle; }
    void setFillColor(QColor fillColor) { fill_color_ = fillColor; }
    void setLineColor(QColor lineColor) { line_color_ = lineColor; }

protected:
    // Properties unique to ADrawablePrimitive
    bool filled_        = true;
    double line_width_  = SYMBOL_LINE_WIDTH_DEFAULT;
    QColor fill_color_  = SYMBOL_FILL_COLOR;
    QColor line_color_  = SYMBOL_LINE_COLOR;
    Qt::PenStyle line_style_ = Qt::SolidLine;

    QPen pen(const QStyleOptionGraphicsItem *option = nullptr);
    QBrush brush(const QStyleOptionGraphicsItem *option = nullptr);
};

#endif // DRAWABLE_PRIMITIVE_H

