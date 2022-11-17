#include "minishell.h"

char	*ft_newstrjoin(char *s1, char *s2)
{
	char	*newstr;

	newstr = ft_strjoin(s1, s2);
	free(s1);
	return (newstr);
}
