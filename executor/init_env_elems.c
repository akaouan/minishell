#include "minishell.h"

int	get_index(char *str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (i);
	return (0);
}

char	**get_env_values(char **env, int env_size)
{
	int		i;
	char	**values;

	i = -1;
	values = malloc(sizeof(char *) * (env_size + 1));
	if (!values)
	{
		ft_putstr_fd("Faild to allocate memory\n", STDERR_FILENO);
		exit(EXIT_FAILURE);			
	}
	while (++i < env_size)
		values[i] = ft_strdup(ft_strchr(env[i], '=') + 1);
	values[i] = NULL;
	return (values);
}

char	**get_env_vars(char **env, int env_size)
{
	int		i;
	char	**vars;

	i = -1;	
	vars = malloc(sizeof(char *) * (env_size + 1));
	if (!vars)
	{
		ft_putstr_fd("Faild to allocate memory\n", STDERR_FILENO);
		exit(EXIT_FAILURE);			
	}
	while (++i < env_size)
		vars[i] = ft_substr(env[i], 0, get_index(env[i], '=') + 1);
	vars[i] = NULL;
	return (vars);
}

char	**get_pwd(char **vars, char **values, char *to_found)
{
	int	i;

	i = -1;
	while (vars[++i])
		if (!ft_strncmp(vars[i], to_found, 3))
			break ;
	return (values + i);
}

void	init_env(t_env **env_elems, char **env)
{
	int	env_size;

	env_size = arr_len(env);
	*env_elems = malloc(sizeof(t_env));
	if (!(*env_elems))
	{
		ft_putstr_fd("Faild to allocate memory\n", STDERR_FILENO);
		exit(EXIT_FAILURE);		
	}
	(*env_elems)->values = get_env_values(env, env_size);
	(*env_elems)->vars = get_env_vars(env, env_size);
	(*env_elems)->pwd = get_pwd((*env_elems)->vars, (*env_elems)->values, "PWD");
	(*env_elems)->old_pwd = get_pwd((*env_elems)->vars, (*env_elems)->values, "OLDPWD");
	(*env_elems)->env = env;
}
