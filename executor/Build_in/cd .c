#include "../minishell.h"

void	cmd_cd(char **old_pwd, char **pwd, char *path)
{
	if(chdir(path) == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		exit(EXIT_FAILURE);	
	}
	path = ft_strjoin(ft_strdup("/"), path);
	// free(old_pwd);
	*old_pwd = ft_strdup(*pwd);
	*pwd = ft_strjoin(*pwd, path);
}