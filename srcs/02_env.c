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

void export_env(t_env_lst **env_lst, t_mal_lst **mal_lst, char **options)
{
	int i;
	int size;
	t_env_lst *head = *env_lst;
	i = 1;
	while (options[i])
	{
		size = 0;
		while (options[i][size])
		{
			if (options[i][size] == '=')
				break ;
			size++;
		}
		if (options[i][size] != '=')
		{
			i++;
			continue ;
		}
		while (head)
		{
			if (!ft_strncmp(head->content, options[i], size))
			{
				head->content = options[i];
				// printf("TROUVEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE\n");
				break ;
			}
			head = head->next;
		}
		if (!head)
			lstadd_back_env(env_lst, lstnew_env(options[i], mal_lst));
		head = *env_lst;
		// printf("SIZE=%d\n", size);
		i++;
	}
}

int env_name_match(char *env, char *env_to_delete)
{
	int i;

	i = 0;
	while (env[i])
	{
		if (env[i] == '=')
			break ;
		if (env[i] != env_to_delete[i])
			return (0);
		i++;
	}
	if (ft_strlen(env_to_delete) != i)
		return (0);
	return (1);
}

void unset_env(t_env_lst *env_lst, char *name)
{
	t_env_lst *previous;

	previous = NULL;
	while (env_lst)
	{
		// printf("%s = %d\n", env_lst->content, ft_strncmp(env_lst->content, name, ft_strlen(name)));
		// if (!ft_strncmp(env_lst->content, name, ft_strlen(name)))
		if (env_name_match(env_lst->content, name))
		{
			printf("TROUVE = %s\n", env_lst->content);
			previous->next = env_lst->next;
			return ;
		}
		previous = env_lst;
		env_lst = env_lst->next;
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