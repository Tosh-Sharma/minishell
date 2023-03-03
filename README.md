# minishell

## Multi-pipe execution pseudocode

- For each command in the pipeline:
-    Create a pipe with file descriptors pipe_fds
-    Fork a child process to run the current command
-    If this is the child process:
-        If this is not the first command in the pipeline:
-            Redirect input to the read end of the previous pipe
-            Close the write end of the previous pipe
-        If this is not the last command in the pipeline:
-            Redirect output to the write end of the current pipe
-            Close the read end of the current pipe
-        Close all other file descriptors (including the unused read and write ends of the pipes)
-        Run the command

-    If this is the parent process:
-        Close the write end of the current pipe (if it's not the last command in the pipeline)
-        Save the read end of the current pipe as the read end of the next pipe (if there is a next command in the pipeline)

- Wait for all child processes to finish
- Note that with only 3 file descriptors, we have to use dup or dup2 to redirect input and output to the appropriate file descriptor. The key difference with the 3-file-descriptor implementation is that we need to be careful to close all file descriptors except for the ones we're using, so that we don't run out of file descriptors