# TapeStorage

**TapeStorage** is a C++ console application that emulates a sequential-access magnetic tape device and implements external merge sort under a strict memory budget. It reads integers from an “input tape” file, sorts them (using only a limited chunk of RAM and temporary tape files), and writes the result to an “output tape” file.

---

## Features

- **Tape emulation**  
  – Sequential read/write with configurable delays (read, write, head movement, tape switching)  
  – Atomic head‐movement operations  
  – Enforced memory limit via a custom allocator  

- **External Merge Sort**  
  – Splits the tape into runs of size _M_  
  – Merges runs two at a time using temporary tape files in `tmp/`  
  – Works on tapes of arbitrary length _N_ with only _M_ bytes of RAM  

- **Configurable delays & memory**  
  – No recompilation required — all delays and memory limits come from `config.txt`  

- **CMake-based build**  
  – Cross-platform (Linux, macOS, Windows with appropriate toolchain)  

---

## Repository Structure

```text
TapeStorage/
├── CMakeLists.txt           # Top-level CMake project file
├── config.txt               # External configuration (memory, delays, etc.)
├── LICENSE                  # MIT License
├── README                   # <this file>
└── src/
    ├── CMakeLists.txt       # CMake for the src/ tree
    ├── main.cpp             # Entry-point: parses args & kicks off SortManager
    ├── Parser/
    │   ├── ConfigParser.h   # Reads config.txt into ConfigData
    │   └── ConfigParser.cpp
    ├── Tape/
    │   ├── Tape.h           # ITape interface & Tape class declaration
    │   └── Tape.cpp         # File-backed tape emulation
    ├── Utils/
    │   └── MemoryLayout.h/cpp  # Simple bump allocator respecting M bytes
    └── Sorting/
        ├── Sorting.h        # SortManager class declaration
        └── Sorting.cpp      # MergeSort implementation over Tape
```

## Usage

1. **Build the executable**  
   After following the build steps (`cmake`, `cmake --build`), you’ll have a `TapeStorage` binary in your `build/` directory, or you can grab build from this repo.

2. **Create `config.txt`**  
   In the project root (next to `CMakeLists.txt`), create a file named `config.txt` with these parameters:

   ```ini
   OP_MEM_SIZE 1024        # max bytes of RAM for buffering
   READ_DELAY 5            # ms delay per cell read
   WRITE_DELAY 5           # ms delay per cell write
   SWITCH_TAPE_DELAY 50    # ms delay when switching temporary tapes
   MOVE_HEAD_DELAY 1       # ms delay per head movement
    
    ```

3. Run:
   ```bash
   ./TapeStorage input.dat output.dat <size of tape>
