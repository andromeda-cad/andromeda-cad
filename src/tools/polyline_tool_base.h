#ifndef POLYLINE_TOOL_BASE_H
#define POLYLINE_TOOL_BASE_H

#include "src/shapes/polyline.h"

#include "tool_base.h"

class PolylineToolBase : public AToolBase
{
    Q_OBJECT

public:
    PolylineToolBase(QObject *parent = 0);

    virtual void getPolyline(APolyline &line);

    virtual bool addPoint(QPointF point) { Q_UNUSED(point); return false; }

    virtual void nextAction(void) override;

    virtual void paintTool(QPainter *painter, const QRectF &rect) override;
    virtual void paintHints(QPainter *painter, const QRectF &rect) override;

protected:
    APolyline polyline_;

    bool allow_self_intersection_ = false;
    bool force_closed_ = false;

    void onReset(void);

    QPen pen(void);
    QBrush brush(void);

};

#endif // POLYLINE_TOOL_BASE_KH

