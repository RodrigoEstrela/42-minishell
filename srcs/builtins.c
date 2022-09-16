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

void builtins(char *line, t_list **env, t_list **export, char **cmds, char **envp)
{
    int i;

    i = -1;
    if (ft_strcmp(line, "exit") == 0)
    {
        printf("exit\n");
        exit(1);
    }
    else if (ft_strcmp(line, "cd") == 0)
    {
        if (ft_strlen(line) == 2)
            chdir(getenv("HOME"));
        else
            chdir(line + 3);
    }
    else if (ft_strcmp(line, "pwd") == 0)
    {
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));
        printf("%s\n", cwd);
    }
    else if (ft_strcmp(line, "env") == 0)
    {
        t_list *tmp = *env;
        while (tmp)
        {
            printf("%s\n", tmp->content);
            tmp = tmp->next;
        }
    }
    else if (ft_strcmp(line, "export") == 0)
    {
        if (ft_strlen(line) == 6)
        {
            t_list *tmp = *export;
            while (tmp)
            {
                printf("declare -x %s\n", tmp->content);
                tmp = tmp->next;
            }
        }
        else
        {
            char *str = ft_substr(line, 7, ft_strlen(line) - 7);
            int dup = check_duplicated(*export, str);
            if (dup == 0)
                ft_lstadd_back(export, ft_lstnew(str));
            else
                value_modifier(export ,dup, str);
        }
    }
    else
    {
        while (cmds[++i])
            ;
        pipex( i, cmds, envp);
    }
}
