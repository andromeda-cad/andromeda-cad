#ifndef OBJECT_ENCODING_H
#define OBJECT_ENCODING_H

#include <QJsonObject>
#include <QJsonValue>
#include <QPointF>

#include "object_keys.h"

/**
 * @brief The AJsonObject class adds some helper extensions to QJsonObject class
 * These helpers refactor common encode/operations
 * and add extra functionality such as encoding point data in a common format
 */
class AJsonObject : public QJsonObject
{
public:

    // Encode point data to an object
    void addPoint(const QString key, const QPointF point);
    void addPoint(const QString key, const QPoint  point);

    // Automate point extraction
    bool getPoint(const QString key, QPointF &point);
    bool getPoint(const QString key, QPoint  &point);

    // Automate other data extraction
    bool getString(const QString key, QString &val);
    bool getDouble(const QString key, double &val);
    bool getBool(const QString key, bool &val);
    bool getInt(const QString key, int &val);

    // Static functions
    static QJsonObject fromPoint(QPointF point);
    static QJsonObject fromPoint(QPoint  point);

};

#endif // OBJECT_ENCODING_H

