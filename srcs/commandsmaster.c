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
    int nbr_cmds;

    nbr_cmds = 0;
//    while (minithings->cmds[++i])
//    {
        if (ft_strcmp(minithings->cmds[0], "exit") == 0)
        {
            printf("exit\n");
            exit(1);
        }
        else if (is_builtin(minithings->cmds[nbr_cmds]))
        {
            builtins(minithings);
            return ;
        }
        pid = fork();
        if (pid == 0) {
            while (minithings->cmds[++nbr_cmds])
                ;
            pipex( nbr_cmds, minithings->cmds, envp);
            exit(0);
        }
        waitpid(pid, NULL, 0);
    }
//}
