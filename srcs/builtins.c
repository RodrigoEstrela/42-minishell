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

int is_builtin(char *str)
{
    if (!str)
        return (0);
    if (ft_strcmp(str, "echo") == 0)
        return (1);
    if (ft_strncmp(str, "cd ", 3) == 0)
        return (1);
    if (ft_strcmp(str, "pwd") == 0)
        return (1);
    if (ft_strncmp(str, "export", 6) == 0)
        return (1);
    if (ft_strncmp(str, "unset", 5) == 0)
        return (1);
    if (ft_strcmp(str, "env") == 0)
        return (1);
    return (0);
}

void builtins(t_minithings *minithings, int flag)
{
    int i;

    i = -1;
    if (ft_strncmp(minithings->line, "cd ", 3) == 0 && flag == 0)
    {
        if (ft_strlen(minithings->line) == 2)
            chdir(getenv("HOME"));
        else {
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
    else if (ft_strncmp(minithings->line, "echo ", 5) == 0)
    {
        char **echo_str;

        //echo_str = ft_split(minithings->line, ' ');
        echo_str = quote_splitter(minithings->cmds[0]);
        if (echo_str[1][0] == '-')
        {
            if (echo_str[1][1] == 'n')
            {
                i += 2;
                while (echo_str[++i])
                    printf("%s", echo_str[i]);
            }
            else
                printf("Unknown option: %c\n", echo_str[1][1]);
        }
        else
        {
            i++;
            while (echo_str[++i])
                printf("%s", echo_str[i]);
            printf("\n");
        }
    }
    else if (ft_strncmp(minithings->line, "export", 6) == 0)
    {
        export(minithings, flag);
    }
    else if (ft_strncmp(minithings->line, "unset", 5) == 0)
    {
       unset(minithings);
    }
}