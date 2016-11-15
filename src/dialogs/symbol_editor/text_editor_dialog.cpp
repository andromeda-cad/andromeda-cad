#include "text_editor_dialog.h"

TextEditorDialog::TextEditorDialog(QWidget *parent) : ObjectEditorDialog( parent )
{
    text_.setUndoEnabled( false );

    ui.setupUi( this );

    setWindowTitle( tr( "Text Item Properties" ) );

    reloadSettings();

    connect( ui.ok, SIGNAL( released() ), this, SLOT( accept() ) );
    connect( ui.cancel, SIGNAL( released() ), this, SLOT( reject() ) );
}

void TextEditorDialog::reloadSettings()
{
    ui.text->setFocus();

    text_.decode( settings_ );

    // Say "Text" again!
    ui.text->setText( text_.text() );

    switch ( text_.alignment() )
    {
    default:
    case ATextItem::Alignment::LEFT:
        ui.alignLeft->setChecked( true );
        break;
    case ATextItem::Alignment::RIGHT:
        ui.alignRight->setChecked( true );
        break;
    case ATextItem::Alignment::CENTER:
        ui.alignCenter->setChecked( true );
        break;
    }
}

AJsonObject TextEditorDialog::saveSettings()
{
    text_.setText( ui.text->text() );

    if ( ui.alignLeft->isChecked() )
        text_.setAlignment( ATextItem::Alignment::LEFT );
    else if ( ui.alignRight->isChecked() )
        text_.setAlignment( ATextItem::Alignment::RIGHT );
    else
        text_.setAlignment( ATextItem::Alignment::CENTER );

    return text_.encoded();
}

