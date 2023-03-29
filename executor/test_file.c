/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsharma <tsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 10:45:10 by toshsharma        #+#    #+#             */
/*   Updated: 2023/03/03 21:00:51 by tsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_CMD_LEN 1024

int main(int argc, char *argv[]) {
    int prev_read_end = STDIN_FILENO;  // Initialize the read end of the previous pipe to stdin

    for (int i = 0; i < argc; i++) {
        int pipe_fds[2];
        if (pipe(pipe_fds) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {  // Child process
            if (i != 0) {  // Not the first command in the pipeline
                dup2(prev_read_end, STDIN_FILENO);  // Redirect input to read end of previous pipe
                close(prev_read_end);  // Close write end of previous pipe
            }

            if (i != argc - 1) {  // Not the last command in the pipeline
                dup2(pipe_fds[1], STDOUT_FILENO);  // Redirect output to write end of current pipe
                close(pipe_fds[0]);  // Close read end of current pipe
            }
            // Close all other file descriptors except stdin, stdout, and the pipe file descriptors
            for (int j = 0; j < argc; j++) {
                if (j != i && j != i - 1) {
                    close(pipe_fds[0]);
                    close(pipe_fds[1]);
                    close(prev_read_end);
                }
            }

            char *cmd = argv[i];
            char *args[2] = {cmd, NULL};
            execvp(cmd, args);
            perror("execvp");
            exit(EXIT_FAILURE);
        } else {  // Parent process
            close(pipe_fds[1]);  // Close write end of current pipe (if not the last command in pipeline)
            prev_read_end = pipe_fds[0];  // Save read end of current pipe as read end of next pipe (if there is a next command)
        }
    }

    // Wait for all child processes to finish
    int status;
    for (int i = 0; i < argc; i++) {
        wait(&status);
    }

    return EXIT_SUCCESS;
}
