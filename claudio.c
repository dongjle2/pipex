#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define READ_END 0
#define WRITE_END 1

int main() {
	int pipefd[2];
	char buffer[4096];
	pid_t pid;

	// Create a pipe
	if (pipe(pipefd) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	pid = fork();
	if (pid == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	} else if (pid == 0) {
		// Child process
		close(pipefd[READ_END]); // Close the read end of the pipe

		// Redirect stdout to the write end of the pipe
		if (dup2(pipefd[WRITE_END], STDOUT_FILENO) == -1) {
			perror("dup2");
			exit(EXIT_FAILURE);
		}

		close(pipefd[WRITE_END]); // Close the write end of the pipe (not needed anymore)

		// Execute the "echo" command with the $PATH argument
		char *args[] = {"/bin/echo", "${PATH}", NULL};
		char *env[] = {"PATH=/bin:/usr/bin", NULL}; // Set the PATH environment variable

		execve("/bin/echo", args, env);

		// If execve() returns, it means an error occurred
		perror("execve");
		exit(EXIT_FAILURE);
	} else {
		// Parent process
		close(pipefd[WRITE_END]); // Close the write end of the pipe

		// Read the output from the pipe
		ssize_t bytes_read = read(pipefd[READ_END], buffer, sizeof(buffer) - 1);
		if (bytes_read == -1) {
			perror("read");
			exit(EXIT_FAILURE);
		}

		buffer[bytes_read] = '\0'; // Add a null terminator

		printf("PATH from child process:\n%s\n", buffer);

		close(pipefd[READ_END]); // Close the read end of the pipe

		// Wait for the child process to finish
		int status;
		if (waitpid(pid, &status, 0) == -1) {
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
	}

	return 0;
}