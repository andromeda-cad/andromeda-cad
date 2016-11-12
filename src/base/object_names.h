#ifndef OBJECT_NAMES_H
#define OBJECT_NAMES_H

namespace OBJECT_NAME
{
const QString A_JSON_OBJECT = "AJsonCloneable";
// Base object class
const QString A_OBJECT = "AndromedaObject";

// Drawable base
const QString A_DRAWABLE_BASE = "ADrawableBase";

// Primitive drawable items
const QString A_DRAWABLE_PRIMITIVE = "ADrawablePrimitive";
const QString A_DRAWABLE_ELLIPSE = "ADrawableEllipse";
const QString A_DRAWABLE_POLYLINE = "ADrawablePolyline";
const QString A_DRAWABLE_SYMBOL_PIN = "ADrawableSymbolPin";
const QString A_DRAWABLE_TEXT = "ADrawableText";

// Complex drawable items
const QString A_DRAWABLE_COMPLEX = "ADrawableComplex";
const QString A_SCHEMATIC_SYMBOL = "ASchematicSymbol";

}

namespace TOOL_NAME
{
const QString BASE = "ToolBase";

// Primitive drawing tools
const QString DRAW_POLYLINE = "DrawPolyline";
const QString DRAW_ELLIPSE = "DrawEllipse";
const QString DRAW_RECT = "DrawRect";

const QString DRAW_PIN = "DrawPin";

// Primitive edit tools
const QString EDIT_POLYLINE = "EditPolyline";
}

#endif // OBJECT_NAMES_H

