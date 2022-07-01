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
		wr_error(STDERR_FILENO, "Faild to open pipes\n");
		exit(EXIT_FAILURE);
	}
}

void	set_cmd(t_exec_elems *elems)
{
	if (dup2(*elems->data->cmd->write_to, STDOUT_FILENO) == -1)
	{
		wr_error(STDERR_FILENO, "Faild to duplicate fd\n");
		exit(EXIT_FAILURE);
	}
	if (dup2(*(elems->data->cmd->read_from), STDIN_FILENO) == -1)
	{
		wr_error(STDERR_FILENO, "Faild to duplicate fd\n");
		exit(EXIT_FAILURE);
	}
	close_pipes(elems->pipes);
	execve(elems->cmd_path, elems->args, NULL);
}

int	check_build_in(t_exec_elems *elems)
{
	if (!ft_strncmp(elems->data->cmd->cmd, "cd", 2))
	{
		if (!elems->args[1])
		{
			wr_error(STDERR_FILENO, "bash: cd: HOME not set\n");
			return (1);
		}
		cmd_cd(elems->args);
		return (1);
	}
	else if (!ft_strncmp(elems->data->cmd->cmd, "pwd", 3))
	{
		cmd_pwd(elems->data);
		return (1);
	}
	// else if (!ft_strncmp(elems->data->cmd->cmd, "echo", 4))
	// {
	// 	cmd_echo(elems->args + 1);
	// 	return (1);
	// }
	return(0);
}

void	execute(t_exec_elems *elems)
{
	int	id;

	if (check_build_in(elems))
		return ;
	id = fork();
	if (!id)
		set_cmd(elems);
	elems->cmd_index++;
	elems->pids[elems->i_pid++] = id;
}