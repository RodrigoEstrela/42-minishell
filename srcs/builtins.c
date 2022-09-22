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

void builtins(t_minithings *minithings, char **envp)
{
    int i;

    i = -1;
    if (ft_strcmp(minithings->line, "exit") == 0)
    {
        printf("exit\n");
        exit(1);
    }
    else if (ft_strncmp(minithings->line, "cd ", 3) == 0)
    {
        if (ft_strlen(minithings->line) == 2)
            chdir(getenv("HOME"));
        else {
            printf("%s\n", minithings->line + 3);
            chdir(minithings->line + 3);
        }
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
        export(minithings);
    }
    else
    {
        while (minithings->cmds[++i])
            ;
        pipex( i, minithings->cmds, envp);
    }
}
