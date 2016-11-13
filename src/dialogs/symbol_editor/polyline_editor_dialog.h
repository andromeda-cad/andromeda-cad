#ifndef POLYLINE_EDITOR_H
#define POLYLINE_EDITOR_H

#include <QDialog>

#include "src/shapes/polyline.h"
#include "src/dialogs/object_editor.h"

#include "ui_polygon_editor.h"

class PolylineEditorDialog : public ObjectEditorDialog
{
    Q_OBJECT

public:
    PolylineEditorDialog(QWidget *parent = 0);

public slots:
    virtual AJsonObject saveSettings(void) override;
    virtual void reloadSettings(void) override;

protected:
    APolyline line_;

    Ui::PolylineEditForm ui;

};

#endif // POLYLINE_EDITOR_H

