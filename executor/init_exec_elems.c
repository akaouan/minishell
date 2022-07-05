#include "minishell.h"

char *init_cmd_path(t_prior *data)
{
	char	*cmd_path;
	int		path_index;

	path_index = get_path_index(data->cmd->env_var);
	if (path_index == -1)
		return (NULL);
	cmd_path = get_cmd_path(ft_strjoin(ft_strdup("/"),
		data->cmd->cmd), data->cmd->env_valuue[path_index]);
	return (cmd_path);
}

void	update_elems(t_exec_elems *elems, t_prior *data)
{
	elems->data = data;
	elems->cmd_input = data->cmd->read_from[0];
	elems->cmd_output = data->cmd->write_to[0];
	elems->args = elems->data->cmd->args;
	if (elems->data->cmd->cmd[0] == '/' || elems->data->cmd->cmd[0] == '.')
		elems->cmd_path = elems->data->cmd->cmd;
	else
		elems->cmd_path = init_cmd_path(elems->data);
	if (elems->size <= 1)
		return ;
	else if (elems->cmd_index > 0 && elems->cmd_index < elems->size - 1)
	{
		if (elems->cmd_input < 2)
			elems->cmd_input = elems->pipes[elems->p1][0];
		if (elems->cmd_output < 2)
			elems->cmd_output = elems->pipes[elems->p2][1];
		swap(&elems->p1, &elems->p2);
	}
	else if (!elems->cmd_index && elems->cmd_output < 2)
			elems->cmd_output = elems->pipes[elems->p1][1];
	else if (elems->cmd_input < 2)
			elems->cmd_input = elems->pipes[elems->p1][0];
}


int	init_pipes(int **pipes)
{
	int i;

	i = -1;
	while (++i < 2)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
			return (0);
		if (pipe(pipes[i]) == -1)
		{
			ft_putstr_fd("Faild to open pipes\n", STDERR_FILENO);
			exit(EXIT_FAILURE);
		}
	}
	return (1);
}

void	init_exec_elems(t_exec_elems **elems, t_prior *data, int size)
{
	if (!size)
		size++;
	*elems = malloc(sizeof(t_exec_elems));
	(*elems)->pids = malloc((sizeof(int) * size));
	(*elems)->pipes = malloc(sizeof(int *) * 2);
	if (!(*elems)
			|| !(*elems)->pids || !(*elems)->pipes
				|| !init_pipes((*elems)->pipes))
	{
		ft_putstr_fd("Faild to allocate memory\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	(*elems)->i_pid = 0;
	(*elems)->cmd_index = 0;
	(*elems)->p1 = 0;
	(*elems)->p2 = 1;
	(*elems)->size = size;
	(*elems)->data = data;
	(*elems)->args = NULL;
	(*elems)->cmd_path = NULL;
}