/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files_vi.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hayy <ael-hayy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 17:40:08 by ael-hayy          #+#    #+#             */
/*   Updated: 2022/07/30 18:52:24 by ael-hayy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/minishell.h"

void	get_herdoc(t_cmd *pipe, int j, char *limit)
{
	char	*line;

	if (global.her != -1)
		global.her = 1;
	while (1 && global.her != -1)
	{
		line = readline("> ");
		if (!line)
			continue ;
		if (ft_strlen(line) > 0 && !ft_strncmp(line, limit, ft_strlen(line)))
		{
			free(line);
			return ;
		}
		if (j == 1)
			line = get_val(line, pipe, 0, 0);
		if (pipe->lastout[0] == 1)
		{
			write(pipe->fd[1], line, ft_strlen(line));
			write(pipe->fd[1], "\n", 1);
		}
		free(line);		
	}
}

int	open_her_doc_i(t_cmd *pip, int i)
{
	if (pip->lastout[0] == 1)
	{
		if (pip->fd[0])
		{
			close(pip->fd[0]);
			close(pip->fd[1]);
		}
		pipe(pip->fd);
	}
	if (no_quote_found(pip->her_limit[i]))
	{
		get_herdoc(pip, 1, pip->her_limit[i]);
		if (global.her != -1)
			global.her = 0;
		close(pip->fd[1]);
		return (0);
	}
	return (1);
}
void	open_her_doc(t_cmd *pip)
{
	int	i;

	if (!pip->her_limit)
		return ;
	i = 0;
	if (pip->lastout[0] == 1)
		pip->fd = malloc(sizeof(int) * 2);
	while (pip->her_limit[i])
	{
		if (open_her_doc_i(pip, i))
		{
			pip->her_limit[i] = remove_quotes_str(pip->her_limit[i], pip, 0);
			get_herdoc(pip, 2, pip->her_limit[i]);
			close(pip->fd[1]);
		}
		i++;
	}
}


void	open_output(t_cmd *pipe)
{
	int	i;

	i = 0;
	if (!pipe->filesout)
		return ;
	pipe->outputs = malloc(strsnums(pipe->filesout) * sizeof(int));
	while (pipe->filesout[i])
	{
		pipe->outputs[i] = open(pipe->filesout[i], O_WRONLY);
		if (pipe->outputs[i] == -1)
		{
			pipe->A[0] = -1;
			printf("monosholo: %s:permission denied\n", pipe->filesout[i]);
			pipe->read_from[0] = - 1;
			while (i-- > 0)
				close (pipe->outputs[i]);
			break ;
		}
		i++;
	}
	i--;
	while (i-- > 0)
		close (pipe->outputs[i]);
	pipe->A[0] = 1;
}