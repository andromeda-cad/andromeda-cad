#include "polyline_editor_dialog.h"

PolylineEditorDialog::PolylineEditorDialog(QWidget *parent) : ObjectEditorDialog(parent)
{
    line_.setUndoEnabled(false);

    ui.setupUi( this );

    setWindowTitle( "Polyline Properties" );

    // Default values
    ui.lineThickness->setMinimum( SYMBOL_LINE_WIDTH_MIN );
    ui.lineThickness->setMaximum( SYMBOL_LINE_WIDTH_MAX );
    ui.lineThickness->setValue( SYMBOL_LINE_WIDTH_DEFAULT );

    reloadSettings();

    connect( ui.okButton, SIGNAL( released() ), this, SLOT( accept() ) );
    connect( ui.cancelButton, SIGNAL( released() ), this, SLOT( reject() ) );
}

void PolylineEditorDialog::reloadSettings()
{
    line_.decode( settings_ );

    ui.lineThickness->setValue( line_.lineWidth() );

    switch ( line_.fillStyle() )
    {
    default:
    case ADrawablePrimitive::FILL_NONE:
        ui.fillNone->setChecked( true );
        break;
    case ADrawablePrimitive::FILL_BACKGROUND:
        ui.fillBackground->setChecked( true );
        break;
    case ADrawablePrimitive::FILL_FOREGROUND:
        ui.fillForeground->setChecked( true );
        break;
    }
}

AJsonObject PolylineEditorDialog::saveSettings()
{
    if ( ui.fillNone->isChecked() )
        line_.setFillStyle( ADrawablePrimitive::FILL_NONE );
    else if ( ui.fillBackground->isChecked() )
        line_.setFillStyle( ADrawablePrimitive::FILL_BACKGROUND );
    else if ( ui.fillBackground->isCheckable() )
        line_.setFillStyle( ADrawablePrimitive::FILL_FOREGROUND );

    line_.setLineWidth( ui.lineThickness->value() );

    return line_.encoded();
}
