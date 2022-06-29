/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hayy <ael-hayy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 09:50:09 by ael-hayy          #+#    #+#             */
/*   Updated: 2022/06/29 12:15:00 by ael-hayy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "executor/minishell.h"

void	po(t_prior *script)
{
	int	i = script->numofchilds;
	if(!i)
	{
		printf("heere  [%d]\n", script->cmd->read_from[0]);
		int i = 0;
		if (script->cmd->args)
		{
			printf("::%s::\n", script->cmd->cmd);
			while (script->cmd->args[i])
			{
				printf("%s", script->cmd->args[i]);
				i++;
			}
		}
		printf("\n");
		// printf("%d ... \n", script->cmd->inputs[0]);
		return;
	}
	int j = 0;
	while (j < i- 1)
	{
		printf("heere\n");
		j++;
	}
	j = 0;
	while (j < i)
	{
		po(script->next[j]);
		j++;
	}
}

int main(int ac, char **av, char **env)
{
	char     *line;
	t_prior  *script;

	line = 0;
	(void)ac;
	(void)av;
	while (1)
	{
		line = readline("monosholo-1.0$ ");
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
		po(script);
		//free_tree(script);
		free(script);
		free (line);
   }
}