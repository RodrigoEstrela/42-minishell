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
		{
			printf("minishell: syntax error near unexpected token `||'");
			return (1);
		}
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
			else if (slen(tmp->cmd) > 2 && tmp->cmd[1] != '>')
			{
				tmp->redirect = 1;
				tmp2 = tmp->cmd;
				tmp->cmd = ft_strdup(tmp2 + 1);
				free(tmp2);
			}
			else if (tmp->cmd[1] == '>')
			{
				tmp2 = tmp->cmd;
				tmp->cmd = ft_strdup(tmp2 + 1);
				free(tmp2);
			}
		}
		if (!ft_strncmp(tmp->cmd, "<<", 2)  && tmp->quotes == 0)
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
		if (tmp->cmd[0] == '>' && tmp->cmd[1] != '>' && tmp->quotes == 0)
		{
			if (tmp->next && slen(tmp->cmd) == 2)
			{
				tmp->redirect = 3;
				free(tmp->cmd);
				tmp->cmd = ft_strdup(tmp->next->cmd);
				delete_elem(cmds, j + 1);
			}
			else if (slen(tmp->cmd) > 2 && tmp->cmd[1] != '<')
			{
				tmp->redirect = 3;
				tmp2 = tmp->cmd;
				tmp->cmd = ft_strdup(tmp2 + 1);
				free(tmp2);
			}
			else if (tmp->cmd[1] == '<')
			{
				tmp2 = tmp->cmd;
				tmp->cmd = ft_strdup(tmp2 + 1);
				free(tmp2);
				cleanup_redirects(cmds);
			}
		}
		if (!ft_strncmp(tmp->cmd, ">>", 2) && tmp->quotes == 0)
		{
			if (tmp->next && slen(tmp->cmd) == 3)
			{
				tmp->redirect = 4;
				free(tmp->cmd);
				tmp->cmd = ft_strdup(tmp->next->cmd);
				delete_elem(cmds, j + 1);
			}
			else if (slen(tmp->cmd) > 2 && tmp->cmd[2] != '<')
			{
				tmp->redirect = 4;
				tmp2 = tmp->cmd;
				tmp->cmd = ft_strdup(tmp2 + 2);
				free(tmp2);
			}
			else if (tmp->cmd[2] == '<')
			{
				tmp2 = tmp->cmd;
				tmp->cmd = ft_strdup(tmp2 + 2);
				free(tmp2);
				cleanup_redirects(cmds);
			}
		}
		j++;
		tmp = tmp->next;
	}
}

void	cleanup_output2(t_mthings *mt)
{
	int		i;

	i = 0;
	if (!*mt->outs)
	{
		ft_lstaddback(mt->outs, ft_lstnew(ft_strdup("SEMOUTS"), 0, 0));
		return;
	}
	if (ft_strcmp(idx(mt->outs, 0)->cmd, "PIPETEMPIPE") == 0)
	{
		addinindex(mt->outs, ft_lstnew(ft_strdup("SEMOUTS"), 0, 0), 0);
		i++;
	}
	if (ft_strcmp(idx(mt->outs, sizelst(mt->outs))->cmd, "PIPETEMPIPE") == 0)
		addinindex(mt->outs, ft_lstnew(ft_strdup("SEMOUTS"), 0, 0), sizelst(mt->outs));
	while (i <= sizelst(mt->outs))
	{
		if (ft_strcmp(idx(mt->outs, i)->cmd, "PIPETEMPIPE") == 0
			&& ft_strcmp(idx(mt->outs, i + 1)->cmd, "PIPETEMPIPE") == 0)
			addinindex(mt->outs, ft_lstnew(ft_strdup("SEMOUTS"), 0, 0), i++ + 1);
		i++;
	}
}

void	cleanup_output(t_cmds **cmds, t_mthings *mt)
{
	t_cmds	*tmp;
	int 	apagar[347];
	int		i;
	int 	j;

	tmp = *cmds;
	j = 0;
	i = 0;
	apagar[0] = 454545;
	mt->outs = malloc(sizeof(t_cmds));
	*mt->outs = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->cmd, "|314159265358979323846") == 0 && tmp->next)
		{
			ft_lstaddback(mt->outs, ft_lstnew(ft_strdup("PIPETEMPIPE"), 0, 0));
			tmp = tmp->next;
			j++;
		}
		if ((tmp->redirect == 3 || tmp->redirect == 4))
		{
			apagar[i++] = j;
			ft_lstaddback(mt->outs, ft_lstnew(tmp->cmd, 0, tmp->redirect));
		}
		j++;
		tmp = tmp->next;
	}
	while (i--)
		delete_elem(cmds, apagar[i]);
	cleanup_output2(mt);
}

void	cleanup_input2(t_mthings *mt)
{
	int		i;

	i = 0;
	if (!*mt->ins)
	{
		ft_lstaddback(mt->ins, ft_lstnew(ft_strdup("SEMINS"), 0, 0));
		return;
	}
	if (ft_strcmp(idx(mt->ins, 0)->cmd, "PIPETEMPIPE") == 0)
	{
		addinindex(mt->ins, ft_lstnew(ft_strdup("SEMINS"), 0, 0), 0);
		i++;
	}
	if (ft_strcmp(idx(mt->ins, sizelst(mt->ins))->cmd, "PIPETEMPIPE") == 0)
		addinindex(mt->ins, ft_lstnew(ft_strdup("SEMINS"), 0, 0), sizelst(mt->ins));
	while (i <= sizelst(mt->ins))
	{
		if (ft_strcmp(idx(mt->ins, i)->cmd, "PIPETEMPIPE") == 0
		&& ft_strcmp(idx(mt->ins, i + 1)->cmd, "PIPETEMPIPE") == 0)
			addinindex(mt->ins, ft_lstnew(ft_strdup("SEMINS"), 0, 0), i++ + 1);
		i++;
	}
}

void	cleanup_input(t_cmds **cmds, t_mthings *mt)
{
	t_cmds	*tmp;
	int 	apagar[347];
	int		i;
	int 	j;

	tmp = *cmds;
	j = 0;
	i = 0;
	apagar[0] = 454545;
	mt->ins = malloc(sizeof(t_cmds));
	*mt->ins = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->cmd, "|314159265358979323846") == 0 && tmp->next)
		{
			ft_lstaddback(mt->ins, ft_lstnew(ft_strdup("PIPETEMPIPE"), 0, 0));
			tmp = tmp->next;
			j++;
		}
		if ((tmp->redirect == 1 || tmp->redirect == 2))
		{
			apagar[i++] = j;
			ft_lstaddback(mt->ins, ft_lstnew(tmp->cmd, 0, tmp->redirect));
		}
		j++;
		tmp = tmp->next;
	}
	while (i--)
		delete_elem(cmds, apagar[i]);
	cleanup_input2(mt);
}
