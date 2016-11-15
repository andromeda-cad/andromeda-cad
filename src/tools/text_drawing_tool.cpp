#include "src/dialogs/symbol_editor/text_editor_dialog.h"

#include "text_drawing_tool.h"

TextDrawingTool::TextDrawingTool(QObject *parent) : AToolBase( parent )
{
    setObjectName( TOOL_NAME::DRAW_TEXT );

    text_.setUndoEnabled( false );

    text_.setText( "Text" );
}

ATextItem* TextDrawingTool::getText()
{
    ATextItem* clone = text_.clone();

    return clone;
}

void TextDrawingTool::openEditor()
{
    if ( dialog_.editObject( &text_ ) )
    {
        emit updated();
    }
}

void TextDrawingTool::paintTool(QPainter *painter, const QRectF &rect)
{
    if ( nullptr == painter ) return;

    Q_UNUSED( rect );

    //if ( !rect.intersects( text_.boundingRect() ) ) return;

    painter->save();

    painter->translate( text_.pos() );
    text_.paint( painter, new QStyleOptionGraphicsItem, nullptr );

    painter->restore();
}

void TextDrawingTool::nextAction()
{
    switch ( toolState() )
    {
    case TOOL_STATE::RESET:
    case TOOL_STATE::TEXT_SET_POS:
        finish();
        break;
    default:
        break;
    }
}

void TextDrawingTool::onToolPosChanged()
{
    text_.setPos( tool_pos_ );
}
