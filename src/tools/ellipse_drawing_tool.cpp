#include "ellipse_drawing_tool.h"

#include <QApplication>

EllipseDrawingTool::EllipseDrawingTool(QObject *parent) : AToolBase(parent)
{
    setObjectName(TOOL_NAME::DRAW_ELLIPSE);
}

QRectF EllipseDrawingTool::getEllipseRect()
{
    QPointF delta = tool_pos_ - start_pos_;

    double x = delta.x();
    double y = delta.y();

    QPointF topLeft = start_pos_;

    int mods = QApplication::keyboardModifiers();

    // Enforce a circle
    if (mods & Qt::ControlModifier)
    {
        double dim = qMax(qFabs(x), qFabs(y));
        x = dim * (x > 0 ? 1 : -1);
        y = dim * (y > 0 ? 1 : -1);
    }

    if (mods & Qt::ShiftModifier)
    {
        topLeft -= QPointF(x,y);

        x *= 2;
        y *= 2;
    }

    return QRectF(topLeft, QSizeF(x,y)).normalized();
}

void EllipseDrawingTool::paintTool(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    if (nullptr == painter)
        return;

    painter->setBrush(tool_brush_);
    painter->setPen(tool_pen_);

    QRectF r = getEllipseRect();

    switch(toolState())
    {
    case TOOL_STATE::ELLIPSE_SET_POINT:
        painter->drawEllipse(r.center(), r.width()/2, r.height()/2);
        break;
    default:
        break;
    }
}

void EllipseDrawingTool::paintHints(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    QRectF r = getEllipseRect();

    switch (toolState())
    {
    case TOOL_STATE::ELLIPSE_SET_POINT:
        // Draw line towards tool_pos, enscribed on the ellipse
        // TODO
        painter->setPen(hints_pen_);
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(r);
        break;
    default:
        break;
    }
}

void EllipseDrawingTool::nextAction()
{
    switch (toolState())
    {
    case TOOL_STATE::RESET:
    case TOOL_STATE::ELLIPSE_SET_CENTER:
        setCenter(tool_pos_);
        setToolState(TOOL_STATE::ELLIPSE_SET_POINT);
        break;
    case TOOL_STATE::ELLIPSE_SET_POINT:
        finish();
        break;
    default:
        break;
    }
}

void EllipseDrawingTool::onToolPosChanged()
{

}

void EllipseDrawingTool::getEllipse(AEllipse &ellipse)
{
    QRectF r = getEllipseRect();

    ellipse.setPos(r.center());
    //ellipse.moveTo(r.center());
    ellipse.setRadius(r.width()/2, r.height()/2);
}
