#include "minishell.h"

void	close_pipes(int **pipes)
{
	int	i;

	i = -1;
	while (++i < 2)
	{		
			close(pipes[i][0]);
			close(pipes[i][1]);
	}
}

void	update_pipes(int **pipes, int to_close)
{
	close(pipes[to_close][0]);
	close(pipes[to_close][1]);
	if (pipe(pipes[to_close]) == -1)
	{
		ft_putstr_fd("Faild to open pipes\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

void	set_cmd(t_exec_elems *elems)
{
	if (dup2(elems->cmd_output, STDOUT_FILENO) == -1)
	{
		ft_putstr_fd("Faild to duplicate fd\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (dup2(elems->cmd_input, STDIN_FILENO) == -1)
	{
		ft_putstr_fd("Faild to duplicate fd\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	close_pipes(elems->pipes);
	execve(elems->cmd_path, elems->args, elems->env_elems->env);
}

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
		return (1);
	}
	else if (!ft_strncmp(elems->args[0], "pwd", 3))
	{
		// cmd_pwd(elems->data);
		elems->build_in = 1;
		return (1);
	}
	else if (!ft_strncmp(elems->args[0], "echo", 4))
	{
		cmd_echo(elems->cmd_output, elems->args + 1);
		elems->build_in = 1;
		return (1);
	}
	elems->build_in = 0;
	return(0);
}

void	execute(t_exec_elems *elems)
{
	int	id;

	id = fork();
	if (!id)
		set_cmd(elems);
	elems->cmd_index++;
	elems->pids[elems->i_pid++] = id;
}