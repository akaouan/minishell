/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hayy <ael-hayy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 09:50:09 by ael-hayy          #+#    #+#             */
/*   Updated: 2022/07/19 12:08:51 by ael-hayy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "executor/minishell.h"

void	execution(t_prior *data, t_exec_elems *elems)
{
	int j;
	int	i;

	j = 0;
	i = data->numofchilds;
	if (i == 0)
	{	
		update_elems(elems, data);
		if (!elems->build_in)
			execute(elems);
		update_pipes(elems->pipes, elems->p2);
		return ;
	}
	while (j < i)
		j++;
	j = 0;
	while(j < i)
	{
		execution(data->next[j], elems);
		j++;
	}
}

int main(int ac, char **av, char **env)
{
	char    		*line;
	t_prior 		*script;
	t_exec_elems	*elems;
	t_env			*env_elems;

	line = 0;
	elems = NULL;
	init_env(&env_elems, env);
	int i;

	i = 0;
	(void)ac;
	(void)av;
	while (1)
	{
		line = readline("\033[0;32mmonosholo-2.0$> \033[0m");
		// if (line && line[0])
		// 	add_history(line);
		if (!line)
		{
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
		init_exec_elems(&elems, env_elems, script->numofchilds);
		execution(script, elems);
		close_pipes(elems->pipes);
		wait_pids(elems);
		free_tree(script);
		free(script);
		free (line);
		i = -1;
		while (++i < 2)
			free(elems->pipes[i]);
		free(elems->pipes);
		free(elems->pids);
		free(elems->cmd_path);
		free(elems);
   }
}
