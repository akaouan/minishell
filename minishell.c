/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hayy <ael-hayy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 09:50:09 by ael-hayy          #+#    #+#             */
/*   Updated: 2022/06/11 19:39:44 by ael-hayy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "executor/minishell.h"

void	execution(t_prior *data, t_exec_elems *elems)
{
	int j = 0;
	if (!data->numofchilds)
	{
		update_elems(elems, data);

		execute(elems);
		// printf("[%d] in: %d, out: %d\n", elems->cmd_index, elems->data->cmd->read_from[0], elems->data->cmd->write_to[0]);
		update_pipes(elems->pipes, elems->p2);
		// elems->cmd_index++;
		return ;
	}
	while (j < data->numofchilds)
		execution(data->next[j++], elems);
}

int main(int ac, char **av, char **env)
{
	char    		*line;
	t_prior 		*script;
	t_exec_elems	*elems;

	line = 0;
	elems = NULL;
	(void)ac;
	(void)av;
	while (1)
	{
		line = readline("\033[0;32mminishell-2.0$> \033[0m");
		if (!line  || line[0] == '\0')
		{
			if (line && line[0] == '\0')
			{
				free(line);
				continue ;
			}
			write(1, "\n", 1);
			continue ;
		}
		if (!all_space(line))
		{
			free(line);
			continue ;
		}
		if (pre_check_line(line))
		{
		   free(line);
		   continue ;
		}
		script = m_shell_parser(line);
		tree_parser(script, env);
		init_exec_elems(&elems, script, script->numofchilds);
		execution(script, elems);
		wait_pids(elems);
		close_pipes(elems->pipes);
		// free_tree(script);
		free(script);
		free (line);
   }
}