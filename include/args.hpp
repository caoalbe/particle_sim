enum class SimulationSetup {
    Circular,
    CircularMoving,
    Four,
    Random,
    Input,
};

class ParsedArgs {
    public:
        // Arguments
        SimulationSetup sim_setup;

        // Flags
        bool ignore_field;
        bool help;

        // Output
        bool error_output;

        ParsedArgs(int argc, char* argv[]);
        void print_usage();

};
