#include <QJsonValue>

#include "object_keys.h"

QJsonObject JsonFromPoint(QPointF point)
{
    QJsonObject json;

    json[OBJ_KEY::POS_X] = point.x();
    json[OBJ_KEY::POS_Y] = point.y();

    return json;
}

bool JsonToPoint(QJsonObject json, QPointF &point)
{
    QJsonValue x = json.value(OBJ_KEY::POS_X);
    QJsonValue y = json.value(OBJ_KEY::POS_Y);

    if (x.isDouble() && y.isDouble())
    {
        point.setX(x.toDouble());
        point.setY(y.toDouble());

        return true;
    }

    return false;
}
