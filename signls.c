/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signls.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hayy <ael-hayy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 12:57:12 by ael-hayy          #+#    #+#             */
/*   Updated: 2022/07/28 16:51:25 by ael-hayy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor/minishell.h"

void    sig_manager()
{
    signal(SIGINT, &sig_handler_cc);   
    signal(SIGQUIT, &sig_handler_cs); 
}
void    sig_handler_cc()
{
    if (!global.is)
    {
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
    else
    {

    }
}
void    sig_handler_cs()
{
    return ;
}