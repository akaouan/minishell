/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hayy <ael-hayy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 10:17:05 by ael-hayy          #+#    #+#             */
/*   Updated: 2022/07/30 19:51:21 by ael-hayy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int all_are_digit(char *args, int   *j)
{
	int i;

	i = 0;
	if (!args)
		return (0);
	if (args[0] == '-' || args[0] == '+')
		i++;
	while (args[i])
	{
		if (!ft_isdigit(args[i]))
		{
			*j = -1;
			return (-1);
		}
		i++;
	}
	return (ft_atoi(args));
}

int is_dgt(char *line)
{
	int i;

	i = 0;
	if (line[i] == '+' || line[i] == '+')
		i++;
	while (line[i])
	{
		if (ft_isdigit(line[i]))
			return(1);
		i++;
	}
	return (0);
	
}

int	ft_exit(char **args)
{
	int is;
	int a;
	is = 0;
	while (args[is + 1])
		is++;
	if (is == 0)
	{
		printf("exit\n");
			exit (0);
	}
	if (is > 1 && is_dgt(args[1]))
		return (printf("minishell: exit: too many arguments\n"));
	a = all_are_digit(args[1], &is);
	if (is == -1)
	{
		if (!global.con)
			printf("exit\nminishell: exit: %s: numeric argument required", args[1]);
		else
			printf("minishell: exit: %s: numeric argument required", args[1]);
		exit(255);
	}
	if (!global.con)
		printf("exit\n");
	exit(a);
	return (0);
}
