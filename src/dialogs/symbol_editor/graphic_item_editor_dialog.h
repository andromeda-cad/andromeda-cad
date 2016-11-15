#ifndef GRAPHIC_ITEM_EDITOR_H
#define GRAPHIC_ITEM_EDITOR_H

#include <QDialog>

#include "src/drawable/drawable_primitive.h"
#include "src/dialogs/object_editor.h"

#include "ui_graphic_item_editor.h"

class GraphicItemEditorDialog : public ObjectEditorDialog
{
    Q_OBJECT

public:
    GraphicItemEditorDialog(QWidget *parent = 0);

public slots:
    virtual AJsonObject saveSettings(void) override;
    virtual void reloadSettings(void) override;

protected:
    ADrawablePrimitive shape_;

    Ui::GraphicItemEditorForm ui;

};

#endif // GRAPHIC_ITEM_EDITOR_H

