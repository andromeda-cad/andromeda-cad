#include "object_editor.h"

ObjectEditorDialog::ObjectEditorDialog(QWidget *parent) : QDialog(parent)
{
}

void ObjectEditorDialog::loadSettings(AJsonObject settings)
{
    // Make a copy of the settings
    settings_ = settings;

    reloadSettings();
}
