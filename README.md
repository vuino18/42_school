# 42 school - common core

this repository contains my implementation of the projects in the **42 school common core** curriculum. the projects focus on rigor, deep understanding of c programming, memory management and unix systems logic

# 🛠️ project overview

|  project name  |  description  |  key concepts  |
|-----------|---------------|----------------|
|  **libft**    | my own standard c library | libc, memory, strings |
| **ft_printf**  | re-implementation of the `printf` | variadic arguments and functions, formatting |
| **get_next_line**  | reading a line from a file descriptor | static variables, buffers |
| **born2beroot**  | setting up a secure debian server | virtualization, `sudo`, `ssh` |
| **push_swap**  | sorting data on a stock with limited moves | algorithms, stacks and optimization |
| **so_long**  | a simple 2d game using the minilibX | graphics, event handling |
| **pipex**  | handling unix pipes and redirections | processes, `execve`, pipes |
| **philosophers**  | the dining philosophers problem | synchronization, multithreading and mutexes |
| **minishell** | building a simple shell | parsing, signals, file descriptors |

# 🚀 featured projects
### minishell

the most complex project of the core, involving the creation of a mini-bash. it handles:

- **interactive prompt**: displays a prompt when waiting for a new command

- **command execution**: executes system binaries found in the PATH or via absolute/relative paths

- **builtins**: implementation of `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`.

- #### redirections:

    * **<** redirects input

    * **\>** redirects output (truncate)

    * **<<** heredoc (stops at a delimiter)

    * **\>>** redirects output (append)

- **pipes**: **|** connects the output of one command to the input of the next.

- **environment variables**: handles **$expansions** and **$?** for the last exit status.

- **signals**: proper handling of ctrl-c, ctrl-d, and ctrl-\

### philosophers

a project dedicated to the basics of threading a process. it focuses on:

* solving the "dining philosophers" problem

* avoiding deadlocks and race conditions

* real-time monitoring and synchronization using mutexes

---

## 📝 methodology
each project follows the 42 norm, a strict coding standard that promotes readability and limits function length. most projects are written in c, prioritizing:

1. **zero memory leaks**: all heap-allocated memory is properly freed

2. **robustness**: handling edge cases, invalid inputs, and system call failures

3. **efficiency**: optimized algorithms to meet strict performance benchmarks

---

## 📂 installation and usage
to explore a specific project, navigate to its directory and use the makefile:

```Bash
git clone https://github.com/your_username/42_school.git
cd 42_school/project_name
make
```

---

## 👤 author
* `vuino18` (gitHub: [vuino18](https://github.com/vuino18/))

* 42 school login: `elino`

---

*this repository is for educational purposes only. if you are a 42 student, always remember to follow the principles of peer-to-peer learning and academic integrity*
