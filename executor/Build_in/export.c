#include "../minishell.h"

t_var_val *add_var_val(char *var_val)
{
	t_var_val *elem;

	elem = malloc(sizeof(t_var_val));
	if (!elem)
		return (NULL);
	if (ft_strchr(var_val, '=') && *(ft_strrchr(var_val, '=') + 1) != '\0')
		elem->value = ft_strdup(ft_strchr(var_val, '=') + 1);
	else
		elem->value = ft_strdup("\0");
	elem->var = ft_substr(var_val, 0, get_index(var_val, '=') + 1);
	return (elem);
}

void	print_error(char *var, char *val)
{
	ft_putstr_fd("bash: export: `", STDERR_FILENO);
	ft_putstr_fd(var, STDERR_FILENO);
	ft_putstr_fd(val, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
}

int	is_valid(t_list **env_list, char *var)
{
	int i;
	t_list *head;

	head = *env_list;
	i = -1;
	while (head)
	{
		if (!ft_strncmp(((t_var_val *)head->content)->var, var, ft_strlen(var)))
		{
			delete_var_val(*env_list, var);
			return (1);
		}
		head = head->next;
	}
	if (ft_isdigit(var[0]))
		return 0;
	while(var[++i])
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
	return (1);
}

void	cmd_export(t_list **env_list, char **args)
{
	int i;
	char *var;
	char *val;

	i = 0;
	if (!args[0])
		return ;
	while (args[++i])
	{
		var = ft_substr(args[i], 0, get_index(args[i], '='));
		val = ft_strdup(ft_strchr(args[i], '='));
		if (is_valid(env_list, var))
			ft_lstadd_back(env_list,
				ft_lstnew((void *)add_var_val(args[i])));
		else
			print_error(var, val);
		free(var);
		free(val);
	}
}
