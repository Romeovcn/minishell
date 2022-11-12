#include "minishell.h"

char *get_env_name(char *env, t_mal_lst **mal_lst)
{
	int i;
	char *name;

	i = 0;
	while (env[i])
	{
		if (env[i] == '=')
			break ;
		i++;
	}
	if (env[i] != '=')
		return (NULL);
	name = malloc((i + 1) * sizeof(char));
	if (!name)
		return (NULL);
	lstadd_back_malloc(mal_lst, lstnew_malloc(name));
	i = 0;
	while (env[i])
	{
		if (env[i] == '=')
			break ;
		name[i] = env[i];
		i++;
	}
	name[i] = 0;
	return (name);
}

void get_env(t_env_lst **env_lst, char **env, t_mal_lst **mal_lst)
{
	int i;
	char *value;
	char *name;

	i = 0;
	while (env[i])
	{
		name = get_env_name(env[i], mal_lst);
		value = getenv(name);
		lstadd_back_env(env_lst, lstnew_env(name, value, mal_lst));
		i++;
	}
}

void export_env(t_env_lst **env_lst, t_mal_lst **mal_lst, char **options)
{
	t_env_lst *head;
	char *value;
	char *name;
	int i;

	i = 1;
	head = *env_lst;
	while (options[i])
	{
		name = get_env_name(options[i], mal_lst);
		if (!name)
		{
			i++;
			continue ;
		}
		i++;
	}
}

// void unset_env(t_env_lst *env_lst, char *name)
// {
// 	t_env_lst *previous;

// 	previous = NULL;
// 	while (env_lst)
// 	{
// 		if (env_name_match(env_lst->content, name))
// 		{
// 			printf("TROUVE = %s\n", env_lst->content);
// 			previous->next = env_lst->next;
// 			return ;
// 		}
// 		previous = env_lst;
// 		env_lst = env_lst->next;
// 	}
// }

char *get_env_value(char *name, t_env_lst *env_lst)
{
	char *env_value;

	while (env_lst)
	{
		if (ft_strmatch(name, env_lst->name))
			return (env_lst->value);
		env_lst = env_lst->next;
	}
	return (NULL);
}