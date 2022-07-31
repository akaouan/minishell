/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hayy <ael-hayy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 09:50:09 by ael-hayy          #+#    #+#             */
/*   Updated: 2022/07/31 10:19:23 by ael-hayy         ###   ########.fr       */
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
		// printf("%d  %s   %d\n", data->cmd->read_from[0],data->cmd->cmd, data->cmd->write_to[0]);
		if (data->cmd->read_from[0] == -1)
			return ;
		update_elems(elems, data);
		if (!elems->build_in)
			execute(elems);
		update_pipes(elems->pipes, elems->p2);		
		return ;
	}
	while (j < i)
	{
		//update_elems(elems, data);
		// if (!elems->build_in)
		// 	execute(elems);
		// update_pipes(elems->pipes, elems->p2);
		j++;
	}
	j = 0;
	while(j < i)
	{
		//printf("%s\n", data->operator[j]);
		//if (data->operator[j] == "||" || data->operator[j] == "&&")
		//{
			execution(data->next[j], elems);
			// wait for all children and then 
		//}
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
	(void)ac;
	(void)av;
	int i = 0;
	sig_manager();
	global.her = 0;
	init_env(&env_elems, env);
	while (1)
	{
		i++;
		if (global.her == -1)
		{
			global.her = 0;
			dup2(global.saver, 0);
		}
		global.is = 0;
		line = readline("\033[0;32mminishell(\033[0;31mv3.0\033[0;32m)$> \033[0m");
		if (line && line[0])
			add_history(line);
		if (!line)
			exit(0);
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
		tree_parser(script, env, env_elems->env_list);
		global.is = 1;
		if (global.her != -1)
		{
			init_exec_elems(&elems, env_elems, script->numofchilds);
			execution(script, elems);
			close_pipes(elems->pipes);
			wait_pids(elems);
		}
		// free_tree(script);
		free_elems(script, elems);
		//free(script);
		free (line);
		line = 0;
   }
}