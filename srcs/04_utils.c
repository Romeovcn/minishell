#include "minishell.h"

void free_string_array(char **array)
{
	int i;

	i = 0;
	while (array[i])
		free(array[i++]);
	if (array)
		free(array);
	printf("array freed\n");
}