#ifndef ANDROMEDA_SCENE_H
#define ANDROMEDA_SCENE_H

#include <QGraphicsScene>
#include <QColor>
#include <QPointF>
#include <QPainter>
#include <QPen>

#include <stdint.h>

#include "src/grid/grid.h"
#include "src/layers/layer_defines.h"
#include "src/shapes/shape_defines.h"

class AScene : public QGraphicsScene
{
    Q_OBJECT

   // Q_PROPERTY(uint64_t layerMask READ name WRITE setName NOTIFY nameChanged)

public:
    AScene(QObject *parent = 0);

    // Background functions
    QColor getBackgroundColor() { return bg_color_; }
    void drawBackground(QPainter *painter, const QRectF &rect) override;

    // Axis functions
    bool getAxesEnabled() { return draw_axes_; }

    // Grid functions
    void setGrid(AGrid grid) { grid_ = grid; }
    AGrid getGrid() { return grid_; }

    // Layer functions
    int getLayerDisplayMode() { return layerDisplayMode_; }

    bool checkLayer(int layerId);

    int getCurrentLayer() { return current_layer_; }

    uint64_t getLayerMask() { return layerMask_; }

public slots:
    void setBackgroundColor(QColor c) { bg_color_ = c;}
    void setAxesEnabled(bool draw) { draw_axes_ = draw; }
    void setLayerDisplayMode(int mode);
    void setCurrentLayer(int layer);
    void setLayerMask(uint64_t layers);
    void showLayers(uint64_t layerMask, bool show = true);
    void hideLayers(uint64_t layerMask);

    void showLayer(int layerId, bool show = true);
    void hideLayer(int layerId);

    void showAllLayers() { setLayerMask((uint64_t) LAYER_MASK::NONE); }
    void hideAllLayers() { setLayerMask((uint64_t) LAYER_MASK::ALL); }
    void setItemDepth(QGraphicsItem *item, int layer, bool flip = false);

protected:
    void init();

    QColor bg_color_ = QColor(0xFF,0xFF,0xFF);   // Background color for the scene
    bool draw_axes_= true;              // Flag for displaying axes

    QPen axis_pen_;     // Pen object for drawing the axes
    QPen grid_pen_;     // Pen object for drawing the grid

    AGrid grid_;    // Grid object

    int layerDisplayMode_ = (int) LAYER_MODE::SHOW_ALL;     // How to display multiple layers

    uint64_t layerMask_ = (uint64_t) LAYER_MASK::ALL;       // Which layers are currently visible

    int current_layer_ = (int) LAYER_ID::TOP;     // Which layer is currently selected (top)

signals:
    void layerSelectionChanged(uint64_t layers);

};


#endif // ANDROMEDA_SCENE_H

