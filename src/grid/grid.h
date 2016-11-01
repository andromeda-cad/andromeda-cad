#ifndef GRID_GRID_H
#define GRID_GRID_H

#include <QPointF>

//TODO - abstract this to allow polar grids

const double GRID_MAJOR_TICK_DEFAULT = 25;
const double GRID_MINOR_TICK_DEFAULT = 0;

const double GRID_TICK_MAX = 100.0f;


class AGrid
{
public:
    AGrid();

    enum GridDrawingStyles
    {
        GRID_NO_GRID         = 0x00,    //!< Don't draw any grid

        GRID_DRAW_MAJOR_DOTS = 0x01,    //!< Draw dots at major grid intersections
        GRID_DRAW_MINOR_DOTS = 0x02,    //!< Draw dots at minor grid intersections
        GRID_DRAW_ALL_DOTS   = 0x03,    //!< Draw major and minor dots

        GRID_DRAW_MAJOR_LINES   = 0x10,     //!< Draw horizontal major grid lines
        GRID_DRAW_MINOR_LINES   = 0x20,     //!< Draw vertical major grid lines
        GRID_DRAW_LINES         = 0x30,     //!< Draw all grid lines
    };

    // Static helper functions
    static double mapToGrid(double value, double spacing, double origin = 0.0f);
    static QPointF mapToGrid(QPointF point, QPointF spacing, QPointF origin = QPointF(0,0));

    double getMajorTick() { return majorTick_; }
    double getMinorTick() { return minorTick_; }
    bool setMajorTick(double tick);
    bool setMinorTick(double tick);

    void setDrawStyle(int style) { drawStyle_ = style; }
    int getDrawStyle() { return drawStyle_; }

    QPointF getOrigin() { return origin_; }
    void setOrigin(QPointF origin) { origin_ = origin; }

protected:
    double majorTick_;
    double minorTick_;
    QPointF origin_;

    int drawStyle_;
};

#endif // GRID_GRID_H

