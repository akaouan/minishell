#include "../minishell.h"

void	delete(void *elem)
{
	t_var_val *to_free;

	to_free = (t_var_val *)elem;
	free(to_free->value);
	free(to_free->var);
	free(to_free);
}

void	delete_var_val(t_list *env_list, char *arg)
{
	t_list	*head;
	t_list	*before;
	char	*var;

	var = ft_substr(arg, 0, get_index(arg, '='));
	head = env_list;
	while (head)
	{
		if (ft_strlen(((t_var_val *)head->content)->var) == ft_strlen(var) &&
			!ft_strncmp(((t_var_val *)head->content)->var
			, var, ft_strlen(var)))
		{
			before->next = head->next;
			ft_lstdelone(head, &delete);
			free(var);
			return ;
		}
		before = head;
		head = head->next;
	}
	free(var);
}

void	cmd_unset(t_list **env_list, char **args)
{
	int i;

	i = 1;
	while (args[i])
	{

		delete_var_val(*env_list, args[i]);
		i++;
	}
}