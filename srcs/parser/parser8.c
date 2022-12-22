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

void	cleanup_redirects(t_cmds **cmds)
{
	int		j;
	t_cmds	*tmp;
	char	*tmp2;

	j = 0;
	tmp = *cmds;
	while (tmp)
	{
		if (tmp->cmd[0] == '<' && tmp->cmd[1] != '<' && tmp->quotes == 0)
		{
			if (tmp->next && slen(tmp->cmd) == 2)
			{
				tmp->redirect = 1;
				free(tmp->cmd);
				tmp->cmd = ft_strdup(tmp->next->cmd);
				delete_elem(cmds, j + 1);
			}
			else if (slen(tmp->cmd) > 2)
			{
				tmp->redirect = 1;
				tmp2 = tmp->cmd;
				tmp->cmd = ft_strdup(tmp2 + 1);
				free(tmp2);
			}
		}
		else if (!ft_strncmp(tmp->cmd, "<<", 2)  && tmp->quotes == 0)
		{
			if (tmp->next && slen(tmp->cmd) == 3)
			{
				tmp->redirect = 2;
				tmp->cmd = ft_strdup(tmp->next->cmd);
				delete_elem(cmds, j + 1);
			}
			else if (slen(tmp->cmd) > 3)
			{
				tmp->redirect = 2;
				tmp2 = tmp->cmd;
				tmp->cmd = ft_strdup(tmp2 + 2);
				free(tmp2);
			}
		}
		else if (tmp->cmd[0] == '>' && tmp->cmd[1] != '>' && tmp->quotes == 0)
		{
			if (tmp->next && slen(tmp->cmd) == 2)
			{
				tmp->redirect = 3;
				free(tmp->cmd);
				tmp->cmd = ft_strdup(tmp->next->cmd);
				delete_elem(cmds, j + 1);
			}
			else if (slen(tmp->cmd) > 2)
			{
				tmp->redirect = 3;
				tmp2 = tmp->cmd;
				tmp->cmd = ft_strdup(tmp2 + 1);
				free(tmp2);
			}
		}
		else if (!ft_strncmp(tmp->cmd, ">>", 2) && tmp->quotes == 0)
		{
			if (tmp->next && slen(tmp->cmd) == 3)
			{
				tmp->redirect = 4;
				free(tmp->cmd);
				tmp->cmd = ft_strdup(tmp->next->cmd);
				delete_elem(cmds, j + 1);
			}
			else if (slen(tmp->cmd) > 2)
			{
				tmp->redirect = 4;
				tmp2 = tmp->cmd;
				tmp->cmd = ft_strdup(tmp2 + 2);
				free(tmp2);
			}
		}
		j++;
		tmp = tmp->next;
	}
}

void	cleanup_output(t_cmds **cmds, t_mthings *mt)
{
	t_cmds	*tmp;
	int 	apagar[347];
	int		i;
	int 	j;
	int		size;
	int		hold;

	(void)mt;
	tmp = *cmds;
	j = 0;
	i = 0;
	apagar[0] = 454545;
	while (tmp)
	{
		if (ft_strcmp(tmp->cmd, "|314159265358979323846") == 0 && tmp->next)
		{
			tmp = tmp->next;
			j++;
		}
		if ((tmp->redirect == 3 || tmp->redirect == 4))
		{
			apagar[i++] = j;
		}
		j++;
		tmp = tmp->next;
	}
	hold = i;
	int a = 0, b = 0, c = 0;
	mt->outs = malloc(sizeof(char *));
	while (c++ < hold)
	{
		if (apagar[c] == 31415)
		{
			a++;
			b = 0;
		}
		else
		{
			mt->outs[a][b++] = ft_strdup(idx(cmds, apagar[c])->cmd);
		}
	}
	if (apagar[0] != -1)
	{
		while (i--)
		{
			printf("apagar[%d] = %d\n", i, apagar[i]);
			if (apagar[i] != 31415) {
				delete_elem(cmds, apagar[i]);
			}
		}
	}
	size = sizelst(cmds);
	printf("i: %d\n", i);
	printf("size: %i\n", size);
}
