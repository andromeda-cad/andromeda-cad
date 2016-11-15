#ifndef OBJ_KEYS_H
#define OBJ_KEYS_H

#include <QString>
#include <QJsonObject>
#include <QPointF>

/**
 * "Enumerated" keys for JSON reading / writing
 * It is safer to pass const values than continually re-type strings manually
 *
 */
namespace OBJ_KEY {

// Item options
const QString ITEM_LAYER = "layer";

// Graphics options
const QString FILL_STYLE = "fillStyle";

// Polygons
const QString POINTS = "points";

// Dimensions
const QString RADIUS = "radius";
const QString RADIUS_X = "rx";
const QString RADIUS_Y = "ry";
const QString POS = "pos";
const QString POS_X = "x";
const QString POS_Y = "y";
const QString WIDTH = "width";
const QString HEIGHT = "height";
const QString THICKNESS = "thickness";
const QString LENGTH = "length";

// Angles
const QString ANGLE = "angle";
const QString ROTATION = "rotation";
const QString ORIENTATION= "orientation";

// Pin options
const QString LABEL = "label";

// Schematic symbols
const QString NAME = "name";    // Symbol name
const QString REF = "ref";      // Reference designator
const QString PINS = "pins";    // Pin array
const QString SYMBOLS = "symbols";

// Text items
const QString TEXT = "text";
const QString ALIGNMENT = "alignment";

const QString FLIP = "flip";

}

#endif // OBJ_KEYS_H

