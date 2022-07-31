#include "../minishell.h"

void	update_pwd(char *path, t_var_val *old_pwd, t_var_val *pwd)
{
	(void)pwd;
	printf("path: %s\n", path);
	printf("---->%s\n", old_pwd->value);
}