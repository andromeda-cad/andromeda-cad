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

bool ObjectEditorDialog::editObject(AndromedaObject *object)
{
    if ( nullptr == object ) return false;

    // Load the object settings into this dialog
    loadSettings( object->encoded() );

    if ( exec() == QDialog::Accepted )
    {
        AJsonObject data = saveSettings();

        object->decode( data );

        return true;
    }

    return false;
}
