#include "minishell.h"

void ft_env(t_env_lst *env_lst)
{
	while (env_lst)
	{
		printf("%s\n", env_lst->content);
		env_lst = env_lst->next;
	}
}

void ft_exit(t_command_data command_data)
{
	free_string_array(command_data.env);
	free(command_data.readline_str);
	printf("ft_exit...\n");
	exit (0);
}

void ft_pwd(char **env)
{
	char *pwd_path;
	char buff[PATH_MAX];

	pwd_path = getenv("PWD");
	if (pwd_path)
		printf("%s\n", pwd_path);
	else
		printf("%s\n", getcwd(buff, PATH_MAX));
}