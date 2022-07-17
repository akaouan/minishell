#include "../minishell.h"

int	check_build_in(t_exec_elems *elems)
{
	if (!ft_strncmp(elems->args[0], "cd", 2))
	{
		if (!elems->args[1])
		{
			ft_putstr_fd("bash: cd: HOME not set\n", STDERR_FILENO);
			return (1);
		}
		cmd_cd(elems->env_elems->old_pwd, elems->env_elems->pwd
				, elems->args[1]);
		elems->build_in = 1;
		elems->cmd_index++;
		return (1);
	}
	else if (!ft_strncmp(elems->args[0], "pwd", 3))
	{
		ft_putstr_fd(elems->env_elems->pwd->value, elems->cmd_output);
		ft_putchar_fd('\n', elems->cmd_output);
		elems->build_in = 1;
		elems->cmd_index++;
		return (1);
	}
	else if (!ft_strncmp(elems->args[0], "echo", 4))
	{
		cmd_echo(elems->cmd_output, elems->args + 1);
		elems->build_in = 1;
		elems->cmd_index++;
		return (1);
	}
	else if (!ft_strncmp(elems->args[0], "env", 4))
	{
		cmd_env(elems);
		elems->build_in = 1;
		elems->cmd_index++;
		return (1);
	}
	else if (!ft_strncmp(elems->args[0], "export", 6))
	{
		cmd_export(&elems->env_elems->env_list, elems->args);
		elems->build_in = 1;
		elems->cmd_index++;
		return (1);
	}
	else if (!ft_strncmp(elems->args[0], "unset", 5))
	{
		cmd_unset(&elems->env_elems->env_list, elems->args);
		elems->build_in = 1;
		elems->cmd_index++;
		return (1);
	}
	elems->build_in = 0;
	return(0);
}