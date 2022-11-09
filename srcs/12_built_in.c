#include "minishell.h"

void ft_env(char **env)
{
	int i;

	i = 0;
	while (env[i])
		printf("%s\n", env[i++]);
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