# TinyCOW

A lightweight, efficient interpreter for the **COW** esoteric programming language written in pure C.

The COW language is a humorous variant of Brainfuck where all instructions are variations of the word "moo" (with different capitalization). This project reads a source file containing COW instructions, parses them, and executes them on a virtual memory tape.

## Features

- **File Parsing:** Reads and validates COW source code directly from a file.
- **Instruction Execution:** Built-in loop control, memory pointer manipulation, and standard I/O commands.
- **Dynamic Instruction Execution (`mOO`):** Supports executing memory tape values as live operations.
- **Safety Checks:** Out-of-bounds protection for the instruction tape memory.

## Instruction Set

The interpreter maps the variations of "moo" to specific operations based on the official COW specification:

| Command | Hex Opcode | Description |
| :--- | :---: | :--- |
| `moo` | `0x00` | **JUMP_START:** Execute next command if previous command was a jump block. |
| `mOo` | `0x01` | **BACK:** Move the memory pointer back one cell. |
| `moO` | `0x02` | **FORWARD:** Move the memory pointer forward one cell. |
| `mOO` | `0x03` | **EXEC:** Execute the instruction matching the value in the current memory cell. |
| `Moo` | `0x04` | **IO_IF_ZERO:** If current cell is 0, read a character from stdin. Otherwise, print it to stdout. |
| `MOo` | `0x05` | **DEC:** Decrement the value in the current memory cell. |
| `MoO` | `0x06` | **INC:** Increment the value in the current memory cell. |
| `MOO` | `0x07` | **JUMP_IF_ZERO:** Jump past matching `moo` if current cell is 0. |
| `OOO` | `0x08` | **SET_ZERO:** Set the current memory cell value to 0. |
| `MMM` | `0x09` | **COPY_REG:** Copy current cell value to register if empty, or paste from register if full. |
| `OOM` | `0x0A` | **PRINT_INT:** Print the integer value of the current memory cell. |
| `oom` | `0x0B` | **READ_INT:** Read an integer from stdin into the current memory cell. |

## Requirements

To build this project, you need:

- **CMake:** Version 3.10 or higher.
- **C Compiler:** A standard C99 (or later) compliant compiler (such as `gcc` or `clang`).
- **Build Tools:** `make` or any other build system generator supported by CMake.

## Installation & Compilation

Follow these steps to generate the build files and compile the project using CMake:

1. **Clone or download** the repository to your local machine.

2. Navigate to the project root directory and create a `build` folder:

   ```bash
   mkdir build && cd build
   ```

3. Configure & build the project with CMake:

   ```bash
   cmake .. && cmake --build .
   ```

## Usage

To run a COW source file, pass the path of the file as an argument to the compiled binary:

```bash
./tinycow <FILE>
```

### Example

You have an example program in [`files/hello_world.cow`](files/hello_world.cow) containing COW code to print the message *Hello, world!*, run:

```bash
./tinycow ../files/hello_world.cow
```

To display help information:

```bash
./tinycow --help
```

## Future Roadmap

- Complete the loop block implementation for `moo` (`JUMP_START`) and `MOO` (`JUMP_IF_ZERO`).
- Add dynamic memory management for the program tape to remove the 4096 instruction limit.

## License

This project is open-source and available under the [MIT License](LICENSE).
