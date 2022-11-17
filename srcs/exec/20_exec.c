#include "minishell.h"

void test(void)
{
	printf("ok");
}

char	*get_right_path(t_tok_lst *t_tok_lst, char **envp)
{
	char	*path;

	path = NULL;
	return (path);
}

void	simple_exec(t_tok_lst *tok_lst, char **envp)
{
	(void)tok_lst;
	char	*path;

	path = get_right_path(tok_lst, env_list);
	execve(path, tok_lst->args->content, envp);
}

void	pipex_exec(t_tok_lst *tok_lst, char **envp)
{
	(void)tok_lst;
}

void exec(t_tok_lst *tok_lst, char	**envp)
{
	int	lst_size;

	lst_size = ft_lstsize_token(tok_lst);
	printf("token size: %d\n", lst_size);
	printf("token 1: %s\n", tok_lst->args->content);
	printf("token 2: %s\n", tok_lst->next->args->content);
	if (lst_size == 1)
		simple_exec(tok_lst, envp);
	else if (lst_size > 1)
		pipex_exec(tok_lst, envp);
}

	// char **args;

	// while (tok_lst)
	// {
		
	// 	tok_lst = tok_lst->next;
	// }