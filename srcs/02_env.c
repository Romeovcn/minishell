#include "minishell.h"

void get_env(t_env_lst **env_lst, char **env, t_mal_lst **mal_lst)
{
	int i;

	i = 0;
	while (env[i])
	{
		lstadd_back_env(env_lst, lstnew_env(env[i], mal_lst));
		i++;
	}
}

char *get_env_value(char *name, t_env_lst *env_lst)
{
	char *env_value;

	while (env_lst)
	{
		if (!ft_strncmp(env_lst->content, name, ft_strlen(name)))
		{
			env_value = env_lst->content;
			while (*env_value)
			{
				if (*env_value == '=')
					return (env_value++, env_value);
				env_value++;
			}
		}
		env_lst = env_lst->next;
	}
	return ("");
}