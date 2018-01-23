#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <editline/readline.h>
#include "mpc.h"


/* Declare a buffer for user input */
const char* QUIT = "quit";

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
	puts("blit version 0.0.0.0.1");
	puts("Ctrl+c to exit\n");

	/* Continuous loop */
	while(1) {

		/* Output prompt */

		/* Output our prompt and get input from user */
		char* input = readline("blit> ");

		/* Add input to history */
		add_history(input);
		
		/* Free retrieved input */
		free(input);

		/* End loop */
		if (strncmp(input, QUIT, 4) == 0) {
			printf("Bye for now.\n");
			break;
		}
			
		/* Echo input back to user */
		printf("You said, '%s'\n", input);
		}

  /* Undefine and Delete our parsers */
  mpc_cleanup(4, Number, Operator, Expr, Blit);

}
