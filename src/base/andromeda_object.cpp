#include "andromeda_object.h"

#include <QDebug>

AndromedaObject::AndromedaObject(QObject *parent) : AUndoableObject(parent)
{
    setObjectName(OBJECT_NAME::A_OBJECT);
}

/**
 * @brief AndromedaObject::decode
 * Decode JSON object, and add it to the undo stack (if applicable)
 * @param json is a JSON object to be decoded
 * @param undoable determines if this action is "undoable"
 *
 * NOTE: Care must be taken that the base AndromedaObject::decode() function is called
 * BEFORE the actual change is made. Otherwise, the encoded() function will include
 * the new changes.
 */
void AndromedaObject::decode(AJsonObject &data, bool undoable)
{
    // If we want to be able to invert the object, add the current state and the new JSON
    if (undoable && undo_enabled_)
    {
        AJsonObject state = encoded();

        QUndoCommand *undo = new AndromedaJsonUndoAction(QString("json-action"), //TODO fix this
                                                         this,  // Pointer to this object
                                                         state, // State of this object BEFORE the action is applied
                                                         data); // JSON responsible for changing the state

        undo_stack_.push(undo);
    }
}

/**
 * @brief AndromedaObject::setUndoAction
 * Apply an invertible operation for a single JSON key to the undo stack
 * This allows for granular UNDO / REDO operations to be pushed to the stack
 * e.g. change a pin label from "Pin_A" to "Pin_B", only the LABEL value will be pushed
 *
 * It also allows for restoring of deleted data without having to refresh the entire object
 *
 * Multiple invertible operations can be chained using the macro functionality of the undo stack
 *
 * @param title is the title of this action
 * @param key is the JSON key for the data being changed
 * @param before is the value of the key BEFORE the change
 * @param after is the value of the key AFTER tha change
 */
void AndromedaObject::setUndoAction(QString title, QString key, QJsonValue before, QJsonValue after)
{
    if (!undo_enabled_) return;

    //TODO
    /*
    qDebug() << "undo" << title << key;

    AJsonObject jBefore, jAfter;

    jBefore[key] = before;
    jAfter[key]  = after;

    QUndoCommand *undo = new AndromedaJsonUndoAction(title,
                                                     this,
                                                     jBefore,
                                                     jAfter);

    pushUndoAction(undo);
    */
}

/**
 * @brief AndromedaObject::setUndoAction
 * Apply an invertible action, but infer the "before" state rather than stating it
 * @param title is the title of this action
 * @param key is the JSON key for the data being changed
 * @param json is the new JSON value
 */
void AndromedaObject::setUndoAction(QString title, QString key, QJsonValue value)
{
    if (!undo_enabled_) return;

    //TODO

    /*

    AJsonObject jData = encoded();

    // Exctrac the current value for the provided key
    QJsonValue jValueBefore = jData.value(key);

    setUndoAction(title, key, jValueBefore, value);

    */
}

void AndromedaObject::pushUndoAction(QUndoCommand *action)
{
    if (!undo_enabled_) return;

    //TODO - notify parent object that there is a new undo action

    undo_stack_.push(action);
}

/**
 * @brief AndromedaObject::getProperties
 * @return a list of QMetaProperty objects associated with this AndromedaObject
 */
QList<QMetaProperty> AndromedaObject::getProperties()
{
    QList<QMetaProperty> props;

    const QMetaObject *object = metaObject();

    if (nullptr == object)
        return props;

    QMetaProperty prop;

    for (int i=0; i<object->propertyCount(); i++)
    {
        prop = object->property(i);

        props.append(prop);
    }

    return props;
}

/**
 * @brief AndromedaObject::getPropertyNames
 * @return a list of the property names associated with this object
 */
QStringList AndromedaObject::getPropertyNames()
{
    QList<QMetaProperty> props = getProperties();

    QStringList names;

    foreach (QMetaProperty p, props)
    {
        names.append(QString::fromUtf8(p.name()));
    }

    return names;
}

/**
 * @brief AndromedaObject::copyFrom
 * Copy the properties from <other> object to <this> object (via JSON)
 * Any compatible properties will be applied to <this>
 * @param other is a pointer to <other> AndromedaObject
 */
void AndromedaObject::copyFrom(AndromedaObject *other)
{
    if (nullptr == other) return;

    AJsonObject json = other->encoded();

    decode(json);
}

/**
 * @brief AndromedaObject::copyTo
 * Copy the properties from <this> object to <other> object (via JSON)
 * @param other is a pointer to <other> AndromedaObject
 */
void AndromedaObject::copyTo(AndromedaObject *other)
{
    if (nullptr == other) return;

    AJsonObject json = encoded();

    other->decode(json);
}

/**
 * @brief AndromedaObject::undo
 * (Attempt to) undo the item at current stack index
 * @return
 */
bool AndromedaObject::undo()
{
    if (!undo_enabled_) return false;

    if (!undo_stack_.canUndo()) return false;

    // Don't push undo actions to the stack
    undo_enabled_ = false;
    undo_stack_.undo();
    undo_enabled_ = true;

    return true;
}

/**
 * @brief AndromedaObject::redo
 * (Attempt to) redo the item at current stack index
 * @return
 */
bool AndromedaObject::redo()
{
    if (!undo_enabled_) return false;

    if (!undo_stack_.canRedo()) return false;

    // Don't push redo actions to the stack
    undo_enabled_ = false;    
    undo_stack_.redo();
    undo_enabled_ = true;

    return true;
}
