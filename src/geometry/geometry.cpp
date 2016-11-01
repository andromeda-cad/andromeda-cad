#include "geometry.h"

// Static geometry functions are wrapped in AGeometry:: namespace

using namespace AGeometry;

// Determine if two points are coincident (within a given threshold)
bool AGeometry::PointsAreCoincident(QPointF p1, QPointF p2, double threshold)
{
    double d2 = DistanceSquared(p1,p2);

    return (d2 < pow(threshold, 2));
}

/**
 * @brief Angle
 * Calculate the angle between two points
 * @param pTo
 * @param pFrom
 * @return
 */
double AGeometry::Angle(QPointF pTo, QPointF pFrom)
{
    QPointF delta = pTo - pFrom;

    return qAtan2(delta.y(), delta.x());
}

/**
 * @brief DistanceSquared
 * Calculate the square of the distance between two points
 * @param pTo
 * @param pFrom
 * @return
 */
double AGeometry::DistanceSquared(QPointF pTo, QPointF pFrom)
{
    QPointF delta = pTo - pFrom;

    return qPow(delta.x(), 2) + qPow(delta.y(), 2);
}

/**
 * @brief Distance
 * Calculate the linear distance between two points
 * @param pTo
 * @param pFrom
 * @return
 */
double AGeometry::Distance(QPointF pTo, QPointF pFrom)
{
    return qSqrt(DistanceSquared(pTo, pFrom));
}

/**
 * @brief Midpoint
 * Calculate the midpoint between two points
 * @param pTo
 * @param pFrom
 * @return the midpoint (QPointF)
 */
QPointF AGeometry::Midpoint(QPointF pTo, QPointF pFrom)
{
    return QPointF((pTo.x() + pFrom.x()) / 2,
                   (pTo.y() + pFrom.y()) / 2);
}

LineEquation_t AGeometry::LineEquation(QPointF pTo, QPointF pFrom)
{
    LineEquation_t eqn;

    eqn.A = pFrom.y() - pTo.y();
    eqn.B = pTo.x() - pFrom.x();

    eqn.C = (pFrom.x() * pTo.y()) - (pTo.x() * pFrom.y());

    return eqn;
}

/**
 * @brief ArcAngle
 * Calculate the angle of an arc given the chord length and the radius
 * Note: If the specified chordLength is greater than the diameter, an arc cannot be formed
 * @param radius
 * @param chordLength
 * @return
 */
double AGeometry::ArcAngle(double radius, double chordLength)
{
    // Return zero if the parameters are incompatible
    if (qFabs(radius) <= (chordLength / 2)) return 0;

    return 2 * qAsin(chordLength / (2 * radius));
}

/**
 * @brief ArcRadius
 * Return the radius of an arc segment given the angle and chordLength
 * @param angle
 * @param chordLength
 * @return
 */
double AGeometry::ArcRadius(double angle, double chordLength)
{
    return chordLength / 2 / qSin(angle / 2);
}

/**
 * @brief ArcLength
 * Calculate the length of an arc given the radius and angle
 * @param radius
 * @param angle
 * @return
 */
double AGeometry::ArcLength(double radius, double angle)
{
    return radius * angle;
}

/**
 * @brief AngleNormalized
 * Normalize an angle (in radians) into the range {-PI, PI}
 * @param angle
 * @return
 */
double AGeometry::AngleNormalized(double angle)
{
    while (angle < -M_PI)
    {
        angle += (2 * M_PI);
    }

    while (angle >  M_PI)
    {
        angle -= (2 * M_PI);
    }

    return angle;
}

/**
 * @brief ArcIsStraight
 * Determine if an arc segment is "straight" based on the provided angle
 * Straight segments have an angle equal (or close to) either zero (or) PI (180 degrees)
 * @param angle is the angle of the arc segment
 * @param threshold is used for floating real number comparison
 * @return true if the segment is straight else false
 */
bool AGeometry::ArcIsStraight(double angle, double threshold)
{
    if (qFabs(angle) < threshold)
        return true;

    if (qFabs(angle) > (M_PI - threshold))
        return true;

    return false;
}

bool AGeometry::ArcIsCurved(double angle, double threshold)
{
    return !AGeometry::ArcIsStraight(angle, threshold);
}

/**
 * @brief ArcCenter
 * Calculace the center points of a circle from two points and an angle
 * @param center
 * @param angle
 * @param pTo
 * @param pFrom
 * @return true if the center can be calculated else false
 */
bool AGeometry::ArcCenter(QPointF &center, double angle, QPointF pTo, QPointF pFrom)
{
    if (ArcIsStraight(angle))
        return false;

    QPointF mid = AGeometry::Midpoint(pTo, pFrom);

    double q = Distance(pTo, pFrom);

    QPointF delta = pTo - pFrom;

    double dx = delta.x();
    double dy = delta.y();

    if (angle < 0)
    {
        dx *= -1;
        dy *= -1;
    }

    double r = ArcRadius(angle, q);

    double Q = sqrt(pow(r,2) - pow(q/2,2));

    center.setX(mid.x() + Q * dx / q);
    center.setY(mid.y() + Q * dy / q);

    return true;
}
