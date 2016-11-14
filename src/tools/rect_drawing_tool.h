#ifndef RECT_DRAWING_TOOL_H
#define RECT_DRAWING_TOOL_H

#include "polyline_drawing_tool.h"

class RectDrawingTool : public PolylineToolBase
{
    Q_OBJECT

public:
    RectDrawingTool(QObject *parent = 0);

    bool addPoint(QPointF point);

    void getPolyline(APolyline &line);

    void paintTool(QPainter *painter, const QRectF &rect);

    QRectF getRect(void);

    void paintHints(QPainter *painter, const QRectF &rect)
    {
        Q_UNUSED(painter);
        Q_UNUSED(rect);
    }

    virtual void openEditor(void) override;

protected:
    // Starting position for the rectangle
    QPointF start_pos_;
};

#endif // RECT_DRAWING_TOOL_H

