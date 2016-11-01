#ifndef UNDOABLE_OBJECT_BASE_H
#define UNDOABLE_OBJECT_BASE_H

#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>

#include "object_encoding.h"
#include "object_names.h"

/**
 * @brief The AUndoableObject class is an object
 * which provides JSON encode/decode functions that can be used for:
 * - Object serialization
 * - Object copying / cloning
 * - UNDO / REDO commands
 * - Diff inspection
 *
 * This is the base class for AndromedaObject.
 *
 * All encode/decode functions are virtual and should be reimplemented
 * as required in derived classes
 */
class AUndoableObject : public QObject
{
    Q_OBJECT

public:
    AUndoableObject(QObject *parent = 0);
    virtual ~AUndoableObject(void) {}

    // virtual JSON serialization functions
    virtual void decode(AJsonObject &data, bool undoable = true) { Q_UNUSED(data); Q_UNUSED(undoable) }
    virtual void encode(AJsonObject &data, bool hideDefaults = false) const { Q_UNUSED(data); Q_UNUSED(hideDefaults); }

    virtual AJsonObject encoded(void)   const;
    virtual QByteArray encodedRaw(void) const;
    virtual QString encodedString(void) const;
};

#endif // UNDOABLE_OBJECT_BASE_H

