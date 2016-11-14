#ifndef OBJECT_EDITOR_H
#define OBJECT_EDITOR_H

#include <QDialog>

#include "src/base/object_encoding.h"

#include "src/base/andromeda_object.h"

class ObjectEditorDialog : public QDialog
{
    Q_OBJECT

public:
    ObjectEditorDialog(QWidget *parent = 0);

public slots:
    void loadSettings(AJsonObject settings);

    bool editObject( AndromedaObject *object );

    virtual AJsonObject saveSettings(void) = 0;

    // Update the stored parameters
    virtual void reloadSettings(void) {}

protected:
    // A copy of the settings passed to this window
    AJsonObject settings_;
};

#endif // OBJECT_EDITOR_H

