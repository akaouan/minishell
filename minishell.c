/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hayy <ael-hayy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 09:50:09 by ael-hayy          #+#    #+#             */
/*   Updated: 2022/07/29 19:44:01 by ael-hayy         ###   ########.fr       */
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
		// update_elems(elems, data);
		// if (!elems->build_in)
		// 	execute(elems);
		// update_pipes(elems->pipes, elems->p2);		
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
		printf("%s\n", data->operator[j]);
		if (data->operator[j] == "||" || data->operator[j] == "&&")
		{
			execution(data->next[j], elems);
			// wait for all children and then 
		}
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
	init_env(&env_elems, env);
	while (1)
	{
		global.is = 0;
		i++;
		line = readline("\033[0;32mmonosholo-2.0$> \033[0m");
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
		init_exec_elems(&elems, env_elems, script->numofchilds);
		execution(script, elems);
		close_pipes(elems->pipes);
		wait_pids(elems);
		free_tree(script);
		free(script);
		free (line);
		line = 0;
   }
}

// init_env(&env_elems, env);
//     t_listhead;
//     head = env_elems->env_list;
//     while (head)
//     {
//         printf("%s <<----->> %s\n", ((t_var_val )head->content)->var, ((t_var_val)head->content)->value);
//         head = head->next;
//     }