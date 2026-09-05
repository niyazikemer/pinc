# Phase 00 — CLI scaffold

Phase 00 ports Tau's smallest command-line surface to pinc:

- The CLI can report the program version.
- Its default behavior confirms that the scaffold is installed.

The CLI belongs in `pinc_coding` because it is application-facing code.

## Files involved

- `src/main.c` defines the standard C entry function and delegates its command-line arguments to the CLI.
- `src/pinc_coding/cli.h` declares the CLI function shared by its implementation and callers such as `main.c`.
- `src/pinc_coding/cli.c` implements argument handling and terminal output.
- `VERSION` is a plain-text file containing only the program version and is the version's single source of truth.
- `Makefile` describes how Make builds the program, passes the version to the C preprocessor, and installs the executable.
- `compile_commands.json` records the exact compiler invocation for each translation unit so editor tooling sees the real build configuration.
- `.vscode/settings.json` tells VS Code's C/C++ extension to use `compile_commands.json`.

## The C approach

This phase uses the ordinary C model: a small `main` function, an explicit header between translation units, and direct inspection of `argc` and `argv`. There is no CLI dependency because one option does not justify one yet.

The two-parameter form of `main` receives the command-line argument count and argument vector from C runtime startup code. The parameter names `argc` and `argv` are conventional rather than reserved; their positions and types give them their roles. Other functions receive these values only when a caller passes them on, as `main` does for `pinc_cli_run`.

A header does not find or load its matching implementation. Including `cli.h` textually supplies declarations to each translation unit that includes it, while the build later compiles `cli.c` and the linker connects calls to its implementation. Including the module's own header in `cli.c` also lets the compiler check the implementation against its shared declaration.

`printf` and `strcmp` are C standard library functions rather than built-in language operations. Their declarations come from `<stdio.h>` and `<string.h>` respectively.

The build uses Make rather than embedding build behavior in the language toolchain. Object files and the executable go under `build/`, keeping generated files separate from source files. The compiler is selected through Make's conventional `CC` variable so the project is not tied to GCC or Clang. Compilation targets C23 and enables strict warnings.

Make reads the plain text in `VERSION` and supplies it with the compiler's `-D` option. That option defines `PINC_VERSION` as a preprocessor macro, so `cli.c` does not open or read the version file at runtime.

The compiler and Make are sufficient to build the program. Bear is development tooling: it observes a Make build and generates `compile_commands.json`. VS Code uses that compilation database to see the same include paths, macro definitions, language version, and flags as the compiler, avoiding false diagnostics such as treating `PINC_VERSION` as unknown.

## Build and installation

Running `make` builds `build/pinc`. If all inputs are unchanged, Make reports that nothing needs to be done because the existing output is current. Running `make clean` removes the build directory so the next `make` performs a complete rebuild.

Running `make install` first ensures the executable is built, then copies it to `~/.local/bin/pinc` with executable permissions. Because `~/.local/bin` is on the shell's `PATH`, the installed program can be invoked from any directory as `pinc` or `pinc --version`.

Installation is separate from compilation: `make` changes only the project's `build` directory, while `make install` writes the executable into the user's local binary directory.

## Difference from Tau

Tau uses Typer to declare and process its CLI. pinc handles its single option directly with the C program's `argc` and `argv`; a CLI framework would add little value at this phase.

Tau exposes the version as `tau_coding.__version__`. C has no package module or runtime package metadata equivalent, so pinc keeps the value in `VERSION`. Make reads it and supplies it to the compiler, avoiding a second version declaration in the source.

Typer also supplies generated help, completion behavior, and option validation. Phase 00 does not reproduce those framework features; it only ports the behavior needed by the current scaffold.
