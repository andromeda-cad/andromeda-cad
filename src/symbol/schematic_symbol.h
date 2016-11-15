#ifndef SCHEMATIC_SYMBOL_H
#define SCHEMATIC_SYMBOL_H

#include <memory>

#include "src/drawable/drawable_complex.h"
#include "src/shapes/text_item.h"
#include "src/shapes/ellipse.h"
#include "src/shapes/polyline.h"

#include "symbol_pin.h"

class ASchematicSymbol : public ADrawableComplex
{
    Q_OBJECT

    Q_PROPERTY( QString name READ name WRITE setName )
    Q_PROPERTY( QString ref READ ref WRITE setRef )
    Q_PROPERTY( int pinCount READ pinCount STORED false )
    Q_PROPERTY( int symbolCount READ symbolCount WRITE setSymbolCount )

public:
    ASchematicSymbol(QObject *parent = 0);
    virtual ~ASchematicSymbol(void);

    virtual void defaultValues() override;

    // Paint functions
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual QPainterPath shape() const;

    // Property getters
    int pinCount(void) const { return pins_.count(); }
    QString name(void) const { return name_text_.text(); }
    QString ref(void) const { return ref_text_.text(); }
    unsigned char symbolCount(void) { return symbol_count_; }

    virtual void encode(AJsonObject &data, bool hideDefaults = false) const override;
    virtual void decode(AJsonObject &data, bool undoable = true) override;

public slots:
    ASymbolPin* addPin(void);
    ASymbolPin* addPin(ASymbolPin *pin);
    ASymbolPin* addPin(AJsonObject data);
    void setName(QString name) { name_text_.setText(name); }
    void setRef(QString ref) { ref_text_.setText(ref); }
    void setSymbolCount(unsigned char count);

signals:

protected:
    //TODO - make use of proper smart pointers
    QList<ASymbolPin*> pins_;
    QList<ATextItem*> texts_;

    ATextItem ref_text_;
    ATextItem name_text_;

    // Number of sub-symbols
    unsigned char symbol_count_ = 1;

    void updatePins(void);
    void deletePins(void);
};

#endif // SCHEMATIC_SYMBOL_H

