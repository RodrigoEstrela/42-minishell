/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                       	:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-albe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 10:05:30 by fde-albe          #+#    #+#             */
/*   Updated: 4242/42/42 42:42:42 by 42424242         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_parser	barra(t_parser ctr, char *input, t_cmds **cmds)
{
	ctr.start = ctr.i + 1;
	while (input[++ctr.i] != '\'')
		;
	if (input[ctr.i + 1] == ' ')
	{
		char *str = str_space_dup(input, ctr.start, '\'');
		ft_lstadd_back(cmds, ft_lstnew(ft_strjoin(str, " ")));
		free(str);
	}
	else
		ft_lstadd_back(cmds, ft_lstnew(str_space_dup(input, ctr.start, '\'')));
	return (ctr);
}

t_parser	aspas(t_parser ctr, char *input, t_cmds **cmds, t_exporttable **export)
{
	ctr.start = ctr.i + 1;
	while (input[++ctr.i] != '"')
		;
	if (ft_strchr(input + ctr.start, '$'))
	{
		if (input[ctr.i + 1] == ' ')
		{
			char *str2 = dollar_expansion(input, ctr.start, '"', export);
			ft_lstadd_back(cmds, ft_lstnew(ft_strjoin(str2, " ")));
			free(str2);
		}
		else
			ft_lstadd_back(cmds, ft_lstnew(dollar_expansion(input, ctr.start, '"', export)));
	}
	else
	{
		if (input[ctr.i + 1] == ' ')
		{
			char *str3 = str_space_dup(input, ctr.start, '"');
			ft_lstadd_back(cmds, ft_lstnew(ft_strjoin(str3, " ")));
			free(str3);
		}
		else
			ft_lstadd_back(cmds, ft_lstnew(str_space_dup(input, ctr.start, '"')));
	}
	return (ctr);
}

t_parser	dollar(t_parser ctr, char *input, t_cmds **cmds, t_exporttable **export)
{
	char	*str5;
	char	*str4;

	ctr.start = ctr.i;
	while (input[++ctr.i] && input[ctr.i] != ' ' && input[ctr.i] != '$' && input[ctr.i] != '"' && input[ctr.i] != '|')
		;
	if (input[ctr.i] == ' ' && input[ctr.i + 1] != '|' && input[ctr.i + 1] && input[ctr.i + 1] != ' ')
	{
		str5 = only_z(input, ctr.start, export);
		str4 = ft_strdup(str5);
		ft_lstadd_back(cmds, ft_lstnew(ft_strjoin(str4, " ")));
		free(str4);
		free(str5);
	}
	else
		ft_lstadd_back(cmds, ft_lstnew(only_z(input, ctr.start, export)));
	ctr.i--;
	return (ctr);
}

t_parser	every(t_parser ctr, char *input, t_cmds **cmds)
{
	ctr.start = ctr.i;
	ft_lstadd_back(cmds, ft_lstnew(str_super_dup(input, ctr.start, '0')));
	while (input[ctr.i] && input[ctr.i] != ' ' && input[ctr.i] != '$' && input[ctr.i] != '"' && input[ctr.i] != '|' && input[ctr.i] != '\'')
		ctr.i++;
	ctr.i--;
	return (ctr);
}

char ***return_parser(t_parser ctr, t_cmds **cmds)
{
	char ***cmd;
	int cmd_ctr;

	cmd_ctr = pipe_counter(*cmds) + 1;
	cmd = malloc(sizeof(char **) * (cmd_ctr + 1));
	ctr.i = -1;
	while (++ctr.i < cmd_ctr)
		cmd[ctr.i] = cmd_maker(*cmds, ctr.i + 1);
	cmd[ctr.i] = NULL;
	delete_linked_list(*cmds);
	free(cmds);
	cleanup(cmd);
	return (cmd);
}

char ***ez_parsing(t_parser ctr, char *input, t_exporttable **export)
{
	t_cmds		**cmds;

	cmds = (t_cmds **)malloc(sizeof(t_cmds *) * 1);
	*cmds = NULL;
	ctr.i = -1;
	while (++ctr.i < slen(input))
	{
		if (input[ctr.i] == '\'')
			ctr = barra(ctr, input, cmds);
		else if (input[ctr.i] == '"')
			ctr = aspas(ctr, input, cmds, export);
		else if (input[ctr.i] == '$')
			ctr = dollar(ctr, input, cmds, export);
		else if (input[ctr.i] == '|')
			ft_lstadd_back(cmds, ft_lstnew(pipe_str()));
		else if (input[ctr.i] != ' ')
			ctr = every(ctr, input, cmds);
	}
	return (return_parser(ctr, cmds));
}