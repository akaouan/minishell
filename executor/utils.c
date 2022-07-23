#include "minishell.h"

void	swap(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	wait_pids(t_exec_elems *elems)
{
	int	i;

	i = -1;
	if (!elems->pids)
		return ;
	while (++i < elems->size)
		waitpid(elems->pids[i], NULL, 0);
}

char	*get_cmd_path(char *cmd, char *path_value)
{
	int		i;
	char	*cmd_path;
	char	**paths;

	i = -1;
	cmd_path = NULL;
	paths = ft_split(path_value, ':');
	// free(path_value);
	while (paths[++i])
	{
		cmd_path = ft_strjoin(paths[i], cmd);
		if (!access(cmd_path, F_OK))
		{
			i  = -1;
			while (paths[++i])
				free(paths[i]);
			free(paths);
			free(cmd);
			return (cmd_path);
		}
		free(cmd_path);
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	free(cmd);
	ft_putstr_fd("Couldn't found command\n", STDERR_FILENO);
	return (NULL);
}

int	arr_len(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}