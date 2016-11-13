#include <QDebug>
#include <QDialog>

#include "src/dialogs/symbol_editor/pin_editor_dialog.h"

#include "pin_drawing_tool.h"


PinDrawingTool::PinDrawingTool(QObject *parent) : AToolBase(parent)
{
    setObjectName(TOOL_NAME::DRAW_PIN);

    pin_.setUndoEnabled(false);

    pin_.setOpacity(0.5);
}

void PinDrawingTool::paintTool(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    if (nullptr == painter) return;

    painter->save();

    painter->translate(pin_.pos());

    if (isActive())
        pin_.paint(painter, new QStyleOptionGraphicsItem(), nullptr);

    painter->restore();

}


void PinDrawingTool::nextAction()
{
    switch (toolState())
    {
    case TOOL_STATE::RESET:
    case TOOL_STATE::PIN_SET_POS:
        // Positon has been set
        finish();
        break;
    default:
        break;
    }
}

ASymbolPin* PinDrawingTool::getPin()
{
    // Clone the tool pin
    pin_.clone();
    ASymbolPin *pin = pin_.clone();

    return pin;
}

void PinDrawingTool::onToolPosChanged()
{
    pin_.setPos(tool_pos_);
    emit updated();
}

void PinDrawingTool::openEditor()
{
    PinEditorDialog dlg;

    // Encode pin settings and pass to the dialog
    dlg.loadSettings( pin_.encoded() );

    if ( dlg.exec() == QDialog::Accepted )
    {
        // Load the settings from the editor
        AJsonObject settings = dlg.saveSettings();
        pin_.decode( settings );

        emit updated();
    }
}

void PinDrawingTool::onKeyEvent(QKeyEvent *event)
{
    if (nullptr == event) return;

    int mods = (int) event->modifiers();

    switch (event->type())
    {
    case QEvent::KeyPress:
        switch (event->key())
        {
        // R key rotates the pin CCW (Shift modifier rotates CW)
        case Qt::Key_R:
            pin_.rotate(mods & Qt::ShiftModifier);
            emit updated();
            break;
            //TODO - Generecise the "edit" key and make it a shortcut
        /*
         * case Qt::Key_E:
            openEditor();
            break; */
        default:
            break;
        }
        break;
    default:
        break;
    }
}
