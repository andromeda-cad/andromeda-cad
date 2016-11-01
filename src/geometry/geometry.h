#ifndef GEOMETRY_H
#define GEOMETRY_H

/*
 * Functions in this file should probably get reassigned
 * Just here as temp placeholders
 * Useful geometry funcs, etc...
 */

#include <qmath.h>
#include <QPointF>

namespace AGeometry
{

// Some arbitratily small angle
const double ARC_ANGLE_THRESHOLD = 0.001 * M_PI / 180;

// Some arbitrarily small distance
const double DISTANCE_EPSILON = 1e-8;

/* Point Functions */
bool PointsAreCoincident(QPointF p1, QPointF p2, double threshold = DISTANCE_EPSILON);

/* Line Functions */

// Calculate the angle between two points
double Angle(QPointF pTo, QPointF pFrom = QPointF(0,0));

// Calculate d^2 between two points
double DistanceSquared(QPointF pTo, QPointF pFrom = QPointF(0,0));

// Calculate distance between two points
double Distance(QPointF pTo, QPointF pFrom = QPointF(0,0));

QPointF Midpoint(QPointF pTo, QPointF pFrom = QPointF(0,0));

/*
 * Structure for defining the equation of a straight line
 */
typedef struct
{
    double A;
    double B;
    double C;
} LineEquation_t;

LineEquation_t LineEquation(QPointF pTo, QPointF pFrom = QPointF(0,0));

/* Arc Functions */

double ArcAngle(double radius, double chordLength);
double ArcRadius(double angle, double chordLength);
double ArcLength(double radius, double angle);

double AngleNormalized(double angle);

bool ArcIsStraight(double angle, double threshold = ARC_ANGLE_THRESHOLD);
bool ArcIsCurved(double angle, double threshold = ARC_ANGLE_THRESHOLD);

bool ArcCenter(QPointF &center, double angle, QPointF pTo, QPointF pFrom = QPointF(0,0));

}

#endif // GEOMETRY_H
