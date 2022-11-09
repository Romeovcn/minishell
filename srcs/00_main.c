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

int check_empty_line(char *readline_str) // to fix
{
	int size;
	int i;

	size = ft_strlen(readline_str);
	if (size == 0)
		return (1);
	i = 0;
	while (readline_str[i])
	{
		if (!ft_isspace(readline_str[i]))
			return (1);
		i++;
	}
	return (0);
}

int main(int argc, char **argv, char **env)
{
	t_lexed_list	*lexed_lst;
	t_malloc_list 	*malloc_lst;
	t_env_list 		*env_lst;
	char 			*readline_str;
	char			cmd_line[] ="<< eof < test\t\"bie$test OK\"\'\'nko\'\'\"\'\' h\'\" test|fd \"ec\"ho \'bonjour$test\"\'|wesh | bien\" | echo 2 >> test\" $test";


	printf("%s\n------------------\n", cmd_line);

	malloc_lst = NULL;
// ---------------------------------------------------------- //
//								Get env                       //
// ---------------------------------------------------------- //
	env_lst = NULL;
	get_env(&env_lst, env, &malloc_lst);
	// printf("\n\n%s\n\n", get_env_value("lol", env_lst));
	// ft_read_lst_env(env_lst);
// ---------------------------------------------------------- //
//								Lexer                         //
// ---------------------------------------------------------- //
	lexed_lst = lexer(cmd_line, &malloc_lst);
// ---------------------------------------------------------- //
//						Check syntax error                    //
// ---------------------------------------------------------- //
	if (check_error(lexed_lst))
		return (free_lst_malloc(malloc_lst), 1);
// ---------------------------------------------------------- //
//							Parsing				              //
// ---------------------------------------------------------- //
	parsing(lexed_lst, &malloc_lst, env_lst);
// ---------------------------------------------------------- //
//							Tokenizer			              //
// ---------------------------------------------------------- //
	// token(lexed_lst, &malloc_lst);
	printf("--------Command lst lexed after--------\n");
// ---------------------------------------------------------- //
//							Shit				              //
// ---------------------------------------------------------- //
	ft_read_lst(lexed_lst);
	free_lst_malloc(malloc_lst);
	// char *options[] = {"hey", "oi\"\"", NULL};
	// execve("/bin/echo", options, env);


	// while (readline_str = readline("minishell>"))
	// {
	// 	add_history(readline_str);
	// 	printf("%s\n", readline_str);

	// 	free(readline_str);
	// }
}