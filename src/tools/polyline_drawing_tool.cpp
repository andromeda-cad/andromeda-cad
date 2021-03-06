#include "src/geometry/geometry.h"
#include "src/dialogs/symbol_editor/polyline_editor_dialog.h"

#include "polyline_drawing_tool.h"

PolylineDrawingTool::PolylineDrawingTool(QObject *parent) : PolylineToolBase(parent)
{
    setObjectName(TOOL_NAME::DRAW_POLYLINE);
}

void PolylineDrawingTool::finalAction()
{
    if (QApplication::keyboardModifiers() & Qt::ShiftModifier)
    {
        addPoint(polyline_.startPoint());
    }
    else
    {
        addPoint(tool_pos_);
    }

    finish();
}

void PolylineDrawingTool::openEditor()
{
    PolylineEditorDialog dlg;

    dlg.loadSettings( polyline_.encoded() );

    if ( dlg.exec() == QDialog::Accepted )
    {
        AJsonObject settings = dlg.saveSettings();
        polyline_.decode( settings );

        emit updated();
    }
}

bool PolylineDrawingTool::addPoint(QPointF point)
{
    switch (toolState())
    {
    default:
    case TOOL_STATE::POLYLINE_SET_ORIGIN:
        // Set the starting position
        reset();
        setToolState(TOOL_STATE::POLYLINE_ADD_POINT);

        polyline_.addPoint(point);
        break;
    case TOOL_STATE::POLYLINE_ADD_POINT:
        if (polyline_.pointCount() > 2)
        {
            if (AGeometry::PointsAreCoincident(point, polyline_.startPoint()))
            {
                // Close the polygon and finish
                polyline_.close();
                return true;
            }
        }

        if (polyline_.pointCount() > 0)
        {
            if (AGeometry::PointsAreCoincident(point, polyline_.endPoint()))
            {
                return false;
            }
        }
        else
        {
            if (AGeometry::PointsAreCoincident(point, polyline_.startPoint()))
            {
                return false;
            }
        }

        polyline_.addPoint(point);
        break;
    }

    // False indicates that the polygon did not close itself
    return false;
}
