/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_line_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hayy <ael-hayy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 09:50:03 by ael-hayy          #+#    #+#             */
/*   Updated: 2022/07/29 18:09:33 by ael-hayy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/minishell.h"

int    all_space(char *line)
{
    int    i;

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

int check_parentheses_ii(char *line, int    *i, int *j, int *k)
{
    if (line[(*i)] == '\"' || line[(*i)] == '\'')
    {
        if (next_qoute(&line[(*i)], line[(*i)]) == -1)
        {
            global.is_printed = 1;
            write(2, ">$ syntax error Unclosed qoute\n", 31);
            return (1);
        }
        (*i) += next_qoute(&line[(*i)], line[(*i)]);
    }
    else if (line[(*i)] == '(')
    {
        if (check_parentheses_i(line, i, j, k))
            return (1);
    }
    else if (line[(*i)] == ')')
        (*j)--;
    if ((*j) < 0 )
        return (1);
    return (0);
}

int check_parentheses_i(char *line, int    *i, int *j, int *k)
{
    if ((*i) == 0)
        (*j)++;
    else
    {
        (*k) = (*i) - 1;
        while ((*k) >= 0)
        {
            if (line[(*k)] == ' ')
            {
                (*k)--;
                continue ;
            }
            if (line[(*k)] != '|' && line[(*k)] != '&' && line[(*k)] != '(')
            {
                check_dir_ii(line[*k]);
                return (1);
            }
            else
                break ;
            (*k)--;
        }
        (*j)++;
    }
    return (0);
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
        if (check_parentheses_ii(line, &i, &j, &k))
            return (1);
        i++;
    }
    if (j != 0)
    {
        global.is_printed = 1;
        write(2, ">$ syntax error near unexpected token `('\n", 42);
        return (1);
    }
    return (0);
}

int    check_andor_i(char *line, int *k, int *i)
{
    if (line[(*i) + 1] == '|' || line[(*i) + 1] == '&')
        (*i)++;
    (*k) = (*i) + 1;
    while ((*k) >= 0)
    {
        while (line[(*k)] == ' ')
            (*k)++;
        if (line[(*k)] == '|' || line[(*k)] == '&' || line[(*i)] == '(' || line[(*i)] == ')')
        {
            check_dir_ii(line[(*k)]);
            return (1);
        }
        else
            break ;
    }
    if ((*k) == 0 && line[(*k)] == ' ')
    {
        check_dir_ii(line[(*k)]);
        return (1);
    }
    return (0);
}
int    check_andor_ii(char *line, int *k, int *i, int *j)
{
    while (line[(*i)] == ' ')
        (*i)++;
    if (!line[(*i)])
        return (1);
    (*j) = 0;
    if (line[(*i)] == '&' && line[(*i) + 1] != '&')
    {
        check_dir_ii(line[(*k)]);
        return (1);
    }
    if ((*i) == 0)
        return (1);
    else
    {
        if (check_andor_i(line, k, i))
            return (1);
    }
    return (0);
}
int    check_andor_iii(char *line, int *i, int *k, int *j)
{
    while (line[(*i)] == ' ')
        (*i)++;
    if (!j && (line[(*i)] == '|' || line[(*i)] == '&'))
    {
        check_dir_ii(line[(*k)]);
        return (1);
    }
    (*j) = 1;
    if (line[(*i)] == '\"' || line[(*i)] == '\'')
        (*i) += next_qoute(&line[(*i)], line[(*i)]);
    return (0);
}

int    check_andor_vi(char *line, int *i, int *l)
{
    static int    j;
    static int    k;
    if (check_andor_iii(line, i, &k, &j))
        return (1);
    if (line[(*i)] == '|' || line[(*i)] == '&')
    {
        
        if ((*l) == 0)
            return (1);
        if (check_andor_ii(line, &k, &(*i), &j))
            return (1);
        (*l) = 0;
    }
    if (line[(*i)] != ' ' && !(line[(*i)] == '|' || line[(*i)] == '&'))
        (*l) = 1;
    if (line[(*i)] != '|' && line[(*i)] != '&')
        j = 1;
    return (0);
}
int    check_andor(char *line)
{
    int    i;
    int    l;
    int     len;

    len = ft_strlen(line);
    i = 0;
    l = 0;

    while (i < len)
    {
        if (check_andor_vi(line, &i, &l))
            return (1);
        i++;
    }
    if (l == 0)
        return (1);
    return(0);
}

int    rev_next_quote(char *line, int    j, char c)
{
    j--;
    while (j >= 0 && line[j] != c)
        j--;
    return (j);
}

int    revcheck_i(char *line, int k, int i)
{
    while (k < (int)ft_strlen(line))
    {
        if (line[k] == ' ')
        {
            k++;
            continue ;
        }
        if (line[k] == '|' || line[k] == '&' || line[i] == ')')
        {
            check_dir_ii(line[i]);
            return (1);
        }
        else
            break ;
    }
    if (k == (int)ft_strlen(line) - 1 && line[k] == ' ')
    {
        check_dir_ii(line[i]);
        return (1);
    }
    return (0);
}

int    revcheck(char *line)
{
    int    i;
    int    k;

    i = ft_strlen(line);
    while (--i >= 0)
    {
        if (line[i] == '\"' || line[i] == '\'')
            i = rev_next_quote(line, i, line[i]);
        while (i >= 0 && line[i] == ' ')
            i--;
        if (i >= 0 && (line[i] == '|' || line[i] == '&'))
        {
            if (i == (int)ft_strlen(line) - 1)
                return (1);
            else
            {
                k = i + 1;
                if (revcheck_i(line, k, i))
                    return (1);
            }
            if (line[i - 1] == '|' || line[i - 1] == '&')
                i--;
        }
    }
    return (0);
}

void    check_dir_ii(char c)
{
    global.is_printed = 1;
    write(2, ">$ syntax error near unexpected token `", 40);
    write(2, &c, 1);
    write(2, "'\n", 2);
}
int    check_dir_i(int    i, char *line, char c, char g)
{
    while (line[i] == ' ')
        i++;
    if (!line[i])
    {
        global.is_printed = 1;
        write(2, ">$ syntax error near unexpected token `>'\n", 42);
        return (1);
    }
    while (line[i] == ' ')
        i++;
    if (line[i ] == g || line[i ] == '|' || line[i ] == '&' || line[i ] == '(' || line[i ] == ')')
    {
        check_dir_ii(line[i]);
        return (1);
    }
    if (line[i] == c)
    {
        i++;
        while (line[i] == ' ')
            i++;
        if (line[i] == '<' || line[i] == '>'|| line[i ] == '|' || line[i ] == '&' || line[i ] == '(' || line[i ] == ')')
        {
            check_dir_ii(line[i]);
            return (1);
        }
    }
    return (0);
}

int    check_dir(char *line)
{
    int    i;

    i = 0;
    while (line[i])
    {
        if (line[i] == '<')
        {
            i++;
            while (line[i] == ' ')
                i++;
            if (check_dir_i(i, line, '<', '>'))
                return (1);
        }
        else if (line[i] == '>')
        {
            i++;
            while (line[i] == ' ')
                i++;
            if (check_dir_i(i, line, '>', '<'))
                return (1);
        }
        i++;
    }
    return (0);
}

int pre_check_line(char *line)
{
    global.is_printed = 0;
    if (check_parentheses(line) || check_andor(line)
            || revcheck(line) || check_dir(line))
    {
        if (global.is_printed == 0)
        write(2, ">$ syntax error unexpected token \n", 34);
        return (1);
    }
    return (0);
}
