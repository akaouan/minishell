#include "minishell.h"

int ft_arrlen(char **arr)
{
    int i;

    i = 0;
    while (arr[i])
        i++;
    return (i);
}

void    cmd_cd(char **args)
{
    if (ft_arrlen(args) > 2)
    {   
        wr_error(STDERR_FILENO, "cd: too many arguments\n");
        return ;
    }
    if (chdir(args[1]) == -1)
    {
        wr_error(STDERR_FILENO, "cd: no such file or directory: ");
        write(STDERR_FILENO, args[1], ft_strlen(args[1]));
        write(STDERR_FILENO, "\n", 1);
    }
}

void    cmd_pwd(t_prior *data)
{
    int i;

    i = 0;
    while (data->cmd->env_var[i] && ft_strncmp(data->cmd->env_var[i], "PWD", 3))
        i++;
    if (!data->cmd->env_var[i])
    {
        wr_error(STDERR_FILENO, "couldn't found pwd variable\n");
        return ;
    }
    printf("%s\n", data->cmd->env_valuue[i]);
}

void    cmd_echo(char **args)
{
    int i;
    int option;

    i = 0;
    option = 0;
    if (!ft_strncmp(args[0], "-n", 2))
    {
        i = 1;
        option = 1;
    }
    while (args[i])
    {
        printf("%s", args[i]);
        if (args[i + 1])
            printf(" ");
        i++;
    }
    if (!option)
        printf("\n");
}