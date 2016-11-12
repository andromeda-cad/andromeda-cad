#ifndef ANDROMEDA_VIEW_H
#define ANDROMEDA_VIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QCursor>

#include <QShortcut>

#include "src/tools/tool_base.h"

#include "andromeda_scene.h"

#include <QtOpenGL>

#include <QElapsedTimer>

#include <QMutex>

#define ANDROMEDA_VIEW_MAX_SCALING 100.0f
#define ANDROMEDA_VIEW_MIN_SCALING 0.001f

class AView : public QGraphicsView
{
    Q_OBJECT

public:
    AView(QWidget *parent = 0);

    void setScene(AScene *scene);
    AScene* getScene(void) { return scene_; }

    QRectF mapRectToScene(QRect rect);
    QRect mapRectFromScene(QRectF rect);

    //TODO make these slots

    // Viewport functions
    QPointF getCenterLocation(void);
    QRectF getViewBounds(void);
    QPointF unitsPerPixel(void);

    // Cursor functions
    QPointF cursorPos(void) { return cursor_pos_; }
    QPointF cursorOrigin(void) { return cursorOrigin_; }
    void setCursorPos(QPointF pos, bool panPastEdges = false);
    void moveCursor(QPointF offset, bool panPastEdges = false);
    void moveCursor(double dx, double dy, bool panPastEdges = false);
    void snapMouseToCursor(void);
    void setCursorStyle(unsigned char style);
    unsigned char getCursorStyle(void) { return cursorStyle_; }

    void scroll(QPoint offset);
    void scroll(int dx, int dy);

    // View scaling functions
    double getScalingFactor(void) { return transform().m11(); }
    void setScalingFactor(double scaling);
    void scaleRelative(double scaling);

    // Item deletion
    void deleteItems(QList<QGraphicsItem*> items);
    void deleteSelectedItems(void);

    //TODO - remove this
    void duplicateItems(void);

    // Tool functions
    void addTool(AToolBase *tool);
    bool startTool(AToolBase *tool = nullptr);
    void resetTool(AToolBase *tool = nullptr);
    void stopTool(AToolBase *tool = nullptr);
    bool isToolActive(AToolBase *tool = nullptr);
    bool isToolAvailable(AToolBase *tool = nullptr);

    enum AViewFlags
    {
        VIEW_NO_FLAGS = 0x00,

        // Drawing flags
        VIEW_FLAG_DRAW_OVERLAY = 0x01,
    };

    void setViewFlags(unsigned int flags, bool on = true);
    void clearViewFlags(unsigned int flags);
    bool checkViewFlags(unsigned int flags);

    enum AndromedaCursorStyles
    {
        VIEW_CURSOR_NONE = 0x00,    // No extra cursor is displayed
        VIEW_CURSOR_CROSS_SMALL,    // Draw a small cross
        VIEW_CURSOR_CROSS_LARGE,    // Draw a large cross (to screen boundaries)

        VIEW_CURSOR_NUM_STYLES
    };

public slots:
    void toolUpdated(void);
    void toolFinished(void);
    void toolCancelled(void);

    // Selection functions
    virtual void selectAll(int filter = 0);
    virtual void onSelectionChanged(void) {}

signals:
    // Called when the user cursor changes (in scene coordinates)
    void cursorPositionChanged(QPointF pos);
    void updateStats( QString stats );

protected:
    // UI event callbacks
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

    void paintEvent(QPaintEvent *event) override;

    // Painting functions (drawn in scene coordinates)
    void drawForeground(QPainter *painter, const QRectF &rect) override;
    void drawSelectionMarquee(QPainter *painter, const QRectF &rect);

    // Overlay functions (drawn in viewport coordinates)
    virtual void drawOverlay(QPainter *painter, const QRectF &rect) const;
    virtual void drawCursor(QPainter *painter) const;

    AScene *scene_;

    QPointF cursorOrigin_;  // 'Origin' of the cursor
    QPointF cursor_pos_; // Current location of the cursor

    // Selection marquee (in scene coords)
    QRectF selection_marquee_;

    // Tools
    AToolBase *current_tool_ = nullptr;

    void sendMouseEventToTool(QMouseEvent *event, AToolBase *tool = nullptr);
    void sendKeyEventToTool(QKeyEvent *event, AToolBase *tool = nullptr);

    virtual void onToolUpdated(AToolBase *toolPtr)    { Q_UNUSED(toolPtr); }
    virtual void onToolFinished(AToolBase *toolPtr)   { Q_UNUSED(toolPtr); }
    virtual void onToolCancelled(AToolBase *toolPtr)  { Q_UNUSED(toolPtr); }

    unsigned char cursorStyle_ = VIEW_CURSOR_CROSS_SMALL;     // Cursor style

    unsigned int viewFlags_ = VIEW_NO_FLAGS;    // View flags

    // Mouse panning
    bool mouse_pan_active_ = false;
    void startMousePan();
    void endMousePan();

    // Selection
    bool selection_enabled_ = false;
    bool selection_active_ = false;
    void startSelection(QPointF pos);
    void updateSelection(QPointF pos);
    void finishSelection(QPointF pos);
    void cancelSelection();

    void toggleViewportMode(void);

    // Keyboard shortcuts
    QShortcut *m_shortcut_select_all;

    virtual void configureShortcuts( void );

private:
    QMutex paint_mutex_;
};

#endif // ANDROMEDA_VIEW_H

