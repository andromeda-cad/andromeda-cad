#ifndef TEXT_DRAWING_TOOL_H
#define TEXT_DRAWING_TOOL_H

#include "src/shapes/text_item.h"

#include "tool_base.h"

class TextDrawingTool : public AToolBase
{
    Q_OBJECT

public:
    TextDrawingTool( QObject *parent = 0 );

    virtual void paintTool(QPainter *painter, const QRectF &rect) override;

    virtual void nextAction( void ) override;

    ATextItem *getText( void );

protected:
    ATextItem text_;

    virtual void onToolPosChanged( void ) override;
};

#endif // TEXT_DRAWING_TOOL_H

