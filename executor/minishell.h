/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hayy <ael-hayy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:21:28 by ael-hayy          #+#    #+#             */
/*   Updated: 2022/07/31 18:02:44 by akaouan          ###   ########.fr       */
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

typedef struct n_var_val{
	char	*var;
	char	*value;
}	t_var_val;

typedef struct n_env{
	t_list		*env_list;
	t_var_val	*pwd;
	t_var_val	*old_pwd;
	char		**env;
}	t_env;

typedef struct n_exec_elems{
	int		build_in;
	t_env	*env_elems;
	char	*cmd_path;
	char	**args;
	int		**pipes;
	int		*pids;
	int		i_pid;
	int		p1;
	int		p2;
	int		size;
	int		cmd_index;
	int		cmd_input;
	int		cmd_output;
	int		is_child;

}	t_exec_elems;

void	wr_error(int fd, char *err_msg);
void	execute(t_exec_elems *elems);
void	wait_pids(t_exec_elems *elems);
void	init_exec_elems(t_exec_elems **elems,
			t_env *env_elems, int size);
void	update_elems(t_exec_elems *elems, t_prior *data);
char	*get_cmd_path(char *cmd, char *env_values);
int		get_path_index(char **env_vars);
void	swap(int *a, int *b);
void	close_pipes(int	**pipes);
void	update_pipes(int **pipes, int to_close);
void	cmd_cd(t_var_val *old_pwd, t_var_val *pwd, char *path);
void	cmd_echo(int fd_output, char **args);
void	free_exec_elems(t_exec_elems *elems);
void	init_env(t_env **env_elems, char **env);
char	**get_env_values(char **env, int env_size);
char	**get_env_vars(char **env, int env_size);
int		arr_len(char **arr);
int		check_build_in(t_exec_elems *elems);
void	cmd_env(t_exec_elems *elems);
int		check_build_in(t_exec_elems *elems);
void	cmd_export(t_list **env_list, char **args, t_exec_elems *elems);
int		get_index(char *str, char c);
void	cmd_unset(t_list **env_list, char **args);
void	free_elems(t_prior *data, t_exec_elems *elems);
void	delete_var_val(t_list *env_list, char *arg);
void	tree_parser(t_prior *script, char **env, t_list *head);
void	set_env(t_cmd *pipe, t_list *head, t_list *headtem);
int		ft_exit(char **args);
void	update_pwd(char *path, t_var_val *old_pwd, t_var_val *pwd);
#endif
