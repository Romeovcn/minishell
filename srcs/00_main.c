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
	t_lex_lst	*lexed_lst;
	t_mal_lst 	*mal_lst;
	t_env_lst 		*env_lst;
	char 			*readline_str;
	char			cmd_line[] ="<< EOF cat -la | grep \"o\" | wc -l >> outfile > outfile2";

	mal_lst = NULL;
	printf("%s\n", cmd_line);
// ---------------------------------------------------------- //
//								Get env                       //
// ---------------------------------------------------------- //
	env_lst = NULL;
	get_env(&env_lst, env, &mal_lst);
	// printf("\n\n%s\n\n", get_env_value("lol", env_lst));
	// ft_read_lst_env(env_lst);
// ---------------------------------------------------------- //
//								Lexer                         //
// ---------------------------------------------------------- //
	lexed_lst = lexer(cmd_line, &mal_lst);
// ---------------------------------------------------------- //
//						Check syntax error                    //
// ---------------------------------------------------------- //
	if (check_error(lexed_lst))
		return (free_lst_malloc(mal_lst), 1);
// ---------------------------------------------------------- //
//							parser				              //
// ---------------------------------------------------------- //
	// parser(lexed_lst, &mal_lst, env_lst);
// ---------------------------------------------------------- //
//							Tokenizer			              //
// ---------------------------------------------------------- //
	token(lexed_lst, &mal_lst);
// ---------------------------------------------------------- //
//							Shit				              //
// ---------------------------------------------------------- //

	free_lst_malloc(mal_lst);
	// char *options[] = {"hey", "oi\"\"", NULL};
	// execve("/bin/echo", options, env);


	// while (readline_str = readline("minishell>"))
	// {
	// 	add_history(readline_str);
	// 	printf("%s\n", readline_str);

	// 	free(readline_str);
	// }
}