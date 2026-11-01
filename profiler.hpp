#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

class Profiler {
    std::vector<std::string> call_stack;
    std::map<std::pair<std::string, std::string>, int> call_edges;
    std::ofstream event_log;

    Profiler() {
        event_log.open("event_log.txt");
    }

    ~Profiler() {
        if (event_log.is_open()) {
            event_log.close();
        }
        write_path_profile();
    }

public:
    static Profiler& instance() {
        static Profiler prof;
        return prof;
    }

    void enter(const std::string& func_name) {
        std::string caller = call_stack.empty() ? "[ROOT]" : call_stack.back();

        // Log event
        if (event_log.is_open()) {
            event_log << "ENTER: " << func_name << " (called by " << caller << ")\n";
        }

        // Track path frequency
        if (!call_stack.empty()) {
            call_edges[{caller, func_name}]++;
        }

        call_stack.push_back(func_name);
    }

    void exit(const std::string& func_name) {
        if (event_log.is_open()) {
            event_log << "EXIT:  " << func_name << "\n";
        }
        if (!call_stack.empty()) {
            call_stack.pop_back();
        }
    }

private:
    void write_path_profile() {
        std::ofstream profile_file("path_profile.txt");
        if (!profile_file.is_open()) return;

        profile_file << "=== PATH PROFILE (Caller -> Callee Frequencies) ===\n\n";
        for (const auto& [edge, count] : call_edges) {
            profile_file << edge.first << " -> " << edge.second
                         << " : " << count << " call(s)\n";
        }
        profile_file.close();
    }
};

struct ScopeProfiler {
    const char* func_name;
    explicit ScopeProfiler(const char* name) : func_name(name) {
        Profiler::instance().enter(func_name);
    }
    ~ScopeProfiler() {
        Profiler::instance().exit(func_name);
    }
};

#define PROFILE_FUNCTION() ScopeProfiler _prof_scope_guard(__func__)