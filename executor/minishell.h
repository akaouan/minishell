/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hayy <ael-hayy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:21:28 by ael-hayy          #+#    #+#             */
/*   Updated: 2022/05/25 17:09:44 by ael-hayy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../parser.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <sys/wait.h>

typedef struct n_exec_elems{
	char	*cmd_path;
	char	**args;
	int		**pipes;
	int		*pids;
	int		i_pid;
	int		p1;
	int		p2;
	int		size;
	t_prior	*data;
	int		cmd_index;
	int		cmd_input;
	int		cmd_output;
}	t_exec_elems;

void	wr_error(int fd, char *err_msg);
void	execute(t_exec_elems *elems);
void	wait_pids(t_exec_elems *elems);
void	init_exec_elems(t_exec_elems **elems, t_prior *data, int size);
void	update_elems(t_exec_elems *elems, t_prior *data);
char	*get_cmd_path(char *cmd, char *env_values);
int		get_path_index(char **env_vars);
void	swap(int *a, int *b);
void	close_pipes(int	**pipes);
void	update_pipes(int **pipes, int to_close);
void    cmd_cd(char **args);
void    cmd_pwd(t_prior *data);
void    cmd_echo(int fd_output, char **args);
#endif