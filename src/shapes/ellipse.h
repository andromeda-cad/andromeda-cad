#ifndef SHAPES_ELLIPSE_H
#define SHAPES_ELLIPSE_H

#include <QPainterPath>

#include "src/geometry/geometry.h"
#include "src/drawable/drawable_primitive.h"

class AEllipse : public ADrawablePrimitive
{
    Q_OBJECT

    Q_PROPERTY( double rx READ rx WRITE setRx )
    Q_PROPERTY( double ry READ ry WRITE setRy )
    Q_PROPERTY( QPointF radius READ radius )
    Q_PROPERTY( bool circular READ isCircular STORED false )

public:
    AEllipse(QObject *parent = 0);
    virtual AEllipse *clone(void) override { return makeClone<AEllipse>(); }

    // Painter Functions
    virtual QRectF boundingRect() const Q_DECL_OVERRIDE;
    virtual QPainterPath shape() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    // Property getters
    QPointF radius(void) const { return QPointF(rx_, ry_); }
    double rx(void) const { return rx_; }
    double ry(void) const { return ry_; }

    bool isCircular(double threshold = AGeometry::DISTANCE_EPSILON) const { return qFabs(rx_ - ry_) < threshold; }

    virtual void encode(AJsonObject &data, bool hideDefaults = false) const override;
    virtual void decode(AJsonObject &data, bool undoable = true) override;

public slots:
    void setRadius(double rx, double ry);
    void setRadius(double r) { setRadius(r,r); }
    void setRadius(QPointF radius) { setRadius(radius.x(), radius.y()); }
    void setRx(double rx) { setRadius(rx, ry_); }
    void setRy(double ry) { setRadius(rx_, ry); }

protected:
    // Properties unique to the ellipse class
    double rx_ = 0;
    double ry_ = 0;

    QRectF bb_;
};

#endif // SHAPES_ELLIPSE_H

