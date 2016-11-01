#include "drawable_complex.h"

ADrawableComplex::ADrawableComplex(QObject *parent) : ADrawableBase(parent)
{
    setObjectName(OBJECT_NAME::A_DRAWABLE_COMPLEX);
}

void ADrawableComplex::encode(AJsonObject &data, bool hideDefaults) const
{
    ADrawableBase::encode(data, hideDefaults);

    // Flipped nature of this object
    if (flip() != (int) Flip::NONE)
    {
        data[OBJ_KEY::FLIP] = flip();
    }
    else
    {
        data.remove(OBJ_KEY::FLIP);
    }

}

void ADrawableComplex::decode(AJsonObject &data, bool undoable)
{
    ADrawableBase::decode(data, undoable);

    if (data.value(OBJ_KEY::FLIP).isDouble())
        setFlip(data.value(OBJ_KEY::FLIP).toInt(flip()));
}

void ADrawableComplex::setFlip(int flip)
{
    if ((flip >= (int) Flip::NONE) && (flip <= (int) Flip::BOTH))
    {
        flip_ = flip;
    }
}

void ADrawableComplex::onChildUpdate()
{
    // Recalculate the shape of this object
    updateShape();

    // Recalculate the bounding rect for this object
    updateBounds();

    // Signal that we have updated
    prepareGeometryChange();
}
