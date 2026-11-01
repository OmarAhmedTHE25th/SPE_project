#include "profiler.hpp"
#include <iostream>

void step_b() {
    PROFILE_FUNCTION();
    std::cout << "  Executing step B...\n";
}

void step_a() {
    PROFILE_FUNCTION();
    std::cout << "  Executing step A...\n";
    step_b();
}

void parse_input() {
    PROFILE_FUNCTION();
    std::cout << "Parsing input...\n";
    step_a();
}

void compute_results() {
    PROFILE_FUNCTION();
    std::cout << "Computing results...\n";
    step_b();
}

int main() {
    PROFILE_FUNCTION();

    parse_input();
    compute_results();

    return 0;
}