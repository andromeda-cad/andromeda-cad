#include <QJsonArray>
#include <QDebug>

#include "schematic_symbol.h"

ASchematicSymbol::ASchematicSymbol(QObject *parent) : ADrawableComplex(parent)
{
    setObjectName(OBJECT_NAME::A_SCHEMATIC_SYMBOL);

    // Disable undo until initialization is completed
    setUndoEnabled( false );

    defaultValues();

    setUndoEnabled( true );
}

void ASchematicSymbol::defaultValues()
{
    //Initial values
    setName( "CMP 1234567890" );
    setRef( "R? 1IiL" );

    ref_text_.setParent(this);
    ref_text_.setParentItem(this);
    ref_text_.setPos(0,50);

    name_text_.setParent(this);
    name_text_.setParentItem(this);
    name_text_.setPos(0,-50);

}

ASchematicSymbol::~ASchematicSymbol()
{
    deletePins();
}

void ASchematicSymbol::setSymbolCount(unsigned char count)
{
    // Ignore invalid values
    if ((count == 0) || (count == symbol_count_)) return;

    //TODO - Apply undo action
    symbol_count_ = count;
}

/**
 * @brief ASchematicSymbol::addPin
 * Add a new pin from a JSON dataset
 * @param data
 * @return
 */
ASymbolPin* ASchematicSymbol::addPin(AJsonObject data)
{
    // Make a new pin as a child of this symbol
    //TODO - make this a smart pointer
    ASymbolPin *pin = new ASymbolPin(this);

    // Decode pin data and prevent undo
    pin->decode(data, false);

    pins_.append(pin);

    // Add pin as a child of the graphics object
    pin->setParentItem(this);

    prepareGeometryChange();
    update();

    return pin;
}

/**
 * @brief ASchematicSymbol::addPin
 * Attempt to add a new pin to this symbol. A pre-formed pin can be passed as an argument
 * If the supplied pin is nullptr then a new blank pin will be aded
 * @param pin is a pointer to the pin to be added
 * @return a pointer to the created pin
 */
ASymbolPin* ASchematicSymbol::addPin(ASymbolPin *pin)
{
    if (nullptr == pin) return nullptr;

    // Copy the encoded pin data
    return addPin(pin->encoded());
}

ASymbolPin* ASchematicSymbol::addPin()
{
    return addPin(new ASymbolPin());
}

void ASchematicSymbol::encode(AJsonObject &data, bool hideDefaults) const
{
    ADrawableComplex::encode(data, hideDefaults);

    // Encode the name of the symbol
    //data[OBJ_KEY::NAME] = name_text_.text();
    //data[OBJ_KEY::REF] = ref_text_text;

    data[OBJ_KEY::SYMBOLS] = symbol_count_;

    // Encode all the pins
    QJsonArray jPins;

    foreach (ASymbolPin *pin, pins_)
    {
        if (nullptr == pin) continue;

        jPins.append(pin->encoded());
    }

    data[OBJ_KEY::PINS] = jPins;
}

void ASchematicSymbol::decode(AJsonObject &data, bool undoable)
{
    ADrawableComplex::decode(data, undoable);

    QString string;

    if (data.getString(OBJ_KEY::NAME, string))
        setName(string);

    if (data.getString(OBJ_KEY::REF, string))
        setRef(string);

    // TODO
}

/**
 * @brief ASchematicSymbol::updatePins
 * Perform 'cleanup' operations on each pin
 *
 */
//TODO for now all this does is delete nullptrs
void ASchematicSymbol::updatePins()
{
    int index = 0;

    while (index < pins_.count())
    {
        if (nullptr == pins_.at(index))
        {
            pins_.removeAt(index);
            continue;
        }

        // Move on to the next pin
        index++;
    }
}

void ASchematicSymbol::deletePins()
{
    qDeleteAll(pins_.begin(), pins_.end());
    pins_.clear();
}

void ASchematicSymbol::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //TODO
}

QPainterPath ASchematicSymbol::shape() const
{
    return shape_;
}
