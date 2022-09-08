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

void builtins(char *line, t_list **env)
{
    if (ft_strncmp(line, "exit", 4) == 0)
    {
        printf("exit\n");
        exit(1);
    }
    else if (ft_strncmp(line, "cd", 1) == 0)
    {
        if (ft_strlen(line) == 2)
            chdir(getenv("HOME"));
        else
            chdir(line + 3);
    }
    else if (ft_strncmp(line, "pwd", 3) == 0)
    {
        char cwd[1024];
        getcwd(cwd, sizeof(cwd));
        printf("%s\n", cwd);
    }
    else if (ft_strncmp(line, "env", 3) == 0)
    {
        t_list *tmp = *env;
        while (tmp)
        {
            printf("%s\n", tmp->content);
            tmp = tmp->next;
        }
    }
    else if (ft_strncmp(line, "export", 6) == 0)
    {
        if (ft_strlen(line) == 6)
            printf("export\n");
    }
}

