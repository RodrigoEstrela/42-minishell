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

void	execute(char **cmd, t_minithings *mt, char **envp, int indx)
{
	char	*path;

	if (is_builtin(cmd[0]))
	{
		builtins(mt, indx);
		return ;
	}
	path = find_path(cmd[0], mt->export);
	write(mt->wcode, "0\n", 2);
	execve(path, cmd, envp);
	free(path);
	printf("Error: command not found: %s\n", cmd[0]);
	write(mt->wcode, "127\n", 4);
}

void	child_one(char **cmds, t_minithings *mt, char **envp, int indx)
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
		execute(cmds, mt, envp, indx);
		exit(0);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}
