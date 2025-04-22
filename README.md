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

**Simple Shell** est un interpréteur de commandes écrit en C, qui permet d'exécuter des commandes dans un environnement Unix, comme un vrai terminal. Il prend en charge :

- **Les modes interactif et non-interactif** : Le shell peut fonctionner à la fois dans un terminal interactif, où l'utilisateur peut entrer des commandes manuellement, et dans un mode non-interactif, où il exécute des commandes passées via un fichier ou un pipe.
  
- **Les commandes simples** : Il permet l'exécution de commandes de base comme `/bin/ls`, `/bin/pwd`, etc., exactement comme un shell standard.

- **Les commandes internes** : Le shell implémente certaines commandes internes, comme `exit` (pour quitter le shell), `cd` (pour changer de répertoire), `env` (pour afficher les variables d'environnement), et `pid` (pour afficher le PID du processus actuel).

- **La gestion des erreurs** : Le shell gère les erreurs telles que les commandes non trouvées, et affiche des messages d'erreur clairs en indiquant le nom du programme suivi de l'erreur spécifique. Exemple : `./hsh: 1: qwerty: not found`.

- **L’exécution via `fork` et `execve`** : Lorsqu'une commande est entrée, le shell crée un processus fils avec `fork()`, puis exécute la commande dans ce processus via `execve()`. Si la commande est interne, elle est traitée directement par le shell sans créer de processus fils.

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


## The Flowchart of Simple Shell


## File organisation

Le projet est structuré en plusieurs fichiers pour organiser le code de manière modulaire et maintenir une bonne lisibilité. Voici l'organisation des fichiers du projet :

### 1. `shell_main.c`
- **Description** : Point d'entrée principal du programme. Ce fichier contient la boucle principale du shell et gère l'interaction avec l'utilisateur.
- **Responsabilités** :
  - Affichage du prompt si le shell est en mode interactif.
  - Lecture de l'entrée de l'utilisateur avec `getline()`.
  - Découpage de l'entrée en arguments avec `strtok()`.
  - Exécution des commandes internes ou externes (via `fork()` et `execve()`).

### 2. `builtins.c`
- **Description** : Contient les fonctions pour gérer les commandes internes du shell.
- **Responsabilités** :
  - Gère les commandes internes comme `exit`, `cd`, `env`, et `pid`.
  - Implémente les comportements spécifiques de ces commandes sans faire appel à un processus externe.

### 3. `pid.c`
- **Description** : Ce fichier contient des fonctions liées à la gestion du PID (identifiant de processus).
- **Responsabilités** :
  - Fonction pour obtenir le PID du processus actuel via `getpid()`.
  - Utilisé pour afficher le PID dans le shell lorsque l'utilisateur demande la commande `pid`.

### 4. `shell.h`
- **Description** : Fichier d'en-tête contenant les déclarations de fonctions et les bibliothèques nécessaires pour le projet.
- **Responsabilités** :
  - Déclarations des fonctions présentes dans `shell_main.c`, `builtins.c`, et `pid.c`.
  - Inclusion des bibliothèques standard nécessaires (comme `stdio.h`, `stdlib.h`, `string.h`, etc.).

---

## Authors

[Benjamin Estrada](https://github.com/Aluranae)  
[Nawfel](https://github.com/nawfel83)  
[Warren](https://github.com/Warrre)