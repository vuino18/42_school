# 42 School - Common Core

This repository contains my implementation of the projects in the **42 School Common Core** curriculum. The projects focus on rigor, deep understanding of C programming, memory management and Unix systems logic

# 🛠️ Project Overview

|  Project  |  Description  |  Key Concepts  |
|-----------|---------------|----------------|
|  libft    | My own standard C library | Libc, Memory, Strings |
| ft_printf | Re-implementation of the `printf` | Variadic arguments, Formatting |
| get_next_line | Reading a line from a file descriptor | Static variables, Buffers |
| born2beroot | Setting up a secure Debian server | Virtualization, Sudo, SSH |
| push_swap | Sorting data on a stock with limited moves | Algorithms, Optimization |
| so_long | A simple 2D game using the MinilibX | Graphics, Event handling |
| pipex | Handling Unix pipes and redirections | Processes, Execve, Pipes |
| philosophers | The Dining Philosophers problem | Multithreading, Mutexes |
| minishell | Building a simple shell | Parsing, Signals, File descriptors |

# 🚀 Featured Projects
### Minishell

The most complex project of the core, involving the creation of a mini-bash. It handles:

- **Interactive Prompt**: Displays a prompt when waiting for a new command

- **Command Execution**: Executes system binaries found in the PATH or via absolute/relative paths

- **Builtins**: Implementation of echo, cd, pwd, export, unset, env, and exit.

- #### Redirections:

    * **<** redirects input

    * **\>** redirects output (truncate)

    * **<<** heredoc (stops at a delimiter)

    * **\>>** redirects output (append)

- **Pipes**: **|** connects the output of one command to the input of the next.

- **Environment Variables**: Handles **$** expansions and **$?** for the last exit status.

- **Signals**: Proper handling of Ctrl-C, Ctrl-D, and Ctrl-\

### Philosophers

A project dedicated to the basics of threading a process. It focuses on:

* Solving the "Dining Philosophers" problem.

* Avoiding deadlocks and race conditions.

* Real-time monitoring and synchronization using Mutexes.

---

## 📝 Methodology
Each project follows the 42 Norm, a strict coding standard that promotes readability and limits function length. Most projects are written in C, prioritizing:

1. **Zero Memory Leaks**: All heap-allocated memory is properly freed.

2. **Robustness**: Handling edge cases, invalid inputs, and system call failures.

3. **Efficiency**: Optimized algorithms to meet strict performance benchmarks.

---

## 📂 Installation & Usage
To explore a specific project, navigate to its directory and use the Makefile:

```Bash
git clone https://github.com/YOUR_USERNAME/42_school.git
cd 42_school/project_name
make
```

---

## 👤 Author
* `vuino18` (GitHub: [vuino18](https://github.com/vuino18/))

* 42 School Login: `elino`

---

*This repository is for educational purposes only. If you are a 42 student, remember to follow the principles of peer-to-peer learning and academic integrity*
