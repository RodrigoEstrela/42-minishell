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

char	*normi(t_path *path)
{
	char	*tmp;

	free_double_array(path->paths);
	tmp = ft_strdup(path->path);
	free(path->path);
	free(path);
	return (tmp);
}

char	*find_path(char *cmd, t_extab **envp)
{
	t_path	*path;

	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	path = malloc(sizeof(t_path));
	path->i = -1;
	path->tmp = *envp;
	while (ft_strnstr(path->tmp->k, "PATH", 4) == 0 && path->tmp->next != NULL)
		path->tmp = path->tmp->next;
	path->paths = ft_split(path->tmp->value, ':');
	while (path->paths[++path->i])
	{
		path->part_path = ft_strjoin(path->paths[path->i], "/");
		path->path = ft_strjoin(path->part_path, cmd);
		free(path->part_path);
		if (access(path->path, F_OK) == 0)
			return (normi(path));
		free(path->path);
	}
	free_double_array(path->paths);
	free(path);
	return (0);
}

char **cpydp(char **dp)
{
	char **new;
	int i;

	i = 0;
	while (dp[i])
		i++;
	new = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (dp[i])
	{
		new[i] = ft_strdup(dp[i]);
		i++;
	}
	new[i] = 0;
	return (new);
}

int	meteins(t_cmds **ins)
{
	int		fd;
	t_cmds *tmp;

	tmp = *ins;
	while (tmp && ft_strcmp(tmp->cmd, "PIPETEMPIPE") != 0)
	{
		if (ft_strcmp(tmp->cmd, "SEMINS") == 0)
		{
			fd = -2;
			tmp = tmp->next;
			delete_elem(ins, 0);
			break;
		}
		if (tmp->cmd[slen(tmp->cmd) - 1] == ' ')
			tmp->cmd[slen(tmp->cmd) - 1] = 0;
		fd = open(tmp->cmd, O_RDONLY);
		tmp = tmp->next;
		delete_elem(ins, 0);
	}
	if (tmp)
		delete_elem(ins, 0);
	return (fd);
}

int meteouts(t_cmds **outs)
{
	int		fd;
	t_cmds *tmp;

	tmp = *outs;
	while (tmp && ft_strcmp(tmp->cmd, "PIPETEMPIPE") != 0)
	{
		if (ft_strcmp(tmp->cmd, "SEMOUTS") == 0)
		{
			fd = -2;
			tmp = tmp->next;
			delete_elem(outs, 0);
			break;
		}
		if (tmp->cmd[slen(tmp->cmd) - 1] == ' ')
			tmp->cmd[slen(tmp->cmd) - 1] = 0;
		if (tmp->redirect == 4)
			fd = open(tmp->cmd, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(tmp->cmd, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		tmp = tmp->next;
		delete_elem(outs, 0);
	}
	if (tmp)
		delete_elem(outs, 0);
	return (fd);
}

t_redirs meteredirs(char **cmd, t_cmds **ins, t_cmds **outs)
{
	t_redirs	redirs;

	redirs.cmd = cpydp(cmd);
	redirs.in = meteins(ins);
	redirs.out = meteouts(outs);
	return (redirs);
}

void print_triple_array(char ***triple)
{
	int i;
	int j;

	i = 0;
	while (triple[i])
	{
		j = 0;
		while (triple[i][j])
		{
			printf("%s ", triple[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	pipex(int nbr_cmds, char ***cmds, char **envp, t_mthings *mt)
{
	int	i;
	t_redirs 	redirs;

	i = -1;
	if (nbr_cmds >= 1)
	{
		if (ft_strcmp(mt->ins[0]->cmd, "SEMINS") != 0)
		{
			dup2(redirs.in, 0);
		}
		while (++i < nbr_cmds - 1)
		{
			redirs = meteredirs(cmds[i], mt->ins, mt->outs);
			child_one(redirs, mt, envp, i);
		}
		redirs = meteredirs(cmds[nbr_cmds - 1], mt->ins, mt->outs);
		execute(redirs, mt, envp, i);
	}
}
