#ifndef TEXT_EDITOR_DIALOG_H
#define TEXT_EDITOR_DIALOG_H

#include <QDialog>

#include "src/shapes/text_item.h"
#include "src/dialogs/object_editor.h"

#include "ui_text_item_editor.h"

class TextEditorDialog : public ObjectEditorDialog
{
    Q_OBJECT

public:
    TextEditorDialog(QWidget *parent = 0);

public slots:
    virtual AJsonObject saveSettings(void) override;
    virtual void reloadSettings(void) override;

protected:
    ATextItem text_;

    Ui::TextItemEditorForm ui;
};

#endif // TEXT_EDITOR_DIALOG_H

