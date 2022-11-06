#include "minishell.h"

char *get_prompt(char **env)
{
	char *prompt;
	int i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "USER=", 5))
			return prompt = env[i] + 5;
		i++;
	}
	return NULL;
}

int check_empty_line(char *readline_str)
{
	int size;
	int i;

	size = ft_strlen(readline_str);
	if (size == 0)
		return (1);
	i = 0;
	while (readline_str[i])
	{
		if (readline_str[i] == ' ' || readline_str[i] == '\t')
			i++;
		else
			break ;
	}
	if (i == size)
		return (1);
	return (0);
}

int main(int argc, char **argv, char **env)
{
	// char *prompt;
	t_lexed_list	*lexed_lst;
	t_malloc_list 	*malloc_lst;
	char 			*readline_str;
	char			cmd_line[] ="<< eof < test\tbienko\'\'\"\'\' h\'\" test|fd \"ec\"ho \'bonjour\"\'|wesh | bien\" | echo 2 >> test >>>><<<>>>>";
	// char **paths;

	// paths = get_paths(env);
	// for (int i = 0;paths[i];i++)
	// // 	printf("%s\n", paths[i]);
	printf("%s\n------------------\n", cmd_line);

	malloc_lst = NULL;
// ---------------------------------------------------------- //
//								Lexer                         //
// ---------------------------------------------------------- //
	lexed_lst = lexer(cmd_line, &malloc_lst);
// ---------------------------------------------------------- //
//						Check syntax error                    //
// ---------------------------------------------------------- //
	if (check_error(lexed_lst))
	{
		free_lst_malloc(malloc_lst);
		exit (1);
	}

	// token(lexed_lst);






	// while (readline_str = readline("minishell>"))
	// {
	// 	add_history(readline_str);
	// 	// if (!check_empty_line(readline_str) && check_builtins(command_data));
	// 	// else
	// 	// 	printf("Do pipex...\n");
	// 	printf("%s\n", readline_str);

	// 	free(readline_str);
	// }
}