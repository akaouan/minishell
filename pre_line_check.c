/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_line_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hayy <ael-hayy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 09:50:03 by ael-hayy          #+#    #+#             */
/*   Updated: 2022/07/18 17:43:43 by ael-hayy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/minishell.h"

int	all_space(char *line)
{
	int	i;

	i = 0;
	if (line[0] == '"')
	{
		if (line[1] == '"')
			if (line[2] == '\0')
			{
				printf("minishell: : command not found\n");
				return (0);
			}
	}
	while (line[i])
	{
		if (line[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

int next_qoute(char *line, char c)
{
	int i;

	i = 1;
	while (line[i])
	{
		if (line[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int check_parentheses(char *line)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	while (line[i] == ' ')
		i++;
	while (line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			if (next_qoute(&line[i], line[i]) == -1)
			{
				write(2, ">$ syntax error Unclosed qoute\n", 31);
				return (1);
			}
			i += next_qoute(&line[i], line[i]);
		}
		else if (line[i] == '(')
		{
			if (i == 0)
				j++;
			else
			{
				k = i - 1;
				while (k >= 0)
				{
					if (line[k] == ' ')
					{
						k--;
						continue ;
					}
					if (line[k] != '|' && line[k] != '&' && line[k] != '(')
					{
						write(2, ">$ syntax error near unexpected token `", 40);
						write(2, &line[k], 1);
						write(2, "'\n", 2);
						return (1);
					}
					else
						break ;
					k--;
				}
				j++;
			}
		}     
		else if (line[i] == ')')
			j--;
		if (j < 0 )
			return (1);
		i++;
	}
	if (j != 0)
	{
		write(2, ">$ syntax error near unexpected token `('\n", 42);
		return (1);
	}
	return (0);
}
int	check_andor(char *line)
{
	int	i;
	int	k;
	int	l;
	int	j;
	i = 0;
	k = 0;
	l = 0;
	j = 0;
	while (line[i])
	{
		while (line[i] == ' ')
			i++;
		if (!j && (line[i] == '|' || line[i] == '&'))
		{
			write(2, ">$ syntax error near unexpected token `", 40);
			write(2, &line[k], 1);
			write(2, "'\n", 2);
			return (1);
		}
		j = 1;
		if (line[i] == '\"' || line[i] == '\'')
			i += next_qoute(&line[i], line[i]);
		if (line[i] == '|' || line[i] == '&')
		{
			j = 0;
			if (l == 0)
				return (1);
			if (line[i] == '&' && line[i + 1] != '&')
			{
				write(2, ">$ syntax error near unexpected token `", 40);
				write(2, &line[k], 1);
				write(2, "'\n", 2);
				return (1);
			}
			if (i == 0)
				return (1);
			else
			{
				if (line[i + 1] == '|' || line[i + 1] == '&')
					i++;
				k = i + 1;
				while (k >= 0)
				{
					while (line[k] == ' ')
						k++;
					if (line[k] == '|' || line[k] == '&' || line[i] == '(' || line[i] == ')')
					{
						write(2, ">$ syntax error near unexpected token `", 40);
						write(2, &line[k], 1);
						write(2, "'\n", 2);
						return (1);
					}
					else
						break ;
				}
				if (k == 0 && line[k] == ' ')
					return (1);
			}
			l = 0;
		}
		if (line[i] != ' ' && !(line[i] == '|' || line[i] == '&'))
			l = 1;
		if (line[i] != '|' && line[i] != '&')
			j = 1;
		i++;
	}
	if (l == 0)
		return (1);
	return(0);
}

int	rev_next_quote(char *line, int	j, char c)
{
	j--;
	while (line[j] != c)
		j--;
	return (j);
}

// int	check_and_or(char *line)
// {
// 	int	i;
// 	int	j;
// 	int	k;

// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	while (line[i])
// 	{
// 		if (line[i] == )
// 	}
// }

int	revcheck(char *line)
{
	int	i;
	int	k;

	i = ft_strlen(line) - 1;
	while (i >= 0)
	{
		if (line[i] == '\"' || line[i] == '\'')
			i = rev_next_quote(line, i, line[i]);
		if (line[i] == '|' || line[i] == '&')
		{
			if (i == (int)ft_strlen(line) - 1)
				return (1);
			else
			{
				k = i + 1;
				while (k < (int)ft_strlen(line))
				{
					if (line[k] == ' ')
					{
						k++;
						continue ;
					}
					if (line[k] == '|' || line[k] == '&' || line[i] == ')')
					{
						write(2, ">$ syntax error near unexpected token `", 40);
						write(2, &line[k], 1);
						write(2, "'\n", 2);
						return (1);
					}
					else
						break ;
				}
				if (k == (int)ft_strlen(line) - 1 && line[k] == ' ')
					return (1);
			}
			if (line[i - 1] == '|' || line[i - 1] == '&')
				i--;
		}
		i--;
	}
	return (0);
}

int	check_dir(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '<')
		{
			i++;
			while (line[i] == ' ')
				i++;
			if (!line[i])
			{
				write(2, ">$ syntax error near unexpected token `<'\n", 42);
				return (1);
			}
			if (line[i] == '>'|| line[i ] == '|' || line[i ] == '&' || line[i ] == '(' || line[i ] == ')')
				{
					write(2, ">$ syntax error near unexpected token `", 40);
					write(2, &line[i], 1);
					write(2, "'\n", 2);
					return (1);
				}
			if (line[i] == '<')
			{
				i++;
				while (line[i] == ' ')
					i++;
				if (line[i] == '<' || line[i] == '>'|| line[i ] == '|' || line[i ] == '&' || line[i ] == '(' || line[i ] == ')')
				{
					write(2, ">$ syntax error near unexpected token `", 40);
					write(2, &line[i], 1);
					write(2, "'\n", 2);
					return (1);
				}
			}
		}
		else if (line[i] == '>')
		{
			i++;
			while (line[i] == ' ')
				i++;
			if (!line[i])
			{
				write(2, ">$ syntax error near unexpected token `>'\n", 42);
				return (1);
			}
			if (line[i ] == '<' || line[i ] == '|' || line[i ] == '&' || line[i ] == '(' || line[i ] == ')')
			{
				write(2, ">$ syntax error near unexpected token `", 40);
				write(2, &line[i], 1);
				write(2, "'\n", 2);
				return (1);
			}
			if (line[i] == '>')
			{
				i++;
				while (line[i] == ' ')
					i++;
				if (line[i] == '<' || line[i] == '>'|| line[i ] == '|' || line[i ] == '&' || line[i ] == '(' || line[i ] == ')')
				{
					write(2, ">$ syntax error near unexpected token `", 40);
					write(2, &line[i], 1);
					write(2, "'\n", 2);
					return (1);
				}
			}
		}
		i++; 
	}
	return (0);
}

int pre_check_line(char *line)
{
	if (check_parentheses(line) || check_andor(line)
			|| revcheck(line) || check_dir(line))
	{
		write(2, ">$ syntax error unexpected token \n", 34);
		return (1);
	}
	return (0);
}