#include "../minishell.h"

t_var_val *add_var_val(char *var_val)
{
	t_var_val *elem;

	elem = malloc(sizeof(t_var_val));
	if (!elem)
		return (NULL);
	if (ft_strrchr(var_val, '=') + 1 != '\0')
		elem->value = ft_strdup(ft_strrchr(var_val, '=') + 1);
	elem->var = ft_substr(var_val, 0, get_index(var_val, '=') + 1);
	return (elem);
}

void	cmd_export(t_list **env_list, char **args)
{
	int i;

	i = 1;
	while (args[i])
	{
		if (ft_strchr(args[i], '='))
		{
			ft_lstadd_back(env_list,
				ft_lstnew((void *)add_var_val(args[i])));
		}
		i++;
	}
}