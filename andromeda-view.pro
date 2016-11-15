#-------------------------------------------------
#
# Project created by QtCreator 2016-10-18T15:50:40
#
#-------------------------------------------------

QT       += core gui svg

qtHaveModule(opengl): QT += opengl

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = andromeda-view
TEMPLATE = app


FORMS    += \
    ui/mainwindow.ui \
    ui/dialogs/symbol_editor/pin_editor.ui \
    ui/dialogs/symbol_editor/graphic_item_editor.ui \
    ui/dialogs/symbol_editor/text_item_editor.ui

RESOURCES += \
    resources/fonts.qrc \
    resources/icons.qrc

HEADERS += \
    src/base/andromeda_object.h \
    src/base/object_names.h \
    src/geometry/bounding_box.h \
    src/geometry/geometry.h \
    src/grid/grid.h \
    src/layers/layer_defines.h \
    src/layers/pcb_layers.h \
    src/logging/debug_handler.h \
    src/shapes/ellipse.h \
    src/shapes/polyline.h \
    src/shapes/shape_defines.h \
    src/tools/ellipse_drawing_tool.h \
    src/tools/polyline_drawing_tool.h \
    src/tools/polyline_editing_tool.h \
    src/tools/polyline_tool_base.h \
    src/tools/rect_drawing_tool.h \
    src/tools/tool_base.h \
    src/tools/tool_defines.h \
    src/viewers/andromeda_scene.h \
    src/viewers/andromeda_view.h \
    src/viewers/polyline_tool_base.h \
    src/mainwindow.h \
    src/symbol/schematic_symbol.h \
    src/symbol/symbol_pin.h \
    src/drawable/drawable_base.h \
    src/drawable/drawable_complex.h \
    src/drawable/drawable_primitive.h \
    src/base/andromeda_undo.h \
    src/shapes/object_properties.h \
    src/base/undoable_object_base.h \
    src/base/object_keys.h \
    src/base/object_encoding.h \
    src/base/action_keys.h \
    src/tools/pin_drawing_tool.h \
    src/dialogs/object_editor.h \
    src/shapes/text_item.h \
    src/viewers/symbol_viewer.h \
    src/viewers/symbol_editor.h \
    src/main.h \
    src/dialogs/symbol_editor/pin_editor_dialog.h \
    src/dialogs/symbol_editor/graphic_item_editor_dialog.h \
    src/tools/text_drawing_tool.h \
    src/dialogs/symbol_editor/text_editor_dialog.h

SOURCES += \
    src/base/andromeda_object.cpp \
    src/geometry/bounding_box.cpp \
    src/geometry/geometry.cpp \
    src/grid/grid.cpp \
    src/layers/layer_defines.cpp \
    src/layers/pcb_layers.cpp \
    src/logging/debug_handler.cpp \
    src/shapes/ellipse.cpp \
    src/shapes/polyline.cpp \
    src/tools/ellipse_drawing_tool.cpp \
    src/tools/polyline_drawing_tool.cpp \
    src/tools/polyline_editing_tool.cpp \
    src/tools/polyline_tool_base.cpp \
    src/tools/rect_drawing_tool.cpp \
    src/tools/tool_base.cpp \
    src/viewers/andromeda_scene.cpp \
    src/viewers/andromeda_view.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/symbol/schematic_symbol.cpp \
    src/symbol/symbol_pin.cpp \
    src/drawable/drawable_base.cpp \
    src/drawable/drawable_complex.cpp \
    src/drawable/drawable_primitive.cpp \
    src/base/andromeda_undo.cpp \
    src/base/undoable_object_base.cpp \
    src/base/object_keys.cpp \
    src/base/object_encoding.cpp \
    src/tools/pin_drawing_tool.cpp \
    src/dialogs/object_editor.cpp \
    src/shapes/text_item.cpp \
    src/viewers/symbol_editor.cpp \
    src/viewers/symbol_viewer.cpp \
    src/dialogs/symbol_editor/pin_editor_dialog.cpp \
    src/dialogs/symbol_editor/graphic_item_editor_dialog.cpp \
    src/tools/text_drawing_tool.cpp \
    src/dialogs/symbol_editor/text_editor_dialog.cpp

DISTFILES +=
