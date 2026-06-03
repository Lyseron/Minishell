*This project has been created as part of the 42 curriculum by [lyaberge], [jercleme]*

# Minishell

## Description
The minishell project consists of reproducing a simplified version of UNIX shell in C.  
It implements core shell behaviors such as:
- PIPES -> (|)
- REDIRECTIONS -> (< > << >>)
- Environnement variables -> ($VAR)

Our project is structured into four main components that work together:  
### Lexer :
The lexer transforms the user input into a linked list of tokens.
Each node of the list contains:
- The string extracted from the input
- It's associated type (enum)

To achieve this, we use a state machine with three distinct states:
1. **SQ (Single Quote)**
	- Everything is taken literally and treated a type: WORD
2. **DQ (Double Quote)** 
	- everything is taken literally as a -> WORD
	- later the $value will be expand
3. **NO_Q (No Quote)**
	- '|' -> PIPE
	- '>' -> REDIR_OUT
	- '<' -> REDIR_IN
	- '>>' -> APPEND
	- '<<' -> HEREDOC
	- "input" -> WORD

Each token is then stored as a node in the linked list, so that they contain the string of the input and its type for the parsing phase.

### Parsing :
The parsing phase parse the user input, by building an AST (Abstract Syntax Tree).
This structure allows us to represent the command in a hierarchical way while respacting operator priority.

**Priority of operator :**
1. The **PIPE** -> root of the AST
2. The **REDIRS** -> branches of the AST
3. The **CMDS** -> leaf of the AST

The AST is built recursively:
1. Search for the **last pipe** in the token list
- if found:
	- create a **PIPE** node
	- build:
		- left subtree -> token before the pipe
		- right subtree -> tokens after the pipe
2. If no pipe is found, search for the **last redirs**
- if found:
	- create a redirs node
	- build:
		- left subtree -> the cmd
		- right subtree -> the file or delimiter target
3. If no operator is found:
- create a **cmd node**

We always search for the last occurence of an operator to respect the shell behavior.


### Expansion

After the parsing we scan the input character by character.
A state machine is used to determine whether a variable must be expanded or not, depending on the current quoting context :
- In the **NO_Q state** && **DOUBLE_Q state**:
	- if a '$' is encountered, the variable is expanded and its value is added to the new string.
	- otherwize, the character is added to the new string.
- In the **SINGLE_Q state** :
	- nothing is expanded, the input stays the same.

**Heredoc** expansion:
The expansion depends on wheter the delimiter is quoted or not:
- if the delimiter has **no quote**, variables are expanded inside the heredoc content.
- if the delimiter **is quoted**, the variables are not expanded.

### Exec :

The execution phase is based on the AST stucture and is implemented using recursion.
Execution follows the structures of the AST:
- if the node is a **PIPE** -> create a pipe() and execute both sides
- if the node is a **CMD** -> execute it in a child process

1. Pipe Execution:
if there is a PIPE node:
- we create a pipe using pipe()
	- **Left child :**
		- redirects STDOUT to the pipe write end using dup2()
		- write into the pipe
		- execute the cmd(s) in a child process
	- **Right child :**
		- redirects STDIN to the pipe read end using dup2()
		- read from the pipe
		- execute the cmd(s) in a child process
2. Redir Execution:
There is a redir if ast->redir exist:
- we create a pipe() to redirect the stdin/stdout depending on the redir_type
	- **Redir_out :**
		- redirects the STDOUT to the next input (file)
		- create the file if it does not exit
	- **Redir_in :**
		- redirects the STDIN from the next input (file)
	- **Append :**
		- redirects the STDOUT to the next input (file)
		- add a content to the file and create it if it does not exist
	- **Heredoc :**
		- create a pipe()
		- let the user enter input til the LIMITER
			- LIMITER -> the next input after the <<
		- redirects the STDOUT to write in the pipe
		- redirects the STDIN for the pipe to read

3. Command Execution

- if the command are builtin :
	- depending on the command we fork()
	- we executes the right function for the command

- otherwize :
	- we creates a child process using fork()
	- we executes the command with execve():
		- get the PATH: in the envp
		- concatene the path (/../../) with the ast->args
		- test if exist and is executable with access()

**Builtin cmd:**
- echo -> to print to the terinal.
	- -n option -> whithout a newline.
- cd -> to change directory.
- pwd -> to print the current working directory.
- exit -> to exit the minishell program.
- export -> to add a VAR in the environment.
- unset -> to remove a VAR from the evironment.
- env -> to print the environment.

**The parent process:**
- close unused fd to avoid leak
- wait for the child process using waitpid()
	- **Left child** -> to avoid zombie processes
	- **Right child** -> to retrieve the final exit status

**Exit Codes:**
- 0 -> success
- 1 -> execution error
- 126 -> command exist but is not executable
- 127 -> command not found
- 128 + signal -> process terminated by a signal

### Signal handling:

To dispatch signals correctly to the differnet part of the shell, we use sigaction.

- In the interactive shell (readline) :
	- Ctrl + C -> clear the current input line and display a new prompt.
	- Ctrl + \ -> does nothing in the parent but exit the child with the msg "Quit (core dumped)"
	- Ctrl + d -> is handled when readline is NULL as an EOF and exits the shell.
- In child process:
	- Ctrl + C -> the default behavior and interrupts the running command, once the child stops, the parent shell regains control and display a new prompt.
	- Ctrl + \ -> the default behavior

## Instruction

To create the executable ./minishell->
``` bash
	make 
```
Then to compile ->
``` bash
	./minishell
```

## Ressources

Subject:
- https://cdn.intra.42.fr/pdf/pdf/199852/en.subject.pdf

Minishell guide:
- https://trove.assistants.epita.fr/docs/42sh/guide/shell_architecture/

Explication fonction from the man and internet research:
- https://docs.google.com/spreadsheets/d/1x6aicQTQW7DzT590bejjM4xvTboWyAQe015CyGTaAqc/edit?gid=0#gid=0

Expansion:
- https://www.gnu.org/software/bash/manual/html_node/Shell-Parameter-Expansion.html

Manuel BASH:
- https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.pdf

Test :
- https://docs.google.com/spreadsheets/d/1BPW7k81LJPhGv2fbi35NIIoOC_mGZXQQJDnV0SjulFs/edit?gid=0#gid=0

To understand l'AST:
- https://ruslanspivak.com/lsbasi-part7/
- https://openclassrooms.com/forum/sujet/abstract-syntax-tree-compilateur

Youtube videos on redirection and communication between process :
- https://www.youtube.com/watch?v=Mqb2dVRe0uo
- https://www.youtube.com/watch?v=6u_iPGVkfZ4
- https://www.youtube.com/watch?v=tcYo6hipaSA
- ect .. the whole serie

For the redir:
- https://tuteurs.ens.fr/unix/shell/entreesortie.html

For the signal:
- https://beej.us/guide/bgc/html/split/signal-handling.html
- https://cs341.cs.illinois.edu/coursebook/Signals
- https://pubs.opengroup.org/onlinepubs/007904875/functions/sigaction.html

Multiple PDF explaining the lexing and parsing.
### AI uses :

I used AI as a learning and debugging tool, **never to generate code**. I always start my prompt with a strict no-code rule only explanations like it was another student teaching me.  
*I use it mostly for:*

- Gave me classes (no code in relation to minishell) on different new concept like AST, linked_chained, States Machine, dispatch tables ect.
- Gave explanations on the readline behavior (has the doc is not well written). And how to compile it on a Mac.
- Help create a test.sh to test multiple input, and compare it to the bash output, at the same time.
- Helped understand that readline has its own signal handling wich interfed with my own.
- Help me with the signal handling because readline intercept signals.
- Helped with a segfault I couldn't find.
- Help write this README in English.

Thank you.
