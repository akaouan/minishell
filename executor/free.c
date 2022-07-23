#include "minishell.h"

void	free_elems(t_prior *data, t_exec_elems *elems)
{
	int i;

	i = -1;
	free_tree(data);
	free(data);
	while (++i < 2)
		free(elems->pipes[i]);
	free(elems->pipes);
	free(elems->pids);
	free(elems->cmd_path);
	free(elems);
}