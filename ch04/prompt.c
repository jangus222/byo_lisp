#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <editline/readline.h>
// #include <editline/history.h>

/* Declare a buffer for user input */
const int BUF_SIZE = 2048;
// static char input[BUF_SIZE];
const char* QUIT = "quit";

int main(int argc, char** argv) {

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

}
