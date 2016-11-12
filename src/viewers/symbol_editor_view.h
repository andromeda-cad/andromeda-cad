#ifndef SYMBOL_EDITOR_VIEW_H
#define SYMBOL_EDITOR_VIEW_H

#include "src/shapes/polyline.h"
#include "src/shapes/ellipse.h"

#include "src/tools/polyline_drawing_tool.h"
#include "src/tools/ellipse_drawing_tool.h"
#include "src/tools/rect_drawing_tool.h"
#include "src/tools/pin_drawing_tool.h"

#include "src/symbol/schematic_symbol.h"

#include "andromeda_view.h"

class SymbolEditorView : public AView
{
    Q_OBJECT

public:
    SymbolEditorView(QWidget * parent = 0);

    void addItems(void);

public slots:
    //TODO these are just hacky. To be remove
    void drawRect(void)     { startTool(&rect_tool_); }
    void drawEllipse(void)  { startTool(&ellipse_tool_); }
    void drawPolyline(void) { startTool(&poly_tool_); }

    ASchematicSymbol& symbol(void) { return symbol_; }

protected:
    void keyPressEvent(QKeyEvent *event);

    // Polyline tool
    PolylineDrawingTool poly_tool_;
    RectDrawingTool rect_tool_;
    EllipseDrawingTool ellipse_tool_;
    PinDrawingTool pin_tool_;

    // Tool callbacks
    void onToolFinished(AToolBase *toolPtr);

    // The symbol being edited
    ASchematicSymbol symbol_;
};

#endif // SYMBOL_EDITOR_VIEW_H

