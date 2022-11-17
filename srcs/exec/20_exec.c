#include "minishell.h"

void test(void)
{
	printf("ok");
}

void	simple_exec(t_tok_lst *tok_lst, char **envp)
{
	char	*path;

	// path = getenv("PATH");
	// printf("path: %s\n", path);
	// printf("test: %s\n", tok_lst->args->content);
	path = find_right_access(getenv("PATH"), tok_lst->args);
	printf("path: %s\n", path);
	// execve(path, tok_lst->args->content, envp);
	// free(path);
}

void	pipex_exec(t_tok_lst *tok_lst, char **envp)
{
	(void)tok_lst;
}

void exec(t_tok_lst *tok_lst, char	**envp)
{
	int			lst_size;

	lst_size = ft_lstsize_token(tok_lst);
	printf("token size: %d\n", lst_size);
	printf("token 1: %s\n", tok_lst->args->content);
	// printf("token 2: %s\n", tok_lst->next->args->content);
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