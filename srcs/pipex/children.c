/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdas-nev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:08:35 by rdas-nev          #+#    #+#             */
/*   Updated: 2022/07/27 19:07:12 by rdas-nev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../inc/minishell.h"

void execute(char *av, char **envp, t_minithings *minithings)
{
	int		i;
	char	**cmd;
	char	*path;

    i = -1;
    cmd = ft_split(av, ' ');
    path = find_path(cmd[0], envp);
    if (!path)
	{
        while (cmd[++i]) {
            free(cmd[i]);
        }
        free(cmd);
        exit(EXIT_FAILURE);
    }
    if (is_builtin(av))
    {
        builtins(minithings, 0);
    }
    else
    {
        execve(path, cmd, envp);
    }
//    execve(path, cmd, envp);
}

void child_one(char *av, char **envp, t_minithings *minithings)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		exit(0);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execute(av, envp, minithings);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}
