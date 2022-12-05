/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-albe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 10:05:30 by fde-albe          #+#    #+#             */
/*   Updated: 2022/11/01 12:17:33 by fde-albe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	pipepipe(char *input)
{
	int	flag;
	int	i;

	flag = 0;
	i = -1;
	while (input[++i])
	{
		if (input[i] == '\'')
		{
			if (flag == 0)
				flag = 1;
			else if (flag == 1)
				flag = 0;
		}
		else if (input[i] == '"')
		{
			if (flag == 0)
				flag = 2;
			else if (flag == 2)
				flag = 0;
		}
		if (input[i] == '|' && input[i + 1] == '|' && flag == 0)
			return (1);
	}
	return (0);
}

void	delete_elem(t_cmds **lst, int index)
{
	t_cmds	*tmp;
	t_cmds	*prev;

	tmp = *lst;
	if (index == 0)
	{
		*lst = tmp->next;
		free(tmp->cmd);
		free(tmp);
		return ;
	}
	while (index--)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	prev->next = tmp->next;
	free(tmp->cmd);
	free(tmp);
}

void	cleanup2(t_cmds **cmds)
{
	int		j;
	t_cmds	*tmp;

	j = 0;
	tmp = *cmds;
	while (tmp)
	{
		if (tmp->cmd[0] == '<' && slen(tmp->cmd) == 2)
		{
			if (tmp->next)
			{
				tmp->cmd = ft_strjoin("INPUTREDIR1", tmp->next->cmd);
				delete_elem(cmds, j + 1);
			}
		}
		else if (tmp->cmd[0] == '>' && slen(tmp->cmd) == 2)
		{
			if (tmp->next)
			{
				tmp->cmd = ft_strjoin("OUTPUTREDIR1", tmp->next->cmd);
				delete_elem(cmds, j + 1);
			}
		}
		else if (!ft_strcmp(tmp->cmd, "<< ") && slen(tmp->cmd) == 3)
		{
			if (tmp->next)
			{
				tmp->cmd = ft_strjoin("HEREDOC", tmp->next->cmd);
				delete_elem(cmds, j + 1);
			}
		}
		else if (!ft_strcmp(tmp->cmd, ">> ") && slen(tmp->cmd) == 3)
		{
			if (tmp->next)
			{
				tmp->cmd = ft_strjoin("APPEND", tmp->next->cmd);
				delete_elem(cmds, j + 1);
			}
		}
		j++;
		tmp = tmp->next;
	}
}
