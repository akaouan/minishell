#include "../minishell.h"

void	cmd_cd(char *pwd, char *path)
{
	if(chdir(path) == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		exit(EXIT_FAILURE);	
	}
	path = ft_strjoin(ft_strdup("/"), path);
	pwd = ft_strjoin(pwd, path);
}