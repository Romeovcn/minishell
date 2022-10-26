#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main()
{
	char history[1000000];
	char *str;
	while (str = readline("ICI="))
	{
		add_history(str);
		printf("str=%s\n", str);
		free(str);
	}
}