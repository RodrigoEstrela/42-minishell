/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MINISHELL                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdas-nev <rdas-nev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 4242/42/42 42:42:42 by rdas-nev          #+#    #+#             */
/*   Updated: 4242/42/42 42:42:42 by rdas-nev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../inc/minishell.h"

int	ft_strstr_index(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == to_find[j])
		{
			while (str[i] == to_find[j] && str[i] && to_find[j])
			{
				i++;
				j++;
			}
			if (to_find[j] == '\0')
				return (str[i]);
			else
				j = 0;
		}
		i++;
	}
	return (-1);
}

char	**key_and_value(char **cmd, char *line, int *p)
{
	char	**key_value;
	int		i;

	i = 0;
	key_value = malloc(sizeof(char *) * 3);
	while (cmd[p[0]][i] && cmd[p[0]][i] != '=')
		i++;
	key_value[0] = ft_substr(cmd[p[0]], 0, i);
	if (cmd[p[0]][i] == '=' && (ft_strstr_index(line, cmd[p[0]]) == '"'
	|| ft_strstr_index(line, cmd[p[0]]) == '\''
	|| ft_strstr_index(line, cmd[p[0]]) == '$'))
	{
		p[0]++;
		key_value[1] = ft_substr(cmd[p[0]], 0, slen(cmd[p[0]]));
	}
	else if (cmd[p[0]][i] == '=')
		key_value[1] = ft_substr(cmd[p[0]], i + 1, slen(cmd[p[0]]) - i);
	else
		key_value[1] = NULL;
	key_value[2] = NULL;
	return (key_value);
}

void	change_errorcode(t_exporttable **export, char *code)
{
	t_exporttable	*tmp;

	tmp = *export;
	while (tmp->k[0] != '?')
	{
		tmp = tmp->next;
	}
	free(tmp->value);
	tmp->value = ft_strdup(code);
	tmp->value[slen(tmp->value) - 1] = '\0';
}

void	mod_or_add(t_minithings *mt, int ind, char **var)
{
	if (ind)
	{
		if (var[1])
			valmod(mt->export, var[1], ind, mt);
	}
	else
	{
		nodeback(mt->export, envvaradd(var[0], var[1], mt));
		write(mt->wcode, "0\n", 2);
	}
	free_double_array(var);
}

void	export(t_minithings *mt)
{
	int		*i;
	char	**var;
	int		ind;

	i = malloc(sizeof(int));
	i[0] = 0;
	if (ft_strcmp(mt->cmds[0][0], "export") == 0 && !mt->cmds[0][1])
		show_export_list(mt, 0);
	else if (mt->cmds[0][1])
	{
		while (mt->cmds[0][++i[0]])
		{
			var = key_and_value(mt->cmds[0], mt->line, i);
			ind = check_duplicated(mt->export, var[0]);
			mod_or_add(mt, ind, var);
		}
	}
	free(i);
}
