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

void	addinindex(t_cmds **lst, t_cmds *new, int index)
{
	t_cmds	*tmp;
	t_cmds	*prev;

	tmp = *lst;
	if (index == 0)
	{
		new->next = tmp;
		*lst = new;
		return ;
	}
	while (index--)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	prev->next = new;
	new->next = tmp;
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

void	cleanup_output(t_cmds **cmds)
{
	t_cmds	*tmp;
	int 	apagar[347];
	int		sitio[347];
	int		m;
	int 	out;
	int		meter;
	int		i;
	int 	j;

	tmp = *cmds;
	j = 0;
	i = 0;
	m = 0;
	out = -1;
	apagar[i++] = -1;
	sitio[m++] = -1;
	meter = 0;
	while (tmp)
	{
		while (ft_strcmp(tmp->cmd, "|314159265358979323846") != 0 && tmp->next)
		{
			printf("entrou no while\n");
			if ((tmp->redirect == 3 || tmp->redirect == 4))
			{
				out = j;
				apagar[i++] = j;
			}
			meter++;
			j++;
			tmp = tmp->next;

		}
		sitio[m++] = meter++;
		tmp = tmp->next;
	}
	while (sitio[--m] != -1)
	{
		printf("sitio: %d\n", sitio[m]);
		addinindex(cmds, ft_lstnew(idx(cmds, out)->cmd, 0, idx(cmds, out)->redirect), sitio[m]);
	}
//	if (out != -1)
	while (apagar[--i] != -1)
		delete_elem(cmds, apagar[i]);
}