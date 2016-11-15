#ifndef ELLIPSE_DRAWING_TOOL
#define ELLIPSE_DRAWING_TOOL

#include "src/shapes/ellipse.h"
#include "src/dialogs/symbol_editor/graphic_item_editor_dialog.h"

#include "tool_base.h"

class EllipseDrawingTool : public AToolBase
{
    Q_OBJECT

public:
    EllipseDrawingTool(QObject *parent = 0);

    void paintTool(QPainter *painter, const QRectF &rect) override;
    void paintHints(QPainter *painter, const QRectF &rect) override;

    void setCenter(QPointF point) { start_pos_ = point; }

    virtual void getEllipse(AEllipse &ellipse);

    void nextAction(void);
    virtual void openEditor(void) override;

protected:
    AEllipse ellipse_;

    GraphicItemEditorDialog dialog_;

    QPointF start_pos_;

    void onToolPosChanged(void);

    QRectF getEllipseRect(void);
};

#endif // ELLIPSE_DRAWING_TOOL

