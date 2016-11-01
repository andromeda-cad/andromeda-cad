#include "polyline_editing_tool.h"

PolylineEditingTool::PolylineEditingTool(QObject *parent) : AToolBase(parent)
{
    setObjectName(TOOL_NAME::EDIT_POLYLINE);
}
