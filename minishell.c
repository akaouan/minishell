/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hayy <ael-hayy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 09:50:09 by ael-hayy          #+#    #+#             */
/*   Updated: 2022/07/01 15:58:48 by ael-hayy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "executor/minishell.h"

void	execution(t_prior *data, t_exec_elems *elems)
{
	int j = 0;
	if (!data->numofchilds)
	{
		update_elems(elems, data);
		if (!elems->build_in)
			execute(elems);
		update_pipes(elems->pipes, elems->p2);
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
	t_env			*env_elems;

	line = 0;
	elems = NULL;
	init_env(&env_elems, env);
	(void)ac;
	(void)av;
	while (1)
	{
		line = readline("\033[0;32mmonosholo-2.0$> \033[0m");
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
		init_exec_elems(&elems, script, env_elems, script->numofchilds);
		execution(script, elems);
		close_pipes(elems->pipes);
		wait_pids(elems);
		// free_tree(script);
		// free_exec_elems(elems);
		free(script);
		free (line);
   }
}

// !  #0 0x10355ae8b in len_without_quotes tree_parser.c:44