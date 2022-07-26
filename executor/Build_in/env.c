#include "../minishell.h"

void	cmd_env(t_exec_elems *elems)
{
	t_list	*env_list;

	env_list = elems->env_elems->env_list;
	while (env_list)
	{
		if (ft_strchr(((t_var_val *)(env_list->content))->var, '='))
		{
			ft_putstr_fd(((t_var_val *)(env_list->content))->var ,
				elems->cmd_output);
			ft_putstr_fd(((t_var_val *)(env_list->content))->value ,
				elems->cmd_output);
			ft_putchar_fd('\n', elems->cmd_output);
		}
		env_list = env_list->next;
	}
}