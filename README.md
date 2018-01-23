Build Your Own Lisp
http://buildyourownlisp.com/

Learn C and build your own programming language in 1000 lines of code!

Use the following basic command for compiling a single file:

`cc -std=c99 -g -O0 -Wall <filename>.c -o <filename>.out`

And to compile with the readline library, link in edit:

`cc -std=c99 -g -O0 -Wall prompt.c -ledit -o prompt.out`

Add mpc library:

`cc -std=c99 -g -O0 -Wall parsing.c mpc.c -ledit -lm -o parsing.out`

