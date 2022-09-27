/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdas-nev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:08:13 by rdas-nev          #+#    #+#             */
/*   Updated: 2022/07/27 19:09:53 by rdas-nev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/pipex.h"

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;

    if (access(cmd, F_OK) == 0)
        return (cmd);
    while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (0);
}

void    pipex(int nbr_cmds, char **cmds, char **envp)
{
	int		i;
    int pid;

	if (nbr_cmds >= 1)
	{
        i = 0;
		while (i < nbr_cmds - 1)
			child_one(cmds[i++], envp);
        pid = fork();
        if (pid == 0)
            execute(cmds[nbr_cmds - 1], envp);
        else
            waitpid(pid, NULL, 0);
        return;
	}
}
