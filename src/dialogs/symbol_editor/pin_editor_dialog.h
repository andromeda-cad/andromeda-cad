#ifndef PIN_EDITOR_H
#define PIN_EDITOR_H

#include <QDialog>

#include "src/symbol/symbol_pin.h"
#include "src/dialogs/object_editor.h"

#include "ui_pin_editor.h"

//TODO - This could be a base class for a general-purpose object editor dialog
//

class PinEditorDialog : public ObjectEditorDialog
{
    Q_OBJECT

public:
    PinEditorDialog(QWidget *parent = 0);

public slots:
    virtual AJsonObject saveSettings(void) override;
    virtual void reloadSettings(void) override;

protected:
    // Store a local pin to edit
    ASymbolPin pin_;

    Ui::PinEditForm ui;
};

#endif // PIN_EDITOR_H

