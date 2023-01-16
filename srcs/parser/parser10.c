/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser10.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-albe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 10:05:30 by fde-albe          #+#    #+#             */
/*   Updated: 2022/11/01 12:17:33 by fde-albe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	doispipesseguidos(t_cmds **cmds)
{
	t_cmds	*tmp;

	tmp = *cmds;
	while (tmp)
	{
		if (tmp->next && ft_strcmp(tmp->cmd, "|314159265358979323846") == 0
			&& ft_strcmp(tmp->next->cmd, "|314159265358979323846") == 0
			&& tmp->next->next)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int	redirsdiferentesjuntas(t_cmds **cmds)
{
	t_cmds	*t;

	t = *cmds;
	while (t)
	{
		if (t->quotes == 0)
		{
			if (t->next && ((t->cmd[slen(t->cmd) - 2] == '>'
						&& t->next->cmd[0] == '<')
					|| (t->cmd[slen(t->cmd) - 2] == '<'
						&& t->next->cmd[0] == '>')
					|| (t->cmd[slen(t->cmd) - 2] == '<'
						&& t->next->cmd[0] == '<')
					|| (t->cmd[slen(t->cmd) - 2] == '>'
						&& t->next->cmd[0] == '>')))
				return (1);
			if (ft_strnstr(t->cmd, "<>", 2) || ft_strnstr(t->cmd, "><", 2))
				return (1);
		}
		t = t->next;
	}
	return (0);
}

int	is_whitespace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

int	redirnotok(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
		if (input[i] == '>' || input[i] == '<')
			if (is_whitespace(input + i + 1))
				return (1);
	return (0);
}

char	***ezpars(t_parser *ctr, char *input, t_extab **etab, t_mthings *mt)
{
	t_cmds		**cmds;

	if (pipepipe(input) || redirnotok(input))
	{
		free(ctr);
		return (NULL);
	}
	cmds = (t_cmds **)malloc(sizeof(t_cmds *) * 1);
	*cmds = NULL;
	ctr->i = -1;
	while (++ctr->i < slen(input))
	{
		if (input[ctr->i] == '\'')
			ctr = barra(ctr, input, cmds);
		else if (input[ctr->i] == '"')
			ctr = aspas(ctr, input, cmds, etab);
		else if (input[ctr->i] == '$')
			ctr = dollar(ctr, input, cmds, etab);
		else if (input[ctr->i] == '|')
			ft_lstaddback(cmds, ft_lstnew(
					ft_strdup("|314159265358979323846"),
					0, 0));
		else if (input[ctr->i] != ' ')
			ctr = every(ctr, input, cmds);
	}
	cleanup_redirsnomeio(cmds);
	if (redirsdiferentesjuntas(cmds) == 1)
		return (missing_command_after_redir(ctr, cmds));
	cleanup_redirects(cmds);
	cleanup_output(cmds, mt);
	cleanup_input(cmds, mt);
	if ((ft_strcmp(ft_last_cmd(*cmds)->cmd, "|314159265358979323846") == 0
			&& input[slen(input) - 1] == '|')
		|| (ft_strcmp((*cmds)->cmd, "|314159265358979323846") == 0)
		|| doispipesseguidos(cmds) == 1
		|| ft_strcmp(ft_last_cmd(*cmds)->cmd, "|314159265358979323846") == 0)
	{
		return (missing_command_after_pipe(ctr, cmds));
	}
	return (return_parser(ctr, cmds));
}
