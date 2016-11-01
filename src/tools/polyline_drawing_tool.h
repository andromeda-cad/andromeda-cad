#ifndef POLYLINE_DRAWING_TOOL_H
#define POLYLINE_DRAWING_TOOL_H

#include "src/shapes/polyline.h"

#include "polyline_tool_base.h"

class PolylineDrawingTool : public PolylineToolBase
{
    Q_OBJECT

public:
    PolylineDrawingTool(QObject *parent = 0);

    bool addPoint(QPointF point);

    void finalAction(void);
};

#endif // POLYLINE_DRAWING_TOOL_H

