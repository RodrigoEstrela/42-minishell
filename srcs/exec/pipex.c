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

#include "../../inc/minishell.h"

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

char	*find_path(char *cmd, t_exporttable **envp)
{
	t_path	p;

	p.i = 0;
	p.tmp = *envp;
	if (access(cmd, F_OK) == 0)
		return (cmd);
	while (ft_strnstr(p.tmp->k, "PATH", 4) == 0 && p.tmp->next != NULL)
		p.tmp = p.tmp->next;
	p.paths = ft_split(p.tmp->value, ':');
	while (p.paths[p.i])
	{
		p.part_path = ft_strjoin(p.paths[p.i], "/");
		p.path = ft_strjoin(p.part_path, cmd);
		free(p.part_path);
		if (access(p.path, F_OK) == 0)
			return (p.path);
		free(p.path);
		p.i++;
	}
	p.i = -1;
	while (p.paths[++p.i])
		free(p.paths[p.i]);
	free(p.paths);
	return (0);
}

void	pipex(int nbr_cmds, char ***cmds, char **envp, t_minithings *mt)
{
	int	i;

	if (nbr_cmds >= 1)
	{
		i = -1;
		while (++i < nbr_cmds - 1)
		{
			child_one(cmds[i], mt, envp, i);
		}
		execute(cmds[nbr_cmds - 1], mt, envp, i);
	}
}
