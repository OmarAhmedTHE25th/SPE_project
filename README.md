# Automated Source Instrumentation & Path Profiler

> **Course:** CSE 446 — Software Performance Evaluation  
> **Author:** Omar Ahmed Abdel Hameed (ID: 24P0201)  
> **Instructor:** Dr. Islam El-Maddah  

---

## 📌 Overview

This project implements an automated, lightweight source-level instrumentation profiler for procedural C/C++ applications. Designed without invasive hardcoded labels or external runtime binary injection, it leverages standard macro reflection (`__func__`) and C++ RAII (Resource Acquisition Is Initialization) to dynamically extract:

1. **Chronological Event Log (`event_log.txt`)**: Traces real-time function entries and exits with explicit caller-callee relationship tracking.
2. **Path Profile Aggregation (`path_profile.txt`)**: Quantifies runtime call frequencies across all unique caller $\to$ callee execution edges.

---

## 📁 Repository Structure

```text
.
├── CMakeLists.txt        # Build configuration for CMake/CLion
├── profiler.hpp          # Profiler engine & RAII scope guard implementation
├── main.cpp              # Sample target workload demonstrating nested calls
├── event_log.txt         # Generated sequential event log
├── path_profile.txt      # Generated call path summary and frequencies
└── README.md             # Replication guide and project documentation
```

---

## ⚙️ Architecture & Mechanism

### 1. RAII Scope Guard Pattern
Rather than manually placing enter and exit hooks before every branching `return` statement, each function declares:

```cpp
PROFILE_FUNCTION();
```

Under the hood:
* **Constructor (`enter`)**: Queries the current top of the internal call stack to identify the caller, emits an `ENTER` record to `event_log.txt`, increments the edge counter `(caller -> callee)` in an internal associative map, and pushes the current routine onto the call stack.
* **Destructor (`exit`)**: Fires automatically upon scope termination, writes an `EXIT` record, and pops the subroutine from the stack.

### 2. Constraints Handled
* **Zero Hardcoded Names**: Function identifiers are resolved at compile time via `__func__`.
* **Safe Call Stacking**: The tracker maintains a stack of active frames to accurately determine callers in multi-tier call chains without assuming single-caller hierarchy.
* Procedural focus: strictly adheres to non-recursive, procedural C/C++ call sequences.

---

## 🚀 How to Build & Run

### Prerequisites
* A C++17 compatible compiler (`g++`, `clang++`, or MSVC)
* CMake 3.15+ (optional, or compile directly)

### Option 1: Direct Compilation (Terminal / GCC)

```bash
# 1. Clone the repository
git clone https://github.com/<your-username>/<your-repo-name>.git
cd https://github.com/OmarAhmedTHE25th/SPE_project.git

# 2. Compile using C++17
g++ -std=c++17 main.cpp -o profiler_app

# 3. Execute
./profiler_app
```

### Option 2: Using CMake / CLion
1. Open the project folder in CLion (or your preferred IDE).
2. Reload CMake project if prompted.
3. Build and Run the `SPE_project` target.
