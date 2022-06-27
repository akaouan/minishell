#include "minishell.h"

void	swap(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	wr_error(int fd, char *err_msg)
{
	ft_putstr_fd(err_msg, fd);
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

char	*get_cmd_path(char *cmd, char *env_values)
{
	int		i;
	char	*cmd_path;
	char	**paths;

	i = -1;
	cmd_path = NULL;
	paths = ft_split(env_values, ':');
	while (paths[++i])
	{
		cmd_path = ft_strjoin(paths[i], cmd);
		if (!access(cmd_path, F_OK))
		{
			free(paths);
			free(cmd);
			return (cmd_path);
		}
		free(cmd_path);
	}
	free(paths);
	wr_error(2, "Couldn't found command\n");
	return (NULL);
}

int	get_path_index(char **env_vars)
{
	int	i;

	i = -1;
	while (env_vars[++i])
		if (!ft_strncmp(env_vars[i], "PATH", 4))
			return (i);
	wr_error(2, "Couldn't found path variable\n");
	return (-1);
}