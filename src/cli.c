#include <stdio.h>
#include <string.h>

#include "cli.h"
#include "../lib/argparse/argparse.h"

static const char *const usage[] = {
    "test_argparse [options] [[--] args]",
    "test_argparse [options]",
    NULL,
};

cli_opt default_options = {
    "",
    true,
    1024,
    1,
    1000,
    0.005
};

cli_opt process_args(int argc, char **argv) {
    cli_opt nbody_options = default_options;
    char *output_parsed = NULL;

    struct argparse_option arg_options[] = {
        OPT_HELP(),
        OPT_GROUP("File options"),
        OPT_STRING('f', "file", &nbody_options.file_path, "Input file to use."),
        OPT_STRING('o', "output", &output_parsed, "Output results to a separate file."),
        OPT_GROUP("Generation"),
        OPT_INTEGER('p', "particles", &nbody_options.num_particles, "Number of particles to initialise."),
        OPT_INTEGER('i', "iterations", &nbody_options.num_iterations, "Number of iterations to compute."),
        OPT_GROUP("Simulation options"),
        OPT_FLOAT('g', "gravity", &nbody_options.grav_constant, "Gravitational constant to use."),
        OPT_FLOAT('t', "timestep", &nbody_options.time_step, "Time step to use."),
        OPT_END(),
    };

    struct argparse argparse;
    argparse_init(&argparse, arg_options, usage, 0);
    argparse_describe(&argparse, "\nSimulate particle interactions using n-body.", "\nZachary Cauchi.");

    argc = argparse_parse(&argparse, argc, argv);

    // Due to limitations with argparse, we must first parse the output variable as a string and then convert to boolean.

    if (output_parsed != NULL && strlen(output_parsed) >= 5)
    {
        char *found_false = strstr(output_parsed, "false");
        nbody_options.output = found_false == NULL? true : false;
    }

    return nbody_options;
}
