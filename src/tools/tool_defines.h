#ifndef TOOL_DEFINES_H
#define TOOL_DEFINES_H

#include <QColor>

// Color of tool outline
const QColor DRAWING_TOOL_OUTLINE_COLOR(100,100,255,200);

// Color of line between last point and mouse
const QColor DRAWING_TOOL_TRACE_LINE_COLOR(130,200,200,200);
// Color of line if next action will close the object
const QColor DRAWING_TOOL_CLOSE_LINE_COLOR(130,200,150,200);

//Enumerated states for all drawing tools
enum class TOOL_STATE : int {
    INACTIVE = -1,  // Tool is in an inactive state and won't respond to input
    RESET = 0,      // Tool is in RESET state (default state)
    FINISHED,       // Tool has completed

    // Polyline drawing tools
    POLYLINE_SET_ORIGIN = 10,
    POLYLINE_ADD_POINT,

    // Ellipse drawing tools
    ELLIPSE_SET_CENTER = 20,
    ELLIPSE_SET_POINT,

    // Pin drawing tools
    PIN_SET_POS = 0x30,
};

#endif // TOOL_DEFINES_H

