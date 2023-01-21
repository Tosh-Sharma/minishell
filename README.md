# minishell

## How I envision this project coming to life

- Part 1: Getting input from the terminal
- Part 2: If its a signal, handling it in that way
- Part 3: If its not a signal, tokenize the input
What is tokenize?
It is to split into words the input being passed.
Can be treated as either pairs of strings or individual strings. TBD.
- Part 4: Once you have tokenized the input, next step is lexting
What is "lexting it up"?
It is understanding each and every input and then acting accordingly on the input.
It means identifying the pipe operators, the executables and the I/O redirection inputs. The inputs that equate to exiting, pausing and so on and allowing the code to react according to this input.