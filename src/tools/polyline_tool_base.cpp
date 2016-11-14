#include "polyline_tool_base.h"

PolylineToolBase::PolylineToolBase(QObject *parent) : AToolBase(parent)
{

}

void PolylineToolBase::onReset()
{
    polyline_.clear();
}

void PolylineToolBase::nextAction()
{
    if (addPoint(tool_pos_))
    {
        finish();
    }
}

QPen PolylineToolBase::pen()
{
    QPen p( SYMBOL_LINE_COLOR );

    p.setWidthF( polyline_.lineWidth() );
    p.setCapStyle( Qt::RoundCap );
    p.setJoinStyle( Qt::RoundJoin );

    return p;
}

QBrush PolylineToolBase::brush()
{
    switch ( polyline_.fillStyle() )
    {
    default:
    case ADrawablePrimitive::FILL_NONE:
        return Qt::NoBrush;
    case ADrawablePrimitive::FILL_BACKGROUND:
        return QBrush( QColor( SYMBOL_FILL_BG ) );
    case ADrawablePrimitive::FILL_FOREGROUND:
        return QBrush( QColor( SYMBOL_FILL_FG ) );
    }
}

void PolylineToolBase::paintTool(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    painter->setPen( pen() );
    painter->setBrush( brush() );

    if (polyline_.shape().intersects(rect))
    {
        painter->drawPath(polyline_.shape());

        if (toolState() == TOOL_STATE::POLYLINE_ADD_POINT)
        {
            painter->drawLine(polyline_.endPoint(), tool_pos_);
        }

        polyline_.drawBoundingBox(painter);
    }

}

void PolylineToolBase::paintHints(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    if (nullptr == painter)
        return;

    if (toolState() == TOOL_STATE::POLYLINE_ADD_POINT)
    {
        QPen p = hints_pen_;

        // Shift + double-click closes the line
        if (QApplication::keyboardModifiers() & Qt::ShiftModifier)
            p.setColor(DRAWING_TOOL_CLOSE_LINE_COLOR);

        painter->setPen(p);
        painter->drawLine(polyline_.startPoint(), tool_pos_);
    }
}

void PolylineToolBase::getPolyline(APolyline &line)
{
    line.clear();

    for (int i=0; i<polyline_.pointCount(); i++)
    {
        line.addPoint(polyline_.point(i));
    }

    if (force_closed_)
    {
        line.close();
    }

    // Re-center the polyline around its own center
    line.normalize();

    AJsonObject data = polyline_.encoded();

    line.decode( data );
}
