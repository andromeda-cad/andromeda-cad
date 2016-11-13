#ifndef DRAWABLE_COMPLEX_H
#define DRAWABLE_COMPLEX_H

#include "drawable_base.h"

/**
 * @brief The ADrawableComplex class describes complex shapes which can be made up of (multiple) simpler shapes
 * e.g. schematic symbols, pcb footprints, etc
 */
class ADrawableComplex : public ADrawableBase
{
    Q_OBJECT

    Q_PROPERTY( int flip READ flip WRITE setFlip )

public:
    ADrawableComplex(QObject *parent = 0);

    // Property getters
    int flip(void) const { return flip_; }

    enum class Flip : int {
        NONE = 0x00,
        HORIZONTAL = 0x01, // Flipped around the VERTICAL axis
        VERTICAL = 0x02,   // Flipped around the HORIZONTAL axis
        BOTH = 0x03
    };

    virtual void encode(AJsonObject &data, bool hideDefaults = false) const override;
    virtual void decode(AJsonObject &data, bool undoable = true) override;

public slots:
    void setFlip(int flip);

    // Should be called whenever children are updated;
    virtual void onChildUpdate(void);

    // Implement these in derived classes
    virtual void updateBounds(void) {}
    virtual void updateShape(void) {}

    virtual void defaultValues(void) {}

protected:
    int flip_ = (int) Flip::NONE;

    /* The 'shape' for a complex object could be quite complicated
     * Only calculate it "as needed" (whenever a child changes)
     */
    QPainterPath shape_;
    QRectF bounding_box_;
};


#endif // DRAWABLE_COMPLEX_H

