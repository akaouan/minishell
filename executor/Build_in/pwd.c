#include "../minishell.h"

int	get_last_char(char *pwd, char c)
{
	int i;
	int	last_char;

	i = -1;
	last_char = 0;
	while (pwd[++i])
		if (pwd[i] == c)
			last_char = i;
	return (last_char);
}

void	update_pwd(char *path, t_var_val *old_pwd, t_var_val *pwd)
{
	char *to_free;

	to_free = NULL;
	if (pwd && !ft_strncmp(path, "..", 2))
	{
		free(old_pwd->value);
		old_pwd->value = ft_strdup(pwd->value);
		to_free = pwd->value;
		pwd->value = ft_substr(pwd->value, 0, get_last_char(pwd->value, '/'));
		free(to_free);
	}
	else if (!ft_strncmp(pwd->value, path, ft_strlen(path)) || 
			!ft_strncmp(pwd->value, path, ft_strlen(pwd->value)))
	{
		printf("true")
		// printf("true %p\n", path);
		// free(old_pwd->value);
		// old_pwd->value = ft_strdup(old_pwd->value);
		// free(pwd->value);
		// pwd->value = ft_strdup(path);
	}
	else if (pwd)
	{
		path = ft_strjoin("/", path);
		free(old_pwd->value);
		old_pwd->value = ft_strdup(pwd->value);
		to_free = pwd->value;
		pwd->value = ft_strjoin(pwd->value, path);
		free(to_free);
		free(path);
	}
}