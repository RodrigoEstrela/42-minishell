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

char	*ft_strnstr(const char	*big, const char *little, size_t len)
{
    size_t	i;
    size_t	j;

    i = 0;
    if (little[i] == '\0')
        return ((char *)big);
    while (big[i] && i < len)
    {
        j = 0;
        while (big[i + j] == little[j] && i + j < len)
        {
            if (little[j + 1] == '\0')
                return ((char *)big + i);
            j++;
        }
        i++;
    }
    return (0);
}

void	execute(char *av, char **envp)
{
	int		i;
	char	**cmd;
	char	*path;

    i = -1;
    cmd = ft_split(av, ' ');
    //cmd = quote_splitter(av);
    path = find_path(cmd[0], envp);
    if (!path)
	{
        while (cmd[++i]) {
            free(cmd[i]);
        }
        free(cmd);
        exit(EXIT_FAILURE);
    }
    if (execve(path, cmd, envp) == -1) {
       exit(EXIT_FAILURE);
    }
}

void	child_one(char *av, char **envp)
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
		execute(av, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}
