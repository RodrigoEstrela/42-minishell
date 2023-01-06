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

void	print_double_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		printf("%s\n", array[i]);
		i++;
	}
}

void	execute(t_redirs redirs, t_mthings *mt, char **envp, int indx)
{
	char	*path;

	if (is_builtin(redirs.cmd[0]))
	{
		builtins(mt, indx);
		return ;
	}
	path = find_path(redirs.cmd[0], mt->export);
	write(mt->wcode, "0\n", 2);
	if (redirs.out != -2)
		dup2(redirs.out, 1);
	if (redirs.in != -2)
	{
		dup2(redirs.in, 0);
	}
	execve(path, redirs.cmd, envp);
	free(path);
	printf("Error: command not found: %s\n", redirs.cmd[0]);
	write(mt->wcode, "127\n", 4);
}

void	child_one(t_redirs redirs, t_mthings *mt, char **envp, int indx)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		exit(0);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		if (redirs.out == -2)
		{
			dup2(fd[1], STDOUT_FILENO);
		}
		execute(redirs, mt, envp, indx);
		exit(0);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}
