/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsharma <tsharma@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 10:45:10 by toshsharma        #+#    #+#             */
/*   Updated: 2023/03/01 16:56:47 by tsharma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#define MAX_ARGS 20
//norminette-ignore
int	main(int argc, char *argv[])
{
    char *args[MAX_ARGS];   // array to store command and its arguments
    int num_pipes = 0;      // number of pipes in command
    int pipes[2 * MAX_ARGS]; // array to store file descriptors for pipes
    int cmd_num = 0;        // current command number in pipeline

    // Parse command line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "|") == 0) {
            // add null terminator to end of current command's arguments
            args[num_pipes] = NULL;
            num_pipes++;
            cmd_num++;
        } else {
            // add argument to current command
            args[i-num_pipes-1] = argv[i];
        }
    }
    // add null terminator to end of last command's arguments
    args[argc-num_pipes-1] = NULL;
    for (int i = 0; i < num_pipes; i++)
    { /** pipe_count */
        if (pipe(pipes + i*2) < 0) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }

    int pid;
    int fd_in = 0; // file descriptor for input to first command
    int fd_out = 1; // file descriptor for output from last command

    // run each command in pipeline
    for (int i = 0; i <= num_pipes; i++) {
        // redirect input to current command from previous command's output
        dup2(fd_in, 0);

        // redirect output from current command to next command's input
        if (i < num_pipes) {
            dup2(pipes[i*2+1], 1);
        } else {
            // last command in pipeline writes output to standard output
            fd_out = 1;
        }

        // close unused file descriptors
        for (int j = 0; j < 2*num_pipes; j++) {
            if (j != fd_in && j != fd_out && j != pipes[i*2] && j != pipes[i*2+1]) {
                close(pipes[j]);
            }
        }

        // fork child process to run current command
        if ((pid = fork()) < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // child process runs current command
            if (execvp(args[cmd_num], args) < 0) {
                perror("execvp");
                exit(EXIT_FAILURE);
            }
        }

        // parent process waits for child process to finish
        if (waitpid(pid, NULL, 0) < 0) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }

        // close input file descriptor if it is not standard input
        if (fd_in != 0) {
            close(fd_in);
        }

        // save output file descriptor for next command in pipeline
        fd_in = pipes[i*2];
    }

    // close output file descriptor if it is not standard output
    if (fd_out != 1) {
        close(fd_out);
    }

    return 0;
}
