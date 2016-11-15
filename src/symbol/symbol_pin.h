#ifndef SYMBOL_PIN_H
#define SYMBOL_PIN_H

#include "src/drawable/drawable_base.h"

class ASymbolPin : public ADrawableBase
{
    Q_OBJECT

public:
    ASymbolPin(QObject *parent = 0);

    // Clone operator
    virtual ASymbolPin* clone(void) override { return makeClone<ASymbolPin>(); }

    Q_PROPERTY( QString label READ label WRITE setLabel )
    Q_PROPERTY( double length READ length WRITE setLength )

    // Property getters
    QString label(void) const   { return label_; }
    double length(void) const   { return length_; }

    // JSON data
    virtual void encode(AJsonObject &data, bool hideDefaults = false) const override;
    virtual void decode(AJsonObject &data, bool undoable = true) override;

    // Drawing function
    virtual QPainterPath shape(void) const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public slots:
    void setLabel(QString label);
    void setLength(double length);
    QPointF endPoint(void) const;
    QPointF endDelta(void) const;
    virtual void updateBoundingBox() override;

protected:
    // The pin label
    QString label_;
    // Pin length
    double length_ = 100; //TODO - define a default length
    // Pin orientation
};

#endif // SYMBOL_PIN_H

