#include <QDebug>
#include <QGraphicsItem>

#include "andromeda_scene.h"

AScene::AScene(QObject *parent) : QGraphicsScene(parent)
{
    init();
}

void AScene::init()
{
    axis_pen_.setColor(QColor(150,150,200,200));
    axis_pen_.setWidth(2);
    axis_pen_.setCapStyle(Qt::RoundCap);
    axis_pen_.setJoinStyle(Qt::RoundJoin);
    axis_pen_.setCosmetic(true);

    grid_pen_.setColor(QColor(150,150,150,200));
    grid_pen_.setWidthF(1.5);
    grid_pen_.setCapStyle(Qt::RoundCap);
    grid_pen_.setJoinStyle(Qt::RoundJoin);
    grid_pen_.setCosmetic(true);

    setMinimumRenderSize(0.5);

    //setItemIndexMethod(QGraphicsScene::NoIndex);
    //setBspTreeDepth(20);
}

void AScene::setLayerDisplayMode(int mode)
{
    layerDisplayMode_ = mode;
}

void AScene::setCurrentLayer(int layer)
{
    current_layer_ = layer;
}

/**
 * @brief AScene::checkLayer
 * Check if the provided layer is visible in the scene layer selection
 * @param layerId
 * @return
 */
bool AScene::checkLayer(int layerId)
{
    // The layer mask accounts for 64 unique layers
    // Any layers outside the maskable range are for display only and are ALWAYS on
    if ((layerId < (int) LAYER_ID::BOTTOM)|| (layerId > (int) LAYER_ID::TOP))
    {
        return true;
    }

    else if (layerId == (int) LAYER_ID::INVISIBLE)
    {
        return false;
    }

    uint64_t layer = LayerIdToMask(layerId);

    return (layerMask_ & layer) > 0;
}

/**
 * @brief AScene::setLayerMask
 * Force visibility of the given layer mask
 * @param selection
 */
void AScene::setLayerMask(uint64_t selection)
{
    layerMask_ = selection;

    /*
    emit layerSelectionChanged(layerMask_);
    int8_t itemLayer;

    foreach (QGraphicsItem *item, items())
    {
        if (nullptr == item) return;

        itemLayer = getItemLayer(item);

        // Check if the item is on a visible layer
        if (checkLayer(itemLayer))
        {
            item->setVisible(true);
            setItemDepth(item, itemLayer);
        }
        else
        {
            item->setVisible(false);
        }
    }
    */
}

/**
 * @brief AScene::showLayers
 * @param layers
 * @param show
 */
void AScene::showLayers(uint64_t layerMask, bool show)
{
    if (show)
    {
        setLayerMask(layerMask_ | layerMask);
    }
    else
    {
        setLayerMask(layerMask_ & ~layerMask);
    }
}

void AScene::hideLayers(uint64_t layerMask)
{
    showLayers(layerMask, false);
}

void AScene::showLayer(int layerId, bool show)
{
    showLayers(LayerIdToMask(layerId), show);
}

void AScene::hideLayer(int layerId)
{
    showLayer(layerId, false);
}

void AScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    if (nullptr == painter) return;

    painter->fillRect(rect, bg_color_);

    if (draw_axes_)
    {
        painter->setPen(axis_pen_);

        double x = grid_.getOrigin().x();
        double y = grid_.getOrigin().y();

        // Draw vertical axis
        if ((rect.left() <= x) && (rect.right() >= x))
        {
            painter->drawLine(x, rect.top()-1, x, rect.bottom()+1);
        }

        // Draw horizontal axis
        if ((rect.top() <= y) && (rect.bottom() >= y))
        {
            painter->drawLine(rect.left()-1, y, rect.right()+1, y);
        }
    }

    double grid = grid_.getMajorTick();

    // Limit the number of grids that will be drawn on the screen
    while ((rect.width() > (50 * grid)) || (rect.height() > (50 * grid)))
    {
        grid *= 2;
    }

    painter->setPen(grid_pen_);

    long int x_min = (long int) (rect.left() / grid) - 1;
    long int x_max = (long int) (rect.right() / grid) + 1;

    long int y_min = (long int) (rect.top() / grid) - 1;
    long int y_max = (long int) (rect.bottom() / grid) + 1;

    /* Draw line grid
    // Draw vertical grid lines
    for (long int i=x_min; i<x_max; i++)
    {
        if (i == 0) continue; // Skip major axis

        painter->drawLine(i*grid, rect.top()-1, i*grid, rect.bottom()+1);

    }

    // Draw horizontal grid lines
    for (long int j=y_min; j<y_max; j++)
    {
        if (j == 0) continue;

        painter->drawLine(rect.left()-1, j*grid, rect.right()+1, j*grid);
    }
    */

    for (long int i=x_min;i<x_max;i++)
    {
        for (long int j=y_min;j<y_max;j++)
        {
            painter->drawPoint(i*grid, j*grid);
        }
    }
}

/**
 * @brief AScene::setItemDepth
 * Set the Z-Order of a given item, based on it's logical layer assignment
 * @param item is a pointer to the item
 * @param layer is the item's logical layer
 * @param flip determines whether the scene view is 'flipped' or not
 */
void AScene::setItemDepth(QGraphicsItem *item, int layer, bool flip)
{
    if (nullptr == item) return;

    // If the layer is above the top layer, ignore
    if ((layer < (int) LAYER_ID::BOTTOM) || (layer > (int) LAYER_ID::TOP))
    {

    }

    // If the layer is the selected layer, force it to the top
    else if (layer == getCurrentLayer())
        layer = (int) LAYER_ID::SELECTED;

    //TODO improve this (simplistic) view flipping
    else if (flip)
        layer *= -1;

    item->setZValue(layer);

}
