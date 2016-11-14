#include "src/dialogs/symbol_editor/polyline_editor_dialog.h"

#include "rect_drawing_tool.h"

RectDrawingTool::RectDrawingTool(QObject *parent) : PolylineToolBase(parent)
{
    setObjectName(TOOL_NAME::DRAW_RECT);
}

bool RectDrawingTool::addPoint(QPointF point)
{
    QRectF rect = getRect().normalized();

    switch (toolState())
    {
    default:
    case TOOL_STATE::POLYLINE_SET_ORIGIN:
        reset();
        start_pos_ = point;
        setToolState(TOOL_STATE::POLYLINE_ADD_POINT);
        break;
    case TOOL_STATE::POLYLINE_ADD_POINT:
        if (rect.width() == 0 || rect.height() == 0)
        {
            return false;
        }

        // Return true to signify finished
        return true;
    }

    return false;
}

void RectDrawingTool::openEditor()
{
    PolylineEditorDialog dlg;

    dlg.setWindowTitle( "Rectangle Properties" );

    dlg.loadSettings( polyline_.encoded() );

    if ( dlg.exec() == QDialog::Accepted )
    {
        AJsonObject settings = dlg.saveSettings();
        polyline_.decode( settings );

        emit updated();
    }
}

void RectDrawingTool::getPolyline(APolyline &line)
{
    QRectF rect = getRect().normalized();

    line.clear();

    //TODO line data should be includedin the encoded() command

    line.addPoint(rect.topLeft());
    line.addPoint(rect.topRight());
    line.addPoint(rect.bottomRight());
    line.addPoint(rect.bottomLeft());
    line.addPoint(rect.topLeft());

    line.normalize();

    AJsonObject data = polyline_.encoded();

    line.decode( data );
}

QRectF RectDrawingTool::getRect()
{
    QPointF delta = tool_pos_ - start_pos_;

    double x = delta.x();
    double y = delta.y();

    QPointF topLeft = start_pos_;

    int mods = QApplication::keyboardModifiers();

    // Enforce a square
    if (mods & Qt::ControlModifier)
    {
        double dim = qMax(qAbs(x), qAbs(y));
        x = dim * (x > 0 ? 1 : -1);
        y = dim * (y > 0 ? 1 : -1);
    }

    if (mods & Qt::ShiftModifier)
    {
        topLeft -= QPointF(x,y);

        x *= 2;
        y *= 2;
    }

    return QRectF(topLeft, QSizeF(x,y));
}

void RectDrawingTool::paintTool(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    if (nullptr == painter)
        return;

    if (toolState() > TOOL_STATE::POLYLINE_SET_ORIGIN)
    {
        painter->setPen( pen() );
        painter->setBrush( brush() );

        painter->drawRect(getRect());
    }
}
