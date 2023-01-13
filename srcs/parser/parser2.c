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

t_parser	*aspas(t_parser *ctr, char *input,
				t_cmds **cmds, t_extab **export)
{
	ctr->start = ctr->i + 1;
	while (input[++ctr->i] != '"')
		;
	if (ft_strchr(input + ctr->start, '$'))
		adollar(ctr, input, cmds, export);
	else
		aspas_no_dollar(ctr, input, cmds);
	return (ctr);
}

char *get_last_content_in_cmds(t_cmds **cmds)
{
	t_cmds	*tmp;

	if (!cmds || !*cmds)
		return (NULL);
	tmp = *cmds;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp->cmd);
}

t_parser	*dollar(t_parser *ctr, char *i,
					t_cmds **cmds, t_extab **export)
{
	char	*str5;
	char	*str4;
	char 	*str6;
	char	*str7;

	ctr->start = ctr->i;
	while (i[++ctr->i] && i[ctr->i] != ' '
		&& i[ctr->i] != '$' && i[ctr->i] != '"' && i[ctr->i] != '|')
		;
	if (i[ctr->i] == ' ' && i[ctr->i + 1] != '|'
		&& i[ctr->i + 1] && i[ctr->i + 1] != ' ')
	{
		str5 = only_z(i, ctr->start, export);
		str4 = ft_strdup(str5);
		if (i[ctr->start - 1] == ' ')
			ft_lstaddback(cmds, ft_lstnew(ft_strjoin(str4, " "), 0, 0));
		else
		{
			str6 = ft_strdup(ft_last_cmd(*cmds)->cmd);
			str7 = ft_strjoin(str6, str4);
			delete_elem(cmds, sizelst(cmds) - 1);
			ft_lstaddback(cmds, ft_lstnew(ft_strjoin(str7, " "), 0, 0));
			free(str6);
			free(str7);
		}
		free(str4);
		free(str5);
	}
	else
	{
		if (i[ctr->start - 1] == ' ')
			ft_lstaddback(cmds, ft_lstnew(only_z(i, ctr->start, export), 0, 0));
		else
		{
			str4 = only_z(i, ctr->start, export);
			str6 = ft_strdup(get_last_content_in_cmds(cmds));
			if (!str6)
				str7 = ft_strdup(str4);
			else
				str7 = ft_strjoin(str6, str4);
			delete_elem(cmds, sizelst(cmds) - 1);
			if (i[ctr->start + 1] == ' ')
				ft_lstaddback(cmds, ft_lstnew(ft_strjoin(str7, " "), 0, 0));
			else
				ft_lstaddback(cmds, ft_lstnew(ft_strdup(str7), 0, 0));
			free(str4);
			free(str6);
			free(str7);
		}

	}
	ctr->i--;
	return (ctr);
}

t_parser	*every(t_parser *ctr, char *i, t_cmds **cmds)
{
	ctr->start = ctr->i;
	ft_lstaddback(cmds, ft_lstnew(str_super_dup(i, ctr->start, '0'), 0, 0));
	while (i[ctr->i] && i[ctr->i] != ' ' && i[ctr->i] != '$'
		   && i[ctr->i] != '"' && i[ctr->i] != '|' && i[ctr->i] != '\'')
		ctr->i++;
	ctr->i--;
	return (ctr);
}

void	printlist(t_cmds **cmds)
{
	t_cmds	*tmp;

	if (!cmds || !*cmds)
		return ;
	tmp = *cmds;
	while (tmp)
	{
		printf("cnt: %s,  redir: %d quotes: %d\n", tmp->cmd, tmp->redirect, tmp->quotes);
		tmp = tmp->next;
	}
	printf("\n");
}

char	***return_parser(t_parser *ctr, t_cmds **cmds)
{
	char	***cmd;
	int		cmd_ctr;

	cmd_ctr = pipe_counter(*cmds) + 1;
	cmd = malloc(sizeof(char **) * (cmd_ctr + 1));
	ctr->i = -1;
	while (++ctr->i < cmd_ctr)
		cmd[ctr->i] = cmd_maker(*cmds, ctr->i + 1);
	cmd[ctr->i] = NULL;
	delete_linked_list(*cmds);
	free(cmds);
	cleanup(cmd);
	free(ctr);
	return (cmd);
}

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

int redirsdiferentesjuntas(t_cmds **cmds)
{
	t_cmds	*tmp;

	tmp = *cmds;
	while (tmp)
	{
		if (tmp->quotes == 0)
		{
			if (tmp->next && ((tmp->cmd[slen(tmp->cmd) - 2] == '>' && tmp->next->cmd[0] == '<')
				|| (tmp->cmd[slen(tmp->cmd) - 2] == '<' && tmp->next->cmd[0] == '>')
				|| (tmp->cmd[slen(tmp->cmd) - 2] == '<' && tmp->next->cmd[0] == '<')
				|| (tmp->cmd[slen(tmp->cmd) - 2] == '>' && tmp->next->cmd[0] == '>')))
				return (1);
			if (ft_strnstr(tmp->cmd, "<>", 2) || ft_strnstr(tmp->cmd, "><", 2))
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

char	***ezpars(t_parser *ctr, char *input, t_extab **etab, t_mthings *mt)
{
	t_cmds		**cmds;

	if (pipepipe(input))
		return (NULL);
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
