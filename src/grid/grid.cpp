#include "grid.h"

AGrid::AGrid() :
    majorTick_(GRID_MAJOR_TICK_DEFAULT),
    minorTick_(0),
    origin_(0,0),
    drawStyle_(GRID_DRAW_ALL_DOTS | GRID_DRAW_MAJOR_LINES)
{

}

/**
 * @brief AGrid::mapToGrid
 *
 * Map an arbitary value to its closest point on the specified grid
 * @param value is the value to be mapped to a regular grid
 * @param spacing is the grid spacing
 * @param origin is the (optional) offset (default = 0)
 * @return
 */
double AGrid::mapToGrid(double value, double spacing, double origin)
{
    double div = value / spacing;

    // Add or subtract values for correct integer rounding
    if (div > 0) div += 0.5;
    else if (div < 0) div -= 0.5;

    //TODO compensate for non-zero origin value

    return (double) ((int) div * spacing);
}

QPointF AGrid::mapToGrid(QPointF point, QPointF spacing, QPointF origin)
{
    QPoint mapped;

    mapped.setX(mapToGrid(point.x(), spacing.x(), origin.x()));
    mapped.setY(mapToGrid(point.y(), spacing.y(), origin.y()));

    return mapped;
}

bool AGrid::setMajorTick(double tick)
{
    // Tick spacing cannot be lower than zero
    if (tick < 0) return false;

    // Tick spacing cannot exceed maximum
    if (tick > GRID_TICK_MAX) return false;

    // Major tick spacing cannot be lower than minor tick spacing
    if (tick < minorTick_) return false;

    majorTick_ = tick;

    return true;
}

bool AGrid::setMinorTick(double tick)
{
    // Tick spacing cannot be lower than zero
    if (tick < 0) return false;

    // Tick spacing cannot exceed maximum
    if ((tick > majorTick_) || (tick > GRID_TICK_MAX)) return false;

    minorTick_ = tick;

    return true;
}
