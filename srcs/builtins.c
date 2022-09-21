/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MINISHELL                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdas-nev <rdas-nev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 4242/42/42 42:42:42 by rdas-nev          #+#    #+#             */
/*   Updated: 4242/42/42 42:42:42 by rdas-nev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/minishell.h"

void builtins(t_lists *minithings, char **envp)
{
    int i;

    i = -1;
    if (ft_strcmp(minithings->line, "exit") == 0)
    {
        printf("exit\n");
        exit(1);
    }
    else if (ft_strcmp(minithings->line, "cd") == 0)
    {
        if (ft_strlen(minithings->line) == 2)
            chdir(getenv("HOME"));
        else
            chdir(minithings->line + 3);
    }
    else if (ft_strcmp(minithings->line, "pwd") == 0)
    {
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));
        printf("%s\n", cwd);
    }
    else if (ft_strcmp(minithings->line, "env") == 0)
    {
        t_list *tmp = *minithings->env;
        while (tmp)
        {
            printf("%s\n", tmp->content);
            tmp = tmp->next;
        }
    }
    else if (ft_strcmp(minithings->line, "export") == 0)
    {
        if (ft_strlen(minithings->line) == 6)
        {
            t_list *tmp = *minithings->export;
            while (tmp)
            {
                printf("declare -x %s\n", tmp->content);
                tmp = tmp->next;
            }
        }
        else
        {
            char *str = ft_substr(minithings->line, 7, ft_strlen(minithings->line) - 7);
            int dup = check_duplicated(*minithings->export, str);
            if (dup == 0)
                ft_lstadd_back(minithings->export, ft_lstnew(str));
            else
                value_modifier(minithings->export ,dup, str);
        }
    }
    else
    {
        while (minithings->cmds[++i])
            ;
        pipex( i, minithings->cmds, envp);
    }
}
