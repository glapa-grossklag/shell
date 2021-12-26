# Shell

A simple shell, written to learn the trio of system calls necessary to control
processes: `fork()`, `exec()`, and `wait()`.

Currently, there are no built-ins (i.e., no `cd`, `pwd`, `help`, etc.) no
redirection (i.e., no `|`, `>`, `<`, etc.), and no quoting (i.e., `echo 'Hello,
world!'` will actually print `'Hello, world!'` not `Hello, world!'`.) But, at
least it works!

# Usage

1. Compile the shell using `make`.
2. Enter the shell with `./shell`.
3. Profit.
