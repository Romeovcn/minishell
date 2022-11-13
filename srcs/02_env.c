#include "minishell.h"

char *get_env_name(char *env, t_mal_lst **mal_lst)
{
	int i;
	char *name;

	i = 0;
	if (env[0] == '=')
		return (NULL);
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

void get_env_lst(t_env_lst **env_lst, char **env, t_mal_lst **mal_lst)
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

void change_env_value(char *name, char *new_value, t_env_lst *env_lst)
{
	while (env_lst)
	{
		if (ft_strmatch(env_lst->name, name))
		{
			env_lst->value = new_value;
			break ;
		}
		env_lst = env_lst->next;
	}
}

void export_env(t_env_lst **env_lst, t_mal_lst **mal_lst, char **options)
{
	char *value_found;
	char *name;
	int i;

	i = 1;
	while (options[i])
	{
		name = get_env_name(options[i], mal_lst);
		if (name)
		{
			while (*(options[i]))
			{
				if (*(options[i]) == '=' && *(options[i])++)
					break ;
				*(options[i])++;
			}
			value_found = get_env_value(name, *env_lst);
			if (value_found)
				change_env_value(name, options[i], *env_lst);
			else
				lstadd_back_env(env_lst, lstnew_env(name, options[i], mal_lst));
		}
		i++;
	}
}

void unset_env(t_env_lst **env_lst, char **options)
{
	t_env_lst	*tmp_previous;
	t_env_lst	*env_head;
	int			i;

	i = 1;
	while (options[i])
	{
		if (ft_strchr(options[i], '='))
		{
			printf("unset: '%s': not a valid identifier\n", options[i++]);
			continue ;
		}
		tmp_previous = NULL;
		env_head = *env_lst;
		while (env_head)
		{
			if (ft_strmatch(options[i], env_head->name))
			{
				if (!tmp_previous)
					*env_lst = (*env_lst)->next;
				else
					tmp_previous->next = env_head->next;
				break ;
			}
			tmp_previous = env_head;
			env_head = env_head->next;
		}
		i++;
	}
}

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