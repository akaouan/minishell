#include "../minishell.h"

void	cmd_env(t_exec_elems *elems)
{
	int i;

	i = -1;
	while (elems->env_elems->vars[++i])
	{
		ft_putstr_fd(elems->env_elems->vars[i], elems->cmd_output);
		ft_putstr_fd(elems->env_elems->values[i], elems->cmd_output);
		ft_putchar_fd('\n', elems->cmd_output);
	}
}