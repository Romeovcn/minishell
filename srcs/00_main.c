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
	char *readline_str;
	char			cmd_line[] ="<<\tbien\"ko\'\'\"\'\' h\' test|fd \"ec\"ho \'bonjour\' \"\'|wesh || bien\" ||| echo 2 >> test >>>\"><<<>>>>";
	// char **paths;

	// paths = get_paths(env);
	// for (int i = 0;paths[i];i++)
	// // 	printf("%s\n", paths[i]);
	// printf("%s\n------------------\n", cmd_line);
	// lexed_lst = lexer(cmd_line);
	// token(lexed_lst);
	// printf("--------Command lst lexed--------\n");
	// ft_read_lst(lexed_lst);
	// free_lst(lexed_lst);





	while (readline_str = readline("minishell>"))
	{
		add_history(readline_str);
		// if (!check_empty_line(readline_str) && check_builtins(command_data));
		// else
		// 	printf("Do pipex...\n");
		printf("%s\n", readline_str);

		free(readline_str);
	}
}

	// "cat file | ls | wc -l"
	// "< infile cat | ls | wc -l"
	// "<< EOF cat | ls | wc -l"
	// "cat file | ls | wc -l >> outfile"
	// "cat file | ls | wc -l > outfile"

	// -- Token --
	// 1 - Split '|' sep in linked list
	// 2 - Check input redirect in first node
	// 3 - Check out redirect in last node
	// 4 - Parse quotes
	// 5 - Exec