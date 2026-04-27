*This project has been created as part of the 42 curriculum by elino and alcarval*

## Description

The Minishell project is a fundamental exercise in creating a simple shell. It aims to provide a deeper understanding of process creation, command execution, and system calls. The goal is to recreate a simplified version of Bash, handling command parsing, environment variables, and redirections while ensuring a leak-free and robust execution environment

### Features

- **Interactive Prompt**: Displays a prompt when waiting for a new command

- **Command Execution**: Executes system binaries found in the PATH or via absolute/relative paths

- **Builtins**: Implementation of `echo`, `cd`, `pwd`, `export`, `unset`, `env` and `exit`.

- #### Redirections:

    * **<** redirects input

    * **\>** redirects output (truncate)

    * **<<** heredoc (stops at a delimiter)

    * **\>>** redirects output (append)

- **Pipes**: **|** connects the output of one command to the input of the next.

- **Environment Variables**: Handles **$** expansions and **$?** for the last exit status.

- **Signals**: Proper handling of Ctrl-C, Ctrl-D, and Ctrl-\

---

## Instructions

#### Build
To compile the executable, run:
```bash
make
```

#### Run
Launch the shell by executing the binary:
```bash
./minishell
```
### Program Usage
Once inside minishell, you can interact with it just like a standard terminal:

| Action | Example | 
|---|---|
| Execute a command | ls -la |
| Use a pipe | cat file.txt|
| Redirect output | echo "Hello World" > hello.txt |
| Environment vars | echo $USER |
| Exit the shell | exit or Ctrl-D |

---

## Resources

- [Guia do minishell - eusourenan](https://github.com/eusourenan/guia_minishell)
- KERRISK, Michael, *The Linux Programming Interface*: A Linux and UNIX® System Programming Handbook. San Francisco: No Starch Press, 2010
- SHOTTS, William, *The Linux Command Line*: A Complete Introduction. 2nd Edition. San Francisco: No Starch Press, 2019
- ARAUJO, Blau, *Pequeno Manual do Programador GNU/Bash*. Sao Paulo: UICLAP, 2023
- [Minishell: *Building a mini-bash (a 42 project)* - zlaarous](https://medium.com/@zouhairlrs/minishell-building-a-mini-bash-a-42-project-5dc20d671fbb)

---

## AI Assistance

This project was developed by elino and alcarval. The core logic — including the parsing pipeline (lexer, expander, parser), pipeline execution, process forking, redirections, builtins, and environment management — was implemented by the team.

Claude (Anthropic) was used in the final stages of the project to assist with the following:
Code review and bug fixing. The AI audited the existing codebase and identified several critical bugs: 
* signal handlers being overridden by readline's internal `SA_RESTART` behavior during heredoc input;
* incorrect NULL-pointer handling in the environment list when the head was empty; 
* a memory leak in `env_to_envp on partial` allocation failure; 
* and `export.c` mutating parser-owned memory by writing directly into argv[i].

**Memory correctness**

The AI reviewed all allocation and deallocation paths, ensuring every `malloc` had a corresponding free on all code paths, that partial-allocation failures were handled cleanly, and that file descriptors were closed after use in pipe and heredoc scenarios.

**Norminette compliance** 

Several files exceeded the 25-line function body limit or the 5-function-per-file limit. The AI proposed how to split files and extract helper functions to bring the codebase into compliance without changing behavior.

**Error message accuracy**

The AI corrected exec_external to distinguish between three distinct error cases — *file not found*, *permission denied*, and *command not found* — matching Bash's exact output and exit codes (126 vs 127).

**Heredoc signal handling**

The AI worked through several iterations of the heredoc SIGINT problem, ultimately arriving at the correct architecture: forking a child process with `SIGINT` = `SIG_DFL` to read heredoc input using `read(2)` directly (avoiding readline's terminal mode changes), with the parent detecting interruption via `WIFSIGNALED` after `waitpid`.

All final decisions, integration, and testing were done by the project authors.
