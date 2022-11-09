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

char	*ft_strjoin_char(char const *s1, char c)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = malloc((ft_strlen(s1) + 1 + 1) * sizeof(char));
	while (s1[i])
		result[j++] = s1[i++];
	i = 0;
	result[j++] = c;
	result[j] = 0;
	return (result);
}
