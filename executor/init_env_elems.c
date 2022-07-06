#include "minishell.h"

void	init_env(t_exec_elems **elems, char **env)
{
	t_env	*env_elems;

	env_elems = malloc(sizeof(t_env));
	if (!env_elems)
	{
		ft_putstr_fd("Faild to allocate memory\n", STDERR_FILENO);
		exit(EXIT_FAILURE);		
	}
	env_elems->values = get_env_values(env);
	env_elems->vars = get_env_vars();
	env_elems->pwd = get_pwd();
}
