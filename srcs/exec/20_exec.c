#include "minishell.h"

void	simple_exec(t_tok_lst *tok_lst, char **envp, t_mal_lst *mal_lst)
{
	char	*path;
	char	**arg;

	// path = getenv("PATH");
	// printf("path: %s\n", path);
	// printf("test: %s\n", tok_lst->args->content);
	if (tok_lst->output_fd < 2 && tok_lst->input_fd < 2)
	{
		path = find_right_access(getenv("PATH"), tok_lst->args);
		printf("path: %s\n", path);
		arg = lst_to_str_array(tok_lst->args, &mal_lst);
		execve(path, arg, envp);
	}
	// free(path);
}

void	pipex_exec(t_tok_lst *tok_lst, char **envp, t_mal_lst *mal_lst)
{
	(void)tok_lst;
}

void exec(t_tok_lst *tok_lst, char	**envp, t_mal_lst *mal_lst)
{
	int			lst_size;

	lst_size = ft_lstsize_token(tok_lst);
	printf("token size: %d\n", lst_size);
	printf("token 1: %s\n", tok_lst->args->content);
	// printf("token 2: %s\n", tok_lst->next->args->content);
	if (lst_size == 1)
		simple_exec(tok_lst, envp, mal_lst);
	else if (lst_size > 1)
		pipex_exec(tok_lst, envp, mal_lst);
}

	// char **args;

	// while (tok_lst)
	// {
		
	// 	tok_lst = tok_lst->next;
	// }
