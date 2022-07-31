#include "../minishell.h"

void	cmd_env(t_exec_elems *elems)
{
	t_list	*env_list;

	env_list = elems->env_elems->env_list;
	while (env_list)
	{
		if (((t_var_val *)env_list->content)->value[0])
		{
			ft_putstr_fd(((t_var_val *)(env_list->content))->var ,
				elems->cmd_output);
			ft_putchar_fd('=', elems->cmd_output);
			ft_putstr_fd(((t_var_val *)(env_list->content))->value ,
				elems->cmd_output);
			ft_putchar_fd('\n', elems->cmd_output);
		}
		env_list = env_list->next;
	}
}