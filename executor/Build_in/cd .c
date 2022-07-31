#include "../minishell.h"

void	cmd_cd(t_var_val *old_pwd, t_var_val *pwd, char *path)
{
	char *bs;

	bs = ft_strrchr(path, '/');
	if(chdir(path) == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", STDERR_FILENO);
		ft_putstr_fd(path, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		return ;
	}
	if (bs && *(bs + 1) == '\0')
		*bs = '\0';
	update_pwd(path, old_pwd, pwd);
}