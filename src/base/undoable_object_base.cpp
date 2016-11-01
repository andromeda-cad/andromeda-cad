#include "undoable_object_base.h"

AUndoableObject::AUndoableObject(QObject *parent) : QObject(parent)
{
    setObjectName(OBJECT_NAME::A_JSON_OBJECT);
}

/**
 * @brief AUndoableObject::encoded
 * Encode this object to JSON
 * @return a QJsonObject
 */
AJsonObject AUndoableObject::encoded() const
{
    AJsonObject json;

    encode(json);

    return json;
}

/**
 * @brief AUndoableObject::encodedString
 * Encodde this object to a JSON string
 * @return a string representation of the JSON object
 */
QString AUndoableObject::encodedString() const
{
    QJsonObject json = encoded();
    QJsonDocument doc(json);

    return doc.toJson(QJsonDocument::Compact);
}

/**
 * @brief AUndoableObject::encodedRaw
 * Return a binary encoding of the JSON object
 * @return
 */
QByteArray AUndoableObject::encodedRaw() const
{
    QJsonObject json = encoded();
    QJsonDocument doc(json);

    return doc.toBinaryData();
}
