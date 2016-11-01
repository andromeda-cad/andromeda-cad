#ifndef ANDROMEDA_UNDO_H
#define ANDROMEDA_UNDO_H

#include <QUndoCommand>
#include <QJsonObject>

#include "object_encoding.h"
#include "undoable_object_base.h"

/**
 * @brief The AndromedaJsonUndoAction class
 * This class provides AndromedaObject undo/redo functionality via the JSON serialization
 * JSON objects are compressed to QByteArray for reduced memory requirements
 *
 * Each command stores the state of the AndromedaObject BEFORE the action is applied
 * (expressed as a JSON representation of the object)
 *
 * The granularity of the action is controlled by the JSON passed to the command.
 *
 * e.g. a single parameter can be altered by only adding THAT parameter to the JSON data
 *
 * Alternatively, multiple parameters can be changed in a single undo/redo commit
 *
 * Multiple commands can be compressed together by merging the JSON data
 * (with NEWER values overriding the OLDER ones)
 *
 */
class AndromedaJsonUndoAction : public QUndoCommand
{
public:
    AndromedaJsonUndoAction(QString text, AUndoableObject* object, AJsonObject aBefore, AJsonObject aAfter);

    virtual void undo(void);
    virtual void redo(void);

    virtual bool mergeWith(const QUndoCommand *other);

    // Getters
    AUndoableObject* object(void) const { return object_; }
    AJsonObject before(void) const { return before_; }
    AJsonObject after(void) const  { return after_; }

protected:
    // Pointer to the object to perform the UNDO / REDO action upon
    AUndoableObject* object_;

    // Before and after states
    AJsonObject before_;
    AJsonObject after_;
};

#endif // ANDROMEDA_UNDO_H

