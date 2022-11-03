#include "minishell.h"

char **get_my_env(char **env)
{
	char **my_env;
	char *my_env_str;
	int i;

	i = 0;
	while (env[i])
		i++;
	my_env = malloc((i + 1) * sizeof(char *));
	if (!my_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		my_env[i] = ft_strdup(env[i]);
		i++;
	}
	my_env[i] = 0;
	return (my_env);
}

char **ft_export_env(char **env, char *new_line_str)
{
	char **my_env;
	int i;

	i = 0;
	while (env[i])
		i++;
	my_env = malloc((i + 2) * sizeof(char *));
	if (!my_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		my_env[i] = ft_strdup(env[i]);
		free(env[i]);
		i++;
	}
	my_env[i++] = ft_strdup(new_line_str);
	my_env[i] = 0;
	free(env);
	return (my_env);
}

// char **ft_unset_env(char **env, char *new_line_str)
// {
// 	char **my_env;
// 	int i;

// 	i = 0;
// 	while (env[i])
// 		i++;
// 	my_env = malloc((i + 2) * sizeof(char *));
// 	if (!my_env)
// 		return (NULL);
// 	i = 0;
// 	while (env[i])
// 	{
// 		my_env[i] = ft_strdup(env[i]);
// 		free(env[i]);
// 		i++;
// 	}
// 	my_env[i++] = ft_strdup(new_line_str);
// 	my_env[i] = 0;
// 	free(env);
// 	return (my_env);
// }