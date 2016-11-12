#include <QPixmap>
#include <QtSvg/QSvgRenderer>
#include <QIcon>
#include <QDebug>

#include "pin_editor.h"

PinEditorDialog::PinEditorDialog(QWidget *parent) : ObjectEditorDialog(parent)
{
    pin_.setUndoEnabled( false );

    ui.setupUi( this );

    setWindowTitle( "Pin Properties" );

    reloadSettings();

    connect(ui.ok, SIGNAL(released()), this, SLOT(accept()));
    connect(ui.cancel, SIGNAL(released()), this, SLOT(reject()));
}

void PinEditorDialog::reloadSettings(void)
{
    // Extract pin data
    pin_.decode(settings_);

    ui.pinLabel->setText(pin_.label());
    ui.pinLength->setValue(pin_.length());
    ui.pinOrientation->setCurrentIndex(pin_.orientation());
}

// Extract the pin settings
AJsonObject PinEditorDialog::saveSettings()
{
    pin_.setLabel(ui.pinLabel->text());
    pin_.setLength(ui.pinLength->value());
    pin_.setOrientation(ui.pinOrientation->currentIndex());

    return pin_.encoded();
}
