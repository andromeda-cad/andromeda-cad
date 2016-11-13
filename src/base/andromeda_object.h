#ifndef ANDROMEDA_OBJECT_H
#define ANDROMEDA_OBJECT_H

#include <QStringList>
#include <QMetaObject>
#include <QMetaProperty>
#include <QUndoStack>

#include "andromeda_undo.h"
#include "undoable_object_base.h"
#include "object_keys.h"

/**
 * @brief The AndromedaObject class
 * This is designed to be the base class of "any" andromeda object
 * Each AndromedaObject should define functions for JSON serialization
 * The base AndromedaObject provides a makeClone() method which returns a new derived object
 * This object is loaded with parameters based on the JSON serialization
 * This allows a copy operator (which QObject prohibits) which will provide as much or as little functionality as the defined JSON operation
 */

class AndromedaObject : public AUndoableObject
{
    Q_OBJECT

public:
    AndromedaObject(QObject *parent = 0);

    // Default clone operator -> Override in child class using the same template pattern
    virtual AndromedaObject* clone(void) { return makeClone<AndromedaObject>(); }

    QList<QMetaProperty> getProperties(void);
    QStringList getPropertyNames(void);

    virtual void decode(AJsonObject &data, bool undoable = true) override;
    virtual void encode(AJsonObject &data, bool hideDefaults = false) const { Q_UNUSED(data); Q_UNUSED(hideDefaults); }

    // Copy functions
    void copyFrom(AndromedaObject *other);
    void copyTo(AndromedaObject *other);

    // Invertible JSON function for granular undo stacking
    void addUndoAction(QString title, QString key, QJsonValue before, QJsonValue after);
    void addUndoAction(QString title, QString key, QJsonValue value);

    // Various getters
    bool isUndoEnabled(void) { return undo_enabled_; }
    QUndoStack* undoStack(void) { return &undo_stack_; }

public slots:
    virtual bool undo(void);    // Perform to perform top item on undo stack
    virtual bool redo(void);    // Attempt to perform top item on redo stack
    void setUndoEnabled(bool enabled);

signals:
    void edited(void); // Should be emitted when object properties are updated

protected:
    // Stack for holding UNDO / REDO commands for this object
    QUndoStack undo_stack_;
    bool undo_enabled_ = true;

    void signalEdited(bool pass = true);    // Call when an object is edited

    void pushUndoAction(QUndoCommand *action);

    /**
     * @brief makeClone
     * This templated function provides an explicit, consistent method of deep-copying an AndromedaObject
     * Instead of relying on the copy constructor of the object,
     * the makeClone() function relies on the inherent JSON serialization of the AndromedaObject class
     * (Note that the serialization is required for these objects, and we can easily leverage this existing functionality)
     *
     * If a non-JSON clone() is required for a particular class, then simply override the clone() function!
     *
     * To use the JSON deep-copy as below, e.g. for some arbitrary class called AChildClass:
     *
     * virtual AChildClass *clone(void) override { return makeClone<AChildClass>(); }
     *
     * And that's all there is to it!
     *
     * Why do it this way?
     * 1. Consistency between object serialization and internal object state
     * 2. Allows cut / copy / paste operations to be performed on text data
     * 3. Allows undo / redo operations to be performed using the same data
     * 4. "Shallower" copies can be arbitrarily defined by excluding certain data from the JSON object
     * 5. It's always important to have a fifth reason
     *
     * @return a new object of the same type, with identical properties
     */
    template <typename T>
    T* makeClone(void)
    {
        T* cloned = new T();

        AJsonObject data;

        encode(data);

        // The CLONE operation should be non-invertible
        cloned->decode(data, false);

        return cloned;
    }

};

#endif //ANDROMEDA_OBJECT_H
