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

void    commands(t_minithings *minithings, char **envp)
{
    int pid;

    if (ft_strncmp(minithings->line, "cd ", 3) == 0)
    {
        if (ft_strlen(minithings->line) == 2)
            chdir(getenv("HOME"));
        else {
            printf("%s\n", minithings->line + 3);
            chdir(minithings->line + 3);
        }
    }
    pid = fork();
    if (pid == 0)
    {
        builtins(minithings, envp);
        exit(0);
    }
    waitpid(pid, 0, 0);
}
