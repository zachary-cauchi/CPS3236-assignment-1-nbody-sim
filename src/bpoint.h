#ifndef BPOINT_H_
#define BPOINT_H_

#include <mpi.h>

#include "vector2.h"

#define MASS_RAND_MAX 10
#define X_RAND_MAX 5000
#define X_RAND_MIN -5000
#define Y_RAND_MAX 5000
#define Y_RAND_MIN -5000

typedef struct b_point {
    double mass;
    vec2 vel;
    vec2 pos;
} b_point;

/**
 * Function: get_mpi_b_point_type
 * ------------------------------
 * Generate and/or get an MPI-registered datatype for b_points.
 * 
 * returns: The new type.
 **/
MPI_Datatype get_mpi_b_point_type();

/**
 * Function: print_points
 * ----------------------
 * Print the points in a given array.
 * Values are printed in the following format:
 * mass | vel | pos
 * %.3f %.3f %.3f %.3f %.3f
 * ex: m: 6.123 v: -4.212, -232.125, p: 100.435, -235.123
 * 
 * points: A point array to be printed.
 * count: How many points are in the array (or to print).
 * 
 **/
void print_points(b_point *points, const int count);

/**
 * Function: generate_rand_points
 * ------------------------------
 * Generate a series of random points with mass and coordinate values.
 * 
 * points: A point array to be populated.
 * count: How many points to generate.
 * 
 **/
void generate_rand_points(b_point *points, const int count);

/**
 * Function: print_point
 * ------------------------------
 * Print a given point.
 * Values are printed in the following format:
 * mass | vel | pos
 * %.3f %.3f %.3f %.3f %.3f
 * ex: m: 6.123 v: -4.212, -232.125, p: 100.435, -235.123
 * 
 * point: The point to print.
 * 
 **/
void print_point(b_point *point);

#endif