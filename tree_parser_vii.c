/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_parser_vii.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hayy <ael-hayy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 17:27:35 by ael-hayy          #+#    #+#             */
/*   Updated: 2022/07/30 17:55:40 by ael-hayy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/minishell.h"

char *rm_dollar(char *str, char c)
{
	int		j;
	char	*tem;

	j = untill_char(str, c);
	tem = ft_substr(str, 0, j + 1);
	return (tem);
}

char	*variable_i(char *tem, t_cmd *pipe, int f)
{
	int	j;

	tem = get_valuue(tem, pipe);
	j = 0;
	if (tem)
		while (tem[j])
		{
			if (tem[j] == ' ' && f)
			{
				pipe->read_from[0] = -1;
				write(2, "ambiguous redirect\n", 19);
				return (tem);
			}
			j++;
		}
	else if (!tem && f)
	{
		pipe->read_from[0] = -1;
		write(2, "ambiguous redirect\n", 19);
		return (tem);
	}
	return (tem);
}

char *variable(char *str, t_cmd *pipe, int f)
{
	int		i;
	int		j;
	char	*tem;

	i = 0;
	if (str[i] == ' ')
		return (str);
	while (str[i] && (ft_isalpha(str[i]) || ft_isdigit(str[i]) || str[i] == '_'))
		i++;
	if (str[0] == '\'' || str[0] == '"')
		return (rm_dollar(str, str[0]));
	tem = malloc(sizeof(char) * i + 1);
	j = 0;
	while (j < i)
	{
		tem[j] = str[j];
		j++;
	}
	tem[j] = '\0';
	return (variable_i(tem, pipe, f));
}

int	untill_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			i += next_qoute(&str[i ], str[i]);
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}

int	untill_char_v(char *str, char c)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] == '\"')
		{
			if (!k)
				k = 1;
			else
				k = 0;
			if (i == 0)
				i++;
		}
		if (str[i] == '\'' && !k)
			i += next_qoute(&str[i ], str[i]);
		if (str[i] == c)
			return (i);
		i++;
	}
	return (i);
}
