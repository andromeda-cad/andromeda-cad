#ifndef PIN_DRAWING_TOOL_H
#define PIN_DRAWING_TOOL_H

#include "src/dialogs/symbol_editor/pin_editor_dialog.h"
#include "src/symbol/symbol_pin.h"

#include "tool_base.h"

class PinDrawingTool : public AToolBase
{
    Q_OBJECT

public:
    PinDrawingTool(QObject *parent = 0);

    virtual void paintTool(QPainter *painter, const QRectF &rect) override;

    virtual void nextAction(void) override;

    ASymbolPin *getPin(void);

protected:
    virtual void onToolPosChanged(void) override;
    virtual void onKeyEvent(QKeyEvent *event) override;

    virtual void openEditor(void) override;

    ASymbolPin pin_;
    PinEditorDialog dialog_;
};

#endif // PIN_DRAWING_TOOL_H

