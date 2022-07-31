/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaouan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/31 18:02:31 by akaouan           #+#    #+#             */
/*   Updated: 2022/07/31 18:02:33 by akaouan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_elems(t_prior *data, t_exec_elems *elems)
{
	int	i;

	i = -1;
	free_tree(data);
	free(data);
	while (++i < 2)
		free(elems->pipes[i]);
	free(elems->cmd_path);
	free(elems->pipes);
	free(elems->pids);
	free(elems);
}
