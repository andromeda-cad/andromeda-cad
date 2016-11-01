#include "andromeda_undo.h"

#include <QStringList>

AndromedaJsonUndoAction::AndromedaJsonUndoAction(QString text,
                                                 AUndoableObject *object,
                                                 AJsonObject jBefore,
                                                 AJsonObject jAfter) : QUndoCommand(text)
{
    setText(text);

    object_ = object;

    before_ = jBefore;
    after_ = jAfter;
}

/**
 * @brief AndromedaJsonUndoAction::undo
 * UNDO this action
 */
void AndromedaJsonUndoAction::undo()
{
    if (nullptr == object_) return;

    AJsonObject jBefore = before();

    object_->decode(jBefore, false);
}

/**
 * @brief AndromedaJsonUndoAction::redo
 * REDO this action
 */
void AndromedaJsonUndoAction::redo()
{
    if (nullptr == object_) return;

    AJsonObject jAfter = after();

    object_->decode(jAfter, false);
}

/**
 * @brief AndromedaJsonUndoAction::mergeWith
 * Merge a new JSON undo action with an old one
 * Values from the NEW action override old values if there are duplicate values
 * @param other is a po
 */
bool AndromedaJsonUndoAction::mergeWith(const QUndoCommand *other)
{
    // Ensure we are looking at another JSONable action
    AndromedaJsonUndoAction *aOther = const_cast<AndromedaJsonUndoAction*>(reinterpret_cast<const AndromedaJsonUndoAction*>(other));

    if (nullptr == aOther)
        return false;

    // Actions must point to the same object
    if (aOther->object() != this->object())
        return false;

    // Extract the AFTER JSON objects
    AJsonObject jThis = after();
    AJsonObject jOther = aOther->after();

    // Copy across the data
    foreach (QString key, jOther.keys())
    {
        jThis[key] = jOther.value(key);
    }

    return true;

}
