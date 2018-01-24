#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <editline/readline.h>
#include "mpc.h"

/* Exit command for user to quit REPL */
const char* QUIT = "quit";

/* Use operator string to see which operation to perform */
long eval_op(long x, char* op, long y) {
  if (strcmp(op, "+") == 0) { return x + y; }
  if (strcmp(op, "-") == 0) { return x - y; }
  if (strcmp(op, "*") == 0) { return x * y; }
  if (strcmp(op, "/") == 0) { return x / y; }
  return 0;
}

/* RECURSIVE FUNCTION */
long eval(mpc_ast_t* t) {
  /* If tagged as a number, return it immediately */
  if (strstr(t->tag, "number")) {
    return atoi(t->contents);
  }
  /* The operator is always the second child */
  char* op = t->children[1]->contents;

  /* We store the third child in 'x' */
  long x = eval(t->children[2]);

  /* Iterate the remaining children and combining */
  int i = 3;
  while (strstr(t->children[i]->tag, "expr")) {
    x = eval_op(x, op, eval(t->children[i]));
    i++;
  }

  return x;
}

int main(int argc, char** argv) {

  /* Create some parsers */
  mpc_parser_t* Number = mpc_new("number");
  mpc_parser_t* Operator = mpc_new("operator");
  mpc_parser_t* Expr = mpc_new("expr");
  mpc_parser_t* Blit = mpc_new("blit");

  /* Define parsers */
  mpca_lang(MPCA_LANG_DEFAULT,
      " \
      number: /-?[0-9]+/ ; \
      operator: '+' | '-' | '*' | '/' ; \
      expr: <number> | '(' <operator> <expr>+ ')' ; \
      blit: /^/ <operator> <expr>+ /$/ ; \
      ",
      Number, Operator, Expr, Blit);

	/* Print version and exit information */
	puts("blit version 0.0.0.0.2");
	puts("Ctrl+c or 'quit' to exit\n");

	/* Continuous loop */
	while(1) {

		char* input = readline("blit> ");
		add_history(input);
		
    /* Exit the REPL loop */
		if (strncmp(input, QUIT, 4) == 0) {
			printf("Bye for now.\n");
			break;
		}		

    /* Attemmpt to parse user input */
    mpc_result_t r;
    if (mpc_parse("<stdin>", input, Blit, &r)) {

      long result = eval(r.output);
      printf("%li\n", result);
      mpc_ast_delete(r.output);
      
    } else { 
      /* Otherwise print the error */
      mpc_err_print(r.error);
      mpc_err_delete(r.error);
    }

		/* Free retrieved input */
		free(input);

		}

  /* Undefine and Delete our parsers */
  mpc_cleanup(4, Number, Operator, Expr, Blit);

}
