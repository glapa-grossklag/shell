# What is this?

A simple shell, written to learn the trio of system calls necessary to control
processes: `fork()`, `exec()`, and `wait()`.

Currently, there are no built-ins (i.e., no `cd`, `pwd`, `help`, etc.) no
redirection (i.e., no `|`, `>`, `<`, etc.), and no quoting (i.e., `echo 'Hello,
world!'` will actually print `'Hello, world!'` not `Hello, world!`.) But, at
least it works!

# How does it work?

The `fork()` system call is used to create a new process. It does this by
creating a copy of the calling process, with a few differences. The child
process has its own address space, registers, and instruction pointer.

The child process's call to `fork()` returns 0 as it's process identifier (PID).
The parent process's call to `fork()` returns the child's PID.

```c
int main(void) {
	pid_t pid = fork();

	if (pid < 0) {
		printf("failed to fork\n");
	} else if (pid == 0) {
		printf("(%d) I'm a child.\n", getpid());
	} else {
		printf("(%d) I'm a parent.\n", getpid());
		printf("(%d) My child is %d\n", getpid(), pid);
	}
}
```

The `wait()` system call pauses execution of the parent process until the child
process completes execution.

In the following program, the child process will run before the parent process,
rather than the order being determined by the scheduler.

```c
int main(void) {
	pid_t pid = fork();

	if (pid < 0) {
		printf("failed to fork\n");
	} else if (pid == 0) {
		printf("(%d) I'm a child.\n", getpid());
	} else {
		wait(NULL);
		printf("(%d) I'm a parent.\n", getpid());
		printf("(%d) My child is %d\n", getpid(), pid);
	}
}
```

The `exec()` system call transforms the current process into one running the
given program -- therefore nothing after the call to `exec()` should be expected
to execute under normal conditions, which is why a `fork()` is necessary.

# How do I use it?

1. Compile the shell using `make`.
2. Enter the shell with `./shell`.
3. Profit.
