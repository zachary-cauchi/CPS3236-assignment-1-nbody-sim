#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fdata.h"
#include "bpoint.h"

const char *out_path = "./res/out/";

FILE *open_file(const char *path, const char *mode) {
    // Open the file for read-only, checking it was successfull.
    FILE *fptr = fopen(path, mode);
    if (fptr == NULL) { 
        printf("File couldn't be opened\n");
        return NULL;
    }

    return fptr;
}

int count_lines(FILE *fptr) {
    int lines = 0;

    // Match against all newlines in the file (accounting for Windows and unix newlines).
    while (EOF != (fscanf(fptr, "%*[^\r\n]"), fscanf(fptr,"%*c")))
        ++lines;
    
    // Reset to beginning of file. Not compatible with stdin.
    rewind(fptr);

    return lines;
}

int load_points_from_file(b_point *points, const int count, FILE *fptr) {
    int i = 0;
    
    // Load all the points by the expected pattern of mass, x, y.
    for(i = 0; i < count && !feof(fptr); ++i)
    {
        fscanf(fptr, "%lf, %lf, %lf", &points[i].mass, &points[i].pos.x, &points[i].pos.y);
        points[i].vel = (vec2) { 0, 0 };
    }

    // Test that we loaded the same amount of points as expected.
    if (i > count) {
        printf("Error: Points read do not match the expected count of points:\n\tExp: %d - Act:%d\n", count, i - 1);
        return -1;
    }
    
    printf("Successfully read %d points.\n", i - 1);

    return 0;
}

b_point *process_file(const char *path, int *point_count) {
    FILE *fptr = open_file(path, "r");

    // Save the number of points found.
    *point_count = count_lines(fptr);

    printf("Found points: %d\n", *point_count);

    // Allocate space for them, so we can return a pointer to this space.
    b_point *points = NULL;
    MPI_Alloc_mem(sizeof(b_point) * *point_count, MPI_INFO_NULL, &points);

    int load_result = load_points_from_file(points, *point_count, fptr);

    if (load_result == -1) {
        printf("File processing failed\n");
        return NULL;
    }

    fclose(fptr);

    return points;
}

void save_points_iteration(b_point *points, int point_count, int iteration)
{
    char buffer[128];
    char filepath[32768];

    // Create the file path.
    snprintf(buffer, 128, "nbody_%d.txt", iteration);
    strcat(strcpy(filepath, out_path), buffer);

    FILE *file = open_file(filepath, "w");

    double m, x, y;

    for (int i = 0; i < point_count; i++)
    {
        m = points[i].mass;
        x = points[i].pos.x;
        y = points[i].pos.y;

        fprintf(file, "%.6f %.6f %.6f\n", m, x, y);
    }

    fclose(file);

    return;
}
