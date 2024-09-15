# 42 Minishell

### Description

Minishell is a project from the 42 School curriculum that requires creating a custom command-line interpreter (similar to a UNIX shell). The primary goal of the project is to help students understand the fundamentals of operating systems, including process management, pipes, memory handling, and interacting with the system using syscalls.

The project mimics a terminal, takes commands from input, and behaves like a standard shell, supporting features such as command execution, redirection, pipes, and environment variable management.
Features

Execution of simple commands (e.g., ls, echo, cat, etc.).
Argument and option handling for commands.
Implementation of pipes (|) to connect multiple commands.
Input redirection (<) and output redirection (>, >>).
Environment variables support and built-in commands (export, unset, env, etc.).
Signal handling (Ctrl-C, Ctrl-D, Ctrl-).
Built-in commands:
    cd: Change the current directory.
    pwd: Print the current directory.
    export: Manage environment variables.
    unset: Remove environment variables.
    env: Display environment variables.
    exit: Exit the shell.
Error handling and reporting for invalid commands.

System Requirements

To run the minishell project, you will need a UNIX-like system with the following requirements:

GCC or another compatible C compiler.
GNU Make to compile the project.
Readline Library: The shell uses readline for handling user input.

### Installation
#### Clone the Repository

First, clone the project repository:


    git clone https://github.com/your-username/minishell.git
    cd minishell

#### Compilation

To compile the project, simply run the make command in the project directory:


    make

This will create the minishell executable.
#### Running

Once compiled, you can run minishell with the following command:


    ./minishell

You will then be able to enter commands and use the shell like a standard terminal.
Usage

### Project Structure

    src/: Contains the .c source files.
    include/: Contains the .h header files.
    Makefile: Build script for compiling the project.
    README.md: This file.

### Dependencies

To run minishell correctly, the readline library is required. You can install it using Homebrew on macOS or through your package manager on Linux.

    On macOS:

    bash

brew install readline

On Ubuntu/Debian:

bash

    sudo apt-get install libreadline-dev

### Known Issues

The project uses the signal() function for handling signals like SIGINT (Ctrl-C), SIGQUIT (Ctrl-), and EOF (Ctrl-D). However, signal() is less reliable than sigaction(), and its behavior can be inconsistent across different platforms or versions of UNIX systems. This could lead to potential issues with signal handling, such as improper resetting of signal handlers after execution.
