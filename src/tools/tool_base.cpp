#include "src/layers/layer_defines.h"

#include "tool_base.h"

AToolBase::AToolBase(QObject *parent) : QObject(parent)
{
    setObjectName(TOOL_NAME::BASE);

    defaultPens();
}

void AToolBase::defaultPens()
{
    // Fill brush
    tool_brush_ = QBrush(Qt::NoBrush);

    // Pen for tool outline
    tool_pen_.setColor(DRAWING_TOOL_OUTLINE_COLOR);
    tool_pen_.setWidthF(2.5);
    tool_pen_.setCosmetic(true);
    tool_pen_.setStyle(Qt::DashDotLine);

    hints_pen_.setColor(DRAWING_TOOL_TRACE_LINE_COLOR);
    hints_pen_.setWidthF(2.0);
    hints_pen_.setCosmetic(true);
    hints_pen_.setStyle(Qt::DotLine);
}

void AToolBase::start()
{
    reset();

    onStart();
}

void AToolBase::reset()
{
    setToolState(TOOL_STATE::RESET);

    onReset();

    // Let anyone watching know that the tool has updated
    emit updated();
}

void AToolBase::finish()
{
    setToolState(TOOL_STATE::FINISHED);
    onFinish();
    emit finished();
}

/**
 * @brief AToolBase::cancel
 * Cancel the tool
 */
void AToolBase::cancel()
{
    reset();

    setToolState(TOOL_STATE::INACTIVE);

    onCancel();

    emit cancelled();
}

void AToolBase::paint(QPainter *painter, const QRectF &rect)
{
    if (painter != nullptr)
    {
        paintTool(painter,  rect);
        paintHints(painter, rect);
    }
}

void AToolBase::mouseEvent(QMouseEvent *event, QPointF cursorPos)
{
    if (nullptr == event)
        return;

    if (!isActive())
        return;

    setToolPos(cursorPos);

    switch (event->type())
    {
    case QEvent::MouseButtonPress:
        if (event->button() == Qt::LeftButton)
        {
            nextAction();
        }
        break;
    case QEvent::MouseButtonDblClick:
        if (event->button() == Qt::LeftButton)
        {
            finalAction();
        }
        break;
    default:
        break;
    }

    onMouseEvent(event);
}

void AToolBase::keyEvent(QKeyEvent *event, QPointF cursorPos)
{
    if (nullptr == event)
        return;

    if (!isActive())
        return;

    setToolPos(cursorPos);

    switch (event->type())
    {
    case QEvent::KeyPress:
        switch (event->key())
        {
        case Qt::Key_Return:
        case Qt::Key_Enter:
            nextAction();
            break;
        case Qt::Key_Escape:
            // If the user is in the middle of this tool, reset state
            if (isActive())
            {
                if (tool_state_ == TOOL_STATE::RESET)
                {
                    cancel();
                }
                else
                {
                    reset();
                }
            }
            break;
        default:
            break;
        }
    default:
        break;
    }

    onKeyEvent(event);
}
