#include "object_encoding.h"

void AJsonObject::addPoint(const QString key, const QPointF point)
{
    insert(key, fromPoint(point));
}

void AJsonObject::addPoint(const QString key, const QPoint point)
{
    QPointF pt(point);

    addPoint(key, pt);
}

bool AJsonObject::getPoint(const QString key, QPointF &point)
{
    QJsonObject jObj = value(key).toObject();

    QJsonValue x = jObj[OBJ_KEY::POS_X];
    QJsonValue y = jObj[OBJ_KEY::POS_Y];

    if (x.isDouble() && y.isDouble())
    {
        point.setX(x.toDouble(point.x()));
        point.setY(y.toDouble(point.y()));

        return true;
    }

    return false;
}

bool AJsonObject::getPoint(const QString key, QPoint &point)
{
    QPointF ptf;

    if (getPoint(key, ptf))
    {
        point.setX((int) ptf.x());
        point.setY((int) ptf.y());

        return true;
    }

    return false;
}

bool AJsonObject::getString(const QString key, QString &val)
{
    QJsonValue jValue =value(key);

    if (jValue.isString())
    {
        val = jValue.toString(val);

        return true;
    }

    return false;
}

bool AJsonObject::getInt(const QString key, int &val)
{
    QJsonValue jValue = value(key);

    if (jValue.isDouble())
    {
        val = (int) jValue.toDouble(val);

        return true;
    }

    return false;
}

bool AJsonObject::getDouble(const QString key, double &val)
{
    QJsonValue jValue =value(key);

    if (jValue.isDouble())
    {
        val = jValue.toDouble(val);

        return true;
    }

    return false;
}

bool AJsonObject::getBool(const QString key, bool &val)
{
    QJsonValue jValue =value(key);

    if (jValue.isBool())
    {
        val =jValue.toBool(val);

        return true;
    }

    return false;
}

QJsonObject AJsonObject::fromPoint(QPointF point)
{
    QJsonObject obj;

    obj[OBJ_KEY::POS_X] = point.x();
    obj[OBJ_KEY::POS_Y] = point.y();

    return obj;
}

QJsonObject AJsonObject::fromPoint(QPoint point)
{
    return fromPoint(QPointF(point.x(), point.y()));
}
