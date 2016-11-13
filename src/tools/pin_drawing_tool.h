#ifndef PIN_DRAWING_TOOL_H
#define PIN_DRAWING_TOOL_H

#include "src/symbol/symbol_pin.h"

#include "tool_base.h"

class PinDrawingTool : public AToolBase
{
    Q_OBJECT

public:
    PinDrawingTool(QObject *parent = 0);

    void paintTool(QPainter *painter, const QRectF &rect);

    void nextAction(void);

    ASymbolPin *getPin(void);

protected:
    virtual void onToolPosChanged(void);
    virtual void onKeyEvent(QKeyEvent *event);

    virtual void openEditor(void) override;

    ASymbolPin pin_;
};

#endif // PIN_DRAWING_TOOL_H

