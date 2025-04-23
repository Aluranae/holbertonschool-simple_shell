# Simple Shell !

## Welcome to the Simple Shell project !

This project is part of my curriculum at Holberton School. It is the second major group project, and also the final project of the first trimester.
Carried out in collaboration with two other students, the goal was to build our own Unix command-line interpreter, called Simple Shell.
The work had to follow strict technical guidelines, including rules on coding style, modularity, and performance. All the requirements and constraints are detailed in the following sections of this README.

## Navigation

- [Technical requirements and constraints](#technical-requirements-and-constraints)
- [Description of Simple Shell](#description-of-simple-shell)
- [The man page](#the-man-page)
- [The Flowchart of Simple Shell](#the-flowchart-of-simple-shell)
- [File organisation](#file-organisation)
- [Main Functions & Return Values](#main-functions--return-values)
- [Memory Leak Testing with Valgrind](#memory-leak-testing-with-valgrind)
- [Tests](#tests)
- [Examples](#examples)
- [How to contribute](#how-to-contribute)
- [Authors](#authors)

## Technical requirements and constraints

- Allowed editors: vi, vim, emacs
- All your files will be compiled on Ubuntu 20.04 LTS using gcc, using the options -Wall -Werror -Wextra -pedantic -std=gnu89
- All your files should end with a new line
- A README.md file, at the root of the folder of the project is mandatory
- Your code should use the Betty style. It will be checked using betty-style.pl and betty-doc.pl
- Your shell should not have any memory leaks
- No more than 5 functions per file
- All your header files should be include guarded
- Use system calls only when you need to (why?)

### Github

There should be one project repository per group. If you clone/fork/whatever a project repository with the same name before the second deadline, you risk a 0% score.

## Description du Shell

Simple Shell is a command-line interpreter written in C that allows the execution of commands in a Unix environment, just like a real terminal. It supports the following features:

Interactive and non-interactive modes: The shell can operate in an interactive terminal, where users manually enter commands, or in a non-interactive mode, where it executes commands passed through a file or a pipe.

Basic command execution: It allows execution of standard Unix commands such as /bin/ls, /bin/pwd, etc., just like a traditional shell.

Built-in commands: The shell includes several built-in commands, such as exit (to exit the shell), cd (to change directories), env (to display environment variables), and pid (to display the current process ID).

Error handling: The shell properly handles errors like "command not found" and displays clear messages indicating the program name followed by the specific error. For example: ./hsh: 1: qwerty: not found.

Execution using fork and execve: When a command is entered, the shell creates a child process using fork(), then executes the command within it using execve(). If the command is a built-in, it is handled directly by the shell without creating a child process.

### Output

- Unless specified otherwise, your program must have the exact same output as sh (/bin/sh) as well as the exact same error output.
- The only difference is when you print an error, the name of the program must be equivalent to your argv[0] (See below)  

Example of error with sh:

```c
julien@ubuntu:/# echo "qwerty" | /bin/sh
/bin/sh: 1: qwerty: not found
julien@ubuntu:/# echo "qwerty" | /bin/../bin/sh
/bin/../bin/sh: 1: qwerty: not foun
```

Same error with your program hsh:

```c

julien@ubuntu:/# echo "qwerty" | ./hsh
./hsh: 1: qwerty: not found
julien@ubuntu:/# echo "qwerty" | ./././hsh
./././hsh: 1: qwerty: not found

```

## List of allowed functions and system calls+

```c

all functions from string.h
access (man 2 access)
chdir (man 2 chdir)
close (man 2 close)
closedir (man 3 closedir)
execve (man 2 execve)
exit (man 3 exit)
_exit (man 2 _exit)
fflush (man 3 fflush)
fork (man 2 fork)
free (man 3 free)
getcwd (man 3 getcwd)
getline (man 3 getline)
getpid (man 2 getpid)
isatty (man 3 isatty)
kill (man 2 kill)
malloc (man 3 malloc)
open (man 2 open)
opendir (man 3 opendir)
perror (man 3 perror)
printf (man 3 printf)
fprintf (man 3 fprintf)
vfprintf (man 3 vfprintf)
sprintf (man 3 sprintf)
putchar (man 3 putchar)
read (man 2 read)
readdir (man 3 readdir)
signal (man 2 signal)
stat (__xstat) (man 2 stat)
lstat (__lxstat) (man 2 lstat)
fstat (__fxstat) (man 2 fstat)
strtok (man 3 strtok)
wait (man 2 wait)
waitpid (man 2 waitpid)
wait3 (man 2 wait3)
wait4 (man 2 wait4)
write (man 2 write)

```

### Compilation

- Your code will be compiled this way:

```c

$ gcc -Wall -Werror -Wextra -pedantic -std=gnu89 -Wno-format *.c

```

### Testing

Your shell should work like this in interactive mode:

```c

julien@ubuntu:/# ./hsh
($) /bin/ls
hsh main.c shell.c
($)
($) exit
julien@ubuntu:/#

```

But also in non-interactive mode:

```c

julien@ubuntu:/# echo "/bin/ls" | ./hsh
hsh main.c shell.c test_ls_2
julien@ubuntu:/# cat test_ls_2
/bin/ls
/bin/ls
julien@ubuntu:/# cat test_ls_2 | ./hsh
hsh main.c shell.c test_ls_2
hsh main.c shell.c test_ls_2
julien@ubuntu:/#

```

### Checks

The Checker will be released at the end of the project (1-2 days before the deadline). We strongly encourage the entire class to work together to create a suite of checks covering both regular tests and edge cases for each task. See task `8. Test suite`.

After the deadline, you will need to fork the repository if it’s not on your Github account to be able to be corrected by the checker.

## The man page

.TH simple_shell 1 "22/04/2025" "version 1.0"
.SH NAME
simple_shell \- A simple UNIX command line interpreter.

.SH SYNOPSIS
.B simple_shell
.RI [ script_file ]

.SH DESCRIPTION
.B simple_shell
is a simple implementation of a UNIX command line interpreter. It provides basic functionality for executing commands, handling built-in commands, and managing the environment.

.SS Builtins
The following built-in commands are supported:
.TP
.B exit
Exit the shell. This command terminates the shell session.
.TP
.B env
Print the current environment variables. Useful for debugging or scripting.

.SH USAGE
.TP
.B Interactive mode:
The shell displays a prompt and waits for the user to type a command. After executing the command, it displays the prompt again.
.TP
.B Non-interactive mode:
The shell reads commands from a file or standard input and executes them.

.SH EXAMPLES
.TP
.B Interactive mode:
Run the shell and type commands:
.EX
$ ./hsh
($) ls
file1 file2
($) exit
.EE
.TP
.B Non-interactive mode:
Provide commands via a script or pipe:
.EX
$ echo "ls" | ./hsh
file1 file2
.EE

.SH AUTHORS
.B Benjamin Estrada
.RI ( https://github.com/Aluranae )
.B Nawfel
.RI ( https

## The Flowchart of Simple Shell

## File Organisation

The project is structured into multiple files to organize the code clearly and modularly:

### 1. `shell_main.c`
- **Description**: Main entry point of the program. This file contains the main loop of the shell and handles user interaction.
- **Responsibilities**:
  - Displaying the prompt if the shell is running in interactive mode.
  - Reading user input using `getline()`.
  - Splitting the input into arguments using `strtok()`.
  - Executing built-in or external commands (via `fork()` and `execve()`).

### 2. `builtins.c`
- **Description**: Contains functions to handle the shell’s built-in commands.
- **Responsibilities**:
  - Handles built-in commands such as `exit`, `cd`, `env`, and `pid`.
  - Implements specific behaviors for these commands without using external processes.

### 3. `pid.c`
- **Description**: This file contains functions related to process ID (PID) handling.
- **Responsibilities**:
  - Provides a function to retrieve the current process ID using `getpid()`.
  - Used to display the PID in the shell when the user invokes the `pid` command.

### 4. `shell.h`
- **Description**: Header file containing function declarations and necessary library includes for the project.
- **Responsibilities**:
  - Declares the functions implemented in `shell_main.c`, `builtins.c`, and `pid.c`.
  - Includes standard libraries (such as `stdio.h`, `stdlib.h`, `string.h`, etc.).


---

## Authors

[Benjamin Estrada](https://github.com/Aluranae)  
[Nawfel](https://github.com/nawfel83)  
[Warren](https://github.com/Warrre)