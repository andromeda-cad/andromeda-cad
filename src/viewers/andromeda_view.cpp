#include <QApplication>
#include <QScrollBar>
#include <QGraphicsItem>
#include <QDebug>
#include <QTime>

#include <QProgressDialog>

#include "src/grid/grid.h"


#include "andromeda_view.h"
#include "src/drawable/drawable_base.h"

AView::AView(QWidget *parent) : QGraphicsView(parent)
{
    setMouseTracking(true);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    setRenderHint(QPainter::Antialiasing);
    //setRenderHint(QPainter::HighQualityAntialiasing);
    setRenderHint(QPainter::TextAntialiasing);

    setDragMode(QGraphicsView::RubberBandDrag);

    setOptimizationFlag(QGraphicsView::DontAdjustForAntialiasing);
    //setOptimizationFlags(QGraphicsView::DontSavePainterState);
    //setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    //setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    // Add a default scene
    setScene(new AScene());

    connect(scene_, SIGNAL(selectionChanged()), this, SLOT(onSelectionChanged()));

    //setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
}

void AView::setScene(AScene *scene)
{
    scene_ = scene;

    QGraphicsView::setScene(scene);
}

void AView::deleteItems(QList<QGraphicsItem *> items)
{
    if (nullptr == scene_) return;

    QProgressDialog dlg;

    dlg.setMinimum(0);
    dlg.setMaximum(items.count()/100);

    dlg.setWindowTitle("Deleting " + QString::number(items.count()) + " items");

    //dlg.show();

    scene_->blockSignals(true);
    blockSignals(true);

    QElapsedTimer t;

    t.start();

    int count = 0;

    for (int i=0;i<items.count();i++)
    {
        if (items[i] == nullptr) continue;

        if (items[i]->scene() != scene_) continue;

        //items[i]->setSelected(false);

        scene_->removeItem(items[i]);


        count = (count + 1) % 100;

        if (count == 0)
        {
            //dlg.setValue(dlg.value()+1);
            //QApplication::processEvents();
        }
    }

    //dlg.cancel();

    scene_->blockSignals(false);
    blockSignals(false);

    update();

    qDebug() << "Deleting" << items.count() << "items took" << t.elapsed() << "ms";
}

void AView::deleteSelectedItems()
{
    if (nullptr == scene_) return;

    deleteItems(scene_->selectedItems());
}

void AView::duplicateItems()
{
    QList<QGraphicsItem*> items = scene_->selectedItems();

    foreach (QGraphicsItem *item, items)
    {
        // Cast to an AndromedaObject
        AndromedaObject *obj = qgraphicsitem_cast<ADrawableBase*>(item);

        if (nullptr == obj) continue;

        qDebug() << obj->encodedString();
    }
}

/**
 * @brief AView::setCursorPos
 * Set the position of the cursor (in scene coordinates)
 * @param pos
 */
void AView::setCursorPos(QPointF pos, bool panPastEdges)
{
    double grid = getScene()->getGrid().getMajorTick();

    pos = AGrid::mapToGrid(pos, QPointF(grid,grid));

    if ((pos.x() == cursor_pos_.x()) && (pos.y() == cursor_pos_.y())) return;

    if (panPastEdges)
    {
        // Check if the cursor has moved outside the screen bounds
        QRectF view = getViewport();

        double dx = 0;
        double dy = 0;

        if (pos.x() < view.left())
            dx = view.left() - pos.x();
        else if (pos.x() > view.right())
            dx = view.right() - pos.x();

        if (pos.y() < view.top())
            dy = view.top() - pos.y();
        else if (pos.y() > view.bottom())
            dy = view.bottom() - pos.y();

        scroll(dx,dy);
    }

    // Update old cursor pos
    scene_->update(cursor_pos_.x() - 25,
                   cursor_pos_.y() - 25,
                   50,
                   50);

    cursor_pos_ = pos;



    emit cursorPositionChanged(cursor_pos_);

    // Repaint only the part of the scene where the
    //getScene()->update();

    scene_->update(cursor_pos_.x() - 25,
                   cursor_pos_.y() - 25,
                   50,
                   50);
}

void AView::moveCursor(QPointF offset, bool panPastEdges)
{
    setCursorPos(cursor_pos_ + offset, panPastEdges);
}

void AView::moveCursor(double dx, double dy, bool panPastEdges)
{
    moveCursor(QPointF(dx,dy), panPastEdges);
}

/**
 * @brief AView::snapMouseToCursor
 *
 * Move the mouse pointer to the location of the scene cursor
 */
void AView::snapMouseToCursor()
{
    // If the cursorPos is off screen, focus view on that point
    if (!sceneRect().contains(cursor_pos_))
    {
        centerOn(cursor_pos_);
    }

    QPoint pos = mapToGlobal(mapFromScene(cursor_pos_));

    cursor().setPos(pos);
}

void AView::scroll(QPoint offset)
{
    scroll(offset.x(), offset.y());
}

/**
 * @brief AView::scroll
 * Adjust the scroll bar position by a given amount
 * @param dx
 * @param dy
 */
void AView::scroll(int dx, int dy)
{
    bool update = false;

    if (dx != 0)
    {
        update = true;
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - dx);
    }
    if (dy != 0)
    {
        update = true;
        verticalScrollBar()->setValue(verticalScrollBar()->value() - dy);
    }

    if (update)
        scene()->update();


}

void AView::keyPressEvent(QKeyEvent *event)
{
    if (nullptr == event) return;

    bool accepted = true;

    double offset = getScene()->getGrid().getMajorTick();

    // High priority keys

    switch (event->key())
    {
    case Qt::Key_Escape:
        if (selection_active_)
            cancelSelection();
        break;
    case Qt::Key_Space:
        // Center the screen at the cursor location
        if (event->modifiers() == Qt::ControlModifier)
        {
            centerOn(cursor_pos_);
        }
        // Reset the cursor origin to the current cursor position
        else
        {
            cursorOrigin_ = cursor_pos_;
            emit cursorPositionChanged(cursor_pos_);
        }

        snapMouseToCursor();
        break;
    // Move the cursor left
    case Qt::Key_Left:
        moveCursor(-offset,0,true);
        snapMouseToCursor();
        break;
    // Move the cursor right
    case Qt::Key_Right:
        moveCursor(offset,0,true);
        snapMouseToCursor();
        break;
    // Move the cursor up
    case Qt::Key_Up:
        moveCursor(0,-offset,true);
        snapMouseToCursor();
        break;
    // Move the cursor down
    case Qt::Key_Down:
        moveCursor(0,offset,true);
        snapMouseToCursor();
        break;
    default:
        break;
    }

    // Forward the event through to the selected tool
    sendKeyEventToTool(event);

    switch (event->key())
    {

    case Qt::Key_C: //TODO - remove this, just a test
        setCursorStyle(getCursorStyle() == VIEW_CURSOR_CROSS_LARGE ? VIEW_CURSOR_CROSS_SMALL : VIEW_CURSOR_CROSS_LARGE);
        scene_->update();
        break;

    default:
        accepted = false;
        break;
    }

    if (accepted)
    {
        event->accept();
    }
    else
    {
        QGraphicsView::keyPressEvent(event);
    }
}

void AView::keyReleaseEvent(QKeyEvent *event)
{
    sendKeyEventToTool(event);

    QGraphicsView::keyReleaseEvent(event);
}

/**
 * @brief AView::wheelEvent
 *
 * Called when the mouse wheel is scrolled and this widget has mouse focus
 * @param event
 */
void AView::wheelEvent(QWheelEvent *event)
{
    if (scene_ == NULL || nullptr == event) return;

    float zoom = (float) event->delta() * 0.01f;

    // Account for 'negative' zoom
    if (zoom < 0)
        zoom = -1.0 / zoom;

    scaleRelative(zoom);

    // Re-move the cursor to the mouse position
    QPoint mousePos = mapFromGlobal(cursor().pos());

    setCursorPos(mapToScene(mousePos));
}

void AView::mousePressEvent(QMouseEvent *event)
{
    if (event == NULL || nullptr == scene_) return;

    QPointF scenePos = mapToScene(event->pos());

    setCursorPos(scenePos);

    sendMouseEventToTool(event);

    switch (event->button())
    {
    case Qt::MiddleButton:
        setCursor(QCursor(Qt::OpenHandCursor));
        break;
    case Qt::LeftButton:
        startPos_ = cursor_pos_;

        if (!isToolActive())
        {
            startSelection();
        }
        break;

    default:
        break;
    }
}

void AView::mouseDoubleClickEvent(QMouseEvent *event)
{
    sendMouseEventToTool(event);
}

void AView::mouseReleaseEvent(QMouseEvent *event)
{
    if (scene_ == NULL || nullptr == event) return;

    // Left mouse button is used for selection
    if (mouse_pan_active_ &&  event->button() == Qt::MiddleButton)
    {
        endMousePan();
    }
    else if (selection_active_ && event->button() == Qt::LeftButton)
    {
        finishSelection();
    }
    else
    {
        sendMouseEventToTool(event);
    }
}


void AView::mouseMoveEvent(QMouseEvent *event)
{
    static QPoint lastMousePos;

    if (getScene() == NULL || nullptr == event) return;

    // Grab the mouse position
    QPoint mousePos = event->pos();

    setCursorPos(mapToScene(mousePos));

    // Check for panning event
    if (event->buttons() & Qt::MiddleButton)
    {
        if (!mouse_pan_active_)
        {
            startMousePan();
        }
        else
        {
            QPoint delta = mousePos - lastMousePos;
            scroll(delta);
        }

        // Set the panning flag
        lastMousePos = mousePos;

        return;
    }

    endMousePan();

    // Forward the event through to the active tool
    sendMouseEventToTool(event);

    QGraphicsView::mouseMoveEvent(event);
}

void AView::startMousePan()
{
    mouse_pan_active_ = true;
    setCursor(QCursor(Qt::ClosedHandCursor));
}

void AView::endMousePan()
{
    mouse_pan_active_ = false;
    setCursor(QCursor(Qt::ArrowCursor));
}

/*
void AView::drawBackground(QPainter *painter, const QRectF &rect)
{

}
*/

/**
 * @brief AView::drawForeground
 * Custom foreground painting (AFTER the scene is painted)
 * Painting is performed in scene coordinates
 * @param painter
 * @param rect
 */
void AView::drawForeground(QPainter *painter, const QRectF &rect)
{
    if (nullptr == painter) return;

    // Draw the active tool
    if (isToolActive())
    {
        current_tool_->paint(painter, rect);
    }

    else if (selection_active_)
    {
        drawSelectionMarquee(painter, rect);
    }
}

void AView::drawSelectionMarquee(QPainter *painter, const QRectF &rect)
{
    if (nullptr == painter) return;

    QRectF selection = getSelectionMarquee();

    // Don't paint if off-screen
    if (!selection.intersects(rect)) return;

    QPen marqueePen(QColor(0,255,200,200));

    bool crossing = selection.width() < 0;

    marqueePen.setCapStyle(Qt::RoundCap);
    marqueePen.setJoinStyle(Qt::RoundJoin);
    marqueePen.setWidth(1);
    marqueePen.setStyle(crossing ? Qt::DashLine : Qt::SolidLine);

    marqueePen.setCosmetic(true);

    QBrush marqueeBrush(crossing? QColor(0,120,50,50) : QColor(0,50,120,50));

    painter->setPen(marqueePen);
    painter->setBrush(marqueeBrush);

    painter->drawRect(selection.normalized());
}

QRectF AView::getSelectionMarquee()
{
    return QRectF(startPos_.x(),
                  startPos_.y(),
                  cursor_pos_.x() - startPos_.x(),
                  cursor_pos_.y() - startPos_.y());
}

void AView::paintEvent(QPaintEvent *event)
{
#define REDRAW_TIMER

    if (nullptr == event) return;

    QTime time;
    time.start();

    // First perform scene painting
    QGraphicsView::paintEvent(event);

    int elapsed = time.elapsed();

    // Grab the painter
    QPainter painter(viewport());

    //TODO - draw a different cursor if the user is using a tool or just navigating
    // Draw the cursor
    //if (isToolActive())
    drawCursor(&painter, event->rect());

    // Draw the overlay
    if (checkViewFlags(VIEW_FLAG_DRAW_OVERLAY))
        drawOverlay(&painter, event->rect());

    painter.setPen(QPen(QColor(255,0,255)));

    // Draw repaint time
#ifdef REDRAW_TIMER
    painter.fillRect(QRectF(0,0,50,20), QColor(255,255,200));
    painter.drawText(QRectF(0,0,50,20), QString::number(elapsed) + "ms");
#endif
}

void AView::drawOverlay(QPainter *painter, QRect rect)
{
    // Re-implement this to draw an overlayover the scene

    Q_UNUSED(painter);
    Q_UNUSED(rect);
}

void AView::drawCursor(QPainter *painter, QRect rect)
{
    if (nullptr == painter) return;

    QPoint viewPos = mapFromScene(cursor_pos_);
    int x = viewPos.x();
    int y = viewPos.y();

    QPen p;
    p.setWidth(1);

    painter->setPen(p);

    switch (cursorStyle_)
    {
    default:
    case VIEW_CURSOR_NONE:
        return;

    // Draw a small cross at the cursor position
    case VIEW_CURSOR_CROSS_SMALL:
#define CURSOR 10
        // Is the cursor position in view?
        if ((viewPos.x() > -CURSOR) &&
            (viewPos.x() < (width() + CURSOR)) &&
            (viewPos.y() > -CURSOR) &&
            (viewPos.y() < (height() + CURSOR)))
        {
            painter->drawLine(x-CURSOR,y,x+CURSOR,y);
            painter->drawLine(x,y-CURSOR,x,y+CURSOR);
        }
        break;

    case VIEW_CURSOR_CROSS_LARGE:

        // Draw horizontal line
        painter->drawLine(rect.left() - 1,
                          y,
                          rect.right() + 1,
                          y);

        // Draw vertical line
        painter->drawLine(x,
                          rect.top() - 1,
                          x,
                          rect.bottom() + 1);

        break;
    }
}

/**
 * @brief AView::getCenterLocation
 * @return the center of the viewport (in scene coordinates)
 */
QPointF AView::getCenterLocation()
{
    return mapToScene(width()/2,height()/2);
}

/**
 * @brief AView::getViewport
 * @return the viewport rectangle in scene coordinates
 */
QRectF AView::getViewport()
{
    return QRectF(
                mapToScene(0,0),
                mapToScene(width()-verticalScrollBar()->width()-1, height()-horizontalScrollBar()->height()-1)
                );
}

/**
 * @brief AView::unitsPerPixel
 * @return <x,y> mapping of how many internal units correspond to each visible pixel
 */
QPointF AView::unitsPerPixel()
{
    QRectF scene = getViewport();

    return QPointF(scene.width() / width(), scene.height() / height());
}

/**
 * @brief AView::setScalingFactor
 * @param scaling is the desired scaling factor
 */
void AView::setScalingFactor(double scaling)
{
    if (scaling <= 0) return;

    if (scaling > ANDROMEDA_VIEW_MAX_SCALING) scaling = ANDROMEDA_VIEW_MAX_SCALING;
    if (scaling < ANDROMEDA_VIEW_MIN_SCALING) scaling = ANDROMEDA_VIEW_MIN_SCALING;

    // Compensate for the current scaling
    scaling /= getScalingFactor();

    scale(scaling, scaling);
}

/**
 * @brief AView::scaleRelative
 * Scale the view by a specified amount relative to the current scaling
 * @param scaling
 */
void AView::scaleRelative(double scaling)
{
    setScalingFactor(getScalingFactor() * scaling);
}

void AView::sendMouseEventToTool(QMouseEvent *event, AToolBase *tool)
{
    if (nullptr == event)
        return;

    if (nullptr == tool)
        tool = current_tool_;

    // Still null?
    if (nullptr == tool)
        return;

    tool->mouseEvent(event, cursorPos());
}

void AView::sendKeyEventToTool(QKeyEvent *event, AToolBase *tool)
{
    if (nullptr == event)
        return;

    if (nullptr == tool)
        tool = current_tool_;

    // Still null?
    if (nullptr == tool)
        return;

    tool->keyEvent(event, cursorPos());
}

void AView::addTool(AToolBase *tool)
{
    if (nullptr == tool)
        return;

    connect(tool, SIGNAL(updated()),    this, SLOT(toolUpdated()));
    connect(tool, SIGNAL(finished()),   this, SLOT(toolFinished()));
    connect(tool, SIGNAL(cancelled()),  this, SLOT(toolCancelled()));
}

void AView::toolUpdated()
{
    AToolBase *tool = qobject_cast<AToolBase*>(QObject::sender());

    if (nullptr == tool)
        return;

    // Force a scene redraw
    scene_->update();

    repaint();
    //onToolUpdated(tool);
}

void AView::toolCancelled()
{
    AToolBase *tool = qobject_cast<AToolBase*>(QObject::sender());

    if (tool != nullptr)
        onToolCancelled(tool);
}

void AView::toolFinished()
{
    // Did a tool call this?
    AToolBase *tool = qobject_cast<AToolBase*>(QObject::sender());

    if (tool != nullptr)
    {
        onToolFinished(tool);
        resetTool(tool);
    }
}

bool AView::startTool(AToolBase *tool)
{
    if (nullptr == tool)
        tool = current_tool_;

    // Still null?
    if (nullptr == tool)
        return false;

    // Stop the current tool
    stopTool();

    current_tool_ = tool;

    tool->start();

    tool->setToolPos(cursorPos());

    return true;
}

/**
 * @brief AView::stopTool
 * Stop the tool (place in TOOL_STATE::INACTIVE mode)
 * @param tool is a pointer to the tool. If nullptr is supplied, current tool is used
 */
void AView::stopTool(AToolBase *tool)
{
    if (nullptr == tool)
        tool = current_tool_;

    if (tool != nullptr)
    {
        tool->cancel();
    }
}

/**
 * @brief AView::resetTool
 * Reset the state of the tool
 * @param tool is a pointer to the tool. If nullptr is supplied, current tool is used
 */
void AView::resetTool(AToolBase *tool)
{
    if (nullptr == tool)
        tool = current_tool_;

    if (tool != nullptr)
    {
        tool->reset();
    }

}

bool AView::isToolAvailable(AToolBase *tool)
{
    if (nullptr == tool)
        tool = current_tool_;

    return tool != nullptr;
}

bool AView::isToolActive(AToolBase *tool)
{
    if (nullptr == tool)
        tool = current_tool_;

    if (!isToolAvailable(tool))
        return false;

    return tool->isActive();
}

void AView::setViewFlags(unsigned int flags, bool on)
{
    if (on)
    {
        viewFlags_ |= flags;
    }
    else
    {
        viewFlags_ &= ~flags;
    }
}

void AView::clearViewFlags(unsigned int flags)
{
    setViewFlags(flags, false);
}

bool AView::checkViewFlags(unsigned int flags)
{
    return (viewFlags_ & flags) > 0;
}

void AView::setCursorStyle(unsigned char style)
{
    if (style < VIEW_CURSOR_NUM_STYLES)
    {
        cursorStyle_ = style;
    }
}

void AView::startSelection()
{
    selection_active_ = true;
}

void AView::cancelSelection()
{
    selection_active_ = false;
}

void AView::finishSelection()
{
    if (selection_active_)
    {
        int mods = (int) QApplication::keyboardModifiers();

        QRectF selection = getSelectionMarquee();

        QPointF pixels = unitsPerPixel();

        // Ignore 'small' selections
        bool validSelection = ((qAbs(selection.width()  / pixels.x()) > 5) &&
                               (qAbs(selection.height() / pixels.y()) > 5));

        // Rectangular selection
        if (validSelection)
        {
            QElapsedTimer t;

            t.start();

            QList<QGraphicsItem*> items;

            scene_->blockSignals(true);
            blockSignals(true);

            // Selection drawn left-to-right requires full selection
            if (selection.width() > 0)
            {
                items = scene_->items(selection, Qt::ContainsItemShape);
            }
            else
            {
                items = scene_->items(selection.normalized(), Qt::IntersectsItemShape);
            }

            bool select = true;


            if (mods & Qt::ControlModifier)
            {
                select = (mods & Qt::ShiftModifier) == 0;
            }
            else
            {
                scene_->clearSelection();
            }

            for (int i=0;i<items.count();i++)
            {
                if (items[i] == nullptr) continue;

                items[i]->setSelected(select);
            }

            scene_->blockSignals(false);
            blockSignals(false);

            update();

            qDebug() << "Selecting" << items.count() << "items took" << t.elapsed() << "ms";
        }
        // Point Selection
        else
        {
            QGraphicsItem *item = scene_->itemAt(cursor_pos_, QTransform());

            // NO item at location, de-select all items
            if (nullptr == item)
            {
                scene_->clearSelection();
            }
            // Toggle selection with control modifier
            else if (mods & Qt::ControlModifier)
            {
                item->setSelected(!item->isSelected());
            }
            // Otherwise, clear selection and select this one item
            else
            {
                scene_->clearSelection();
                item->setSelected(true);
            }

            scene_->update();
        }

        cancelSelection();
    }
}
