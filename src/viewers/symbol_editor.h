#ifndef SYMBOL_EDITOR_H
#define SYMBOL_EDITOR_H

#include "src/shapes/polyline.h"
#include "src/shapes/ellipse.h"

#include "src/tools/polyline_drawing_tool.h"
#include "src/tools/ellipse_drawing_tool.h"
#include "src/tools/rect_drawing_tool.h"
#include "src/tools/pin_drawing_tool.h"
#include "src/tools/text_drawing_tool.h"

#include "src/symbol/schematic_symbol.h"

#include "symbol_viewer.h"

class ASymbolEditor : public ASymbolViewer
{
    Q_OBJECT

public:
    ASymbolEditor(QWidget * parent = 0);

    void addItems(void);

public slots:
    //TODO these are just hacky. To be remove
    void drawText(void)     { startTool(&text_tool_); }
    void drawPin(void)      { startTool(&pin_tool_); }
    void drawRect(void)     { startTool(&rect_tool_); }
    void drawEllipse(void)  { startTool(&ellipse_tool_); }
    void drawPolyline(void) { startTool(&poly_tool_); }

    ASchematicSymbol& symbol(void) { return symbol_; }

    void symbolEdited(void);

    virtual void editItems(void) override;
    virtual void editSingleItem(ADrawableBase *item) override;

protected:
    void keyPressEvent(QKeyEvent *event);

    // Polyline tool
    PolylineDrawingTool poly_tool_;
    RectDrawingTool rect_tool_;
    EllipseDrawingTool ellipse_tool_;
    PinDrawingTool pin_tool_;
    TextDrawingTool text_tool_;

    // Tool callbacks
    void onToolFinished(AToolBase *toolPtr);

    // The symbol being edited
    ASchematicSymbol symbol_;
};

#endif // SYMBOL_EDITOR_H

