#include "../minishell.h"

int	get_last_char(char *pwd, char c)
{
	int i;
	int	last_char;

	i = -1;
	last_char = 0;
	while (pwd[++i])
		if (pwd[i] == '/')
			last_char = i;
	return (last_char);
}

void	rm_back(char *str)
{
	int i;

	i = -1;
	while (str[++i])
		if (str[i] == '/')
			str[i] = '\0';
}

void	cmd_cd(char **old_pwd, char **pwd, char *path)
{
	rm_back(path);
	if(chdir(path) == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		exit(EXIT_FAILURE);	
	}
	if (!ft_strncmp(path, "..", 2))
	{
		free(*old_pwd);
		*old_pwd = ft_strdup(*pwd);
		*pwd = ft_substr(*pwd, 0, get_last_char(*pwd, '/'));
	}
	else
	{
		path = ft_strjoin(ft_strdup("/"), path);
		free(*old_pwd);
		*old_pwd = ft_strdup(*pwd);
		*pwd = ft_strjoin(*pwd, path);
	}
}