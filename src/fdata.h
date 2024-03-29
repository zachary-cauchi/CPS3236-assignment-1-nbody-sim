#ifndef FDATA_H_
#define FDATA_H_

#include "bpoint.h"

/**
 * Function: count_lines
 * ---------------------
 * Count the lines in a file. Used for checking how many points need to be loaded.
 * 
 * fptr: A pointer to a loaded file.
 * 
 * returns: Number of lines found.
 * 
 **/
int count_lines(FILE *fptr);

/**
 * Function: load_points_from_file
 * -------------------------------
 * Load a number of points from a given file.
 * Points are saved to a given allocated array.
 * 
 * points: A pointer to a point array to be filled.
 * count: The number of points in the file to be loaded. Must equal the total lines of the file.
 * fptr: Pointer to a loaded file.
 * 
 * returns: 0 if successful, -1 if unsuccessful.
 * 
 **/
int load_points_from_file(b_point *points, const int count, FILE *fptr);

/**
 * Function: process_file
 * ----------------------
 * Read a file at the given file path. Can be a relative or absolute path.
 * 
 * path: Relative or absolute string file path to the file to load.
 * point_count: A pointer to an integer representing the size of the loaded point array.
 * 
 * returns: NULL if unsuccessful, a pointer to a point array of *point_count size.
 * 
 **/
b_point *process_file(const char *path, int *point_count);

/**
 * Function: save_points_iteration
 * ----------------------
 * Save the points as an iteration to the file.
 * The points are saved as-is assuming to be in the same order as when they were first read in.
 * 
 * points: The points array to save.
 * point_count: The number of points in the array.
 * 
 **/
void save_points_iteration(b_point *points, int point_count, int iteration);

#endif
