#include <iostream>
#include "args.hpp"

ParsedArgs::ParsedArgs(int argc, char* argv[]) {
    if (argc == 1) {
        std::cerr << "Error: Missing required argument <simulation_setup>\n";
        error_output = true;
        help = true;
    }

    for (int i = 1; i < argc; i++) {
        if (std::strcmp(argv[i], "circular") == 0) {
            sim_setup = SimulationSetup::Circular;
        } else if (std::strcmp(argv[i], "circular-moving") == 0) {
            sim_setup = SimulationSetup::CircularMoving;
        } else if (std::strcmp(argv[i], "four") == 0) {
            sim_setup = SimulationSetup::Four;
        } else if (std::strcmp(argv[i], "random") == 0) {
            sim_setup = SimulationSetup::Random;
        } else if (std::strcmp(argv[i], "input") == 0) {
            sim_setup = SimulationSetup::Input;
        } else if (std::strcmp(argv[i], "--ignore-field") == 0) {
            ignore_field = true;
        } else if (std::strcmp(argv[i], "--help") == 0 || std::strcmp(argv[i], "-h") == 0) {
            help = true;
        } else {
            std::cerr << "Error: Unrecognized argument '" << argv[i] << "'\n";
            error_output = true;
        }
    }
}

void ParsedArgs::print_usage() {
    std::cout   << "Usage: ./main <simulation_setup> [options]\n"
                << "Arguments:\n"
                << "<simulation_setup>      Preset of particle state (required)\n"
                << "                        circular, circular-moving, four, random\n"
                << "Options:\n"
                << "    --ignore-field      Does not show electric field\n"
                << "        --help, -h      Shows this message\n";
}