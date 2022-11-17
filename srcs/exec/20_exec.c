#include "minishell.h"

void test(void)
{
	printf("ok");
}

char	*get_right_path(t_tok_lst *t_tok_lst, t_env_lst *env_list)
{
	char	*path;

	path = NULL;
	printf("pathname: %s\n", env_list->name);
	printf("pathvalue: %s\n", env_list->value);
	return (path);
}

void	simple_exec(t_tok_lst *tok_lst, t_env_lst *env_list)
{
	(void)tok_lst;
	char	*path;

	path = get_right_path(tok_lst, env_list);
	// execve(path, tok_lst->args->content, envp);
}

void	pipex_exec(t_tok_lst *tok_lst, t_env_lst *env_list)
{
	(void)tok_lst;
}

void exec(t_tok_lst *tok_lst, t_env_lst *env_list)
{
	int	lst_size;

	lst_size = ft_lstsize_token(tok_lst);
	printf("token size: %d\n", lst_size);
	printf("token 1: %s\n", tok_lst->args->content);
	printf("token 2: %s\n", tok_lst->next->args->content);
	if (lst_size == 1)
		simple_exec(tok_lst, env_list);
	else if (lst_size > 1)
		pipex_exec(tok_lst, env_list);
}

	// char **args;

	// while (tok_lst)
	// {
		
	// 	tok_lst = tok_lst->next;
	// }