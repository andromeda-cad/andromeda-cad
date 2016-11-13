#ifndef DRAWABLE_BASE_H
#define DRAWABLE_BASE_H

#include <QGraphicsItem>
#include <QList>
#include <QPointF>
#include <QColor>
#include <QPen>
#include <QBrush>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QString>
#include <QGraphicsItem>

#include "src/layers/layer_defines.h"
#include "src/shapes/shape_defines.h"
#include "src/geometry/bounding_box.h"

#include "src/base/andromeda_object.h"

class ADrawableBase : public AndromedaObject, public QGraphicsItem
{
    Q_OBJECT

    Q_INTERFACES( QGraphicsItem )

    // Generic drawable properties that we want exposed
    Q_PROPERTY( int layer READ layer WRITE setLayer NOTIFY layerChanged)
    Q_PROPERTY( QPointF pos READ pos WRITE setPos)
    Q_PROPERTY( QRectF boundingBox READ boundingRect STORED false)
    Q_PROPERTY( unsigned int orientation READ orientation WRITE setOrientation )

public:
    ADrawableBase(QObject *parent = 0);

    /**
     * @brief The Orientation enum lists allowable pin orientations
     * The orientations describe the location of the connection point
     * e.g. LEFT means that that connection occurs at the left-most point of the pin
     */
    enum class Orientation : int {
        LEFT = 0,   // Pin connection point on the left
        DOWN,
        RIGHT,
        UP,
        //TODO FREE, - allow free rotation
        INVALID,
    };

    /**
     * @brief The LOCK enum describes the various "lock" modes avaiable
     * for a drawable item.
     */
    enum class LOCK : int {
        UNLOCKED = 0,
        LOCKED = 0xF,
    };

    // JSON params
    virtual void decode(AJsonObject &data, bool undoable = true) override;
    virtual void encode(AJsonObject &data, bool hideDefaults = false) const override;

    // Bounding box drawing
    void drawBoundingBox(QPainter *painter);

    // Property getters
    virtual QRectF boundingRect(void) const override { return QRectF(); }
    int layer(void) const { return layer_; }
    unsigned orientation(void) const { return orientation_; }

    //QPen getBoundingBoxPen(void) { return bounding_box_pen_; }

    // Return a list of 'anchors' for this item
    // Default, empty list

    virtual QPointF centroid(void) { return boundingRect().center(); }
    //TODO
    //QList<QPointF> getAnchors() { return QList<QPointF>(); }

public slots:
    void setLayer(int layer);
    void setBoundingBoxPen(QPen pen) { bounding_box_pen_ = pen; }

    void setPos(QPointF point);
    void setPos(double x, double y);

    void setX(double x);
    void setY(double y);

    void setOrientation(unsigned int orientation);
    void rotate(bool ccw = true);

    int getLock( void ) { return lock_; }

signals:
    void layerChanged(int layer);

protected:
    // Properties unique to ADrawableBase
    bool draw_bounding_box_ = false;
    QPen bounding_box_pen_;

    int layer_ = (int)  LAYER_ID::NONE;

    //!
    int lock_ = (int) LOCK::UNLOCKED;

    unsigned int orientation_ = (int) Orientation::LEFT;
};

#endif // DRAWABLE_BASE_H

