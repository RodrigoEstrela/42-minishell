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

int	check_duplicated(t_extab **export, char *str)
{
	int	i;

	i = 0;
	while (i < ft_lstsize(*export))
	{
		if (ft_strcmp(ind(*export, i)->k, str) == 0)
			return (i);
		i++;
	}
	return (0);
}

void	valmod(t_extab **export, char *value, int i, t_mthings *mt)
{
	ind(*export, i)->value = ft_strdup(value);
	write(mt->wcode, "0\n", 2);
}

t_extab	*copy_list(t_extab *export, t_mthings *minithings)
{
	t_extab	*new;
	t_extab	*tmp;

	new = NULL;
	while (export)
	{
		tmp = envvaradd(export->k, export->value, minithings);
		nodeback(&new, tmp);
		export = export->next;
	}
	return (new);
}

void	showenv(t_extab *tmp2)
{
	tmp2 = tmp2->next;
	while (tmp2)
	{
		if (slen(tmp2->value) > 0)
			printf("%s=%s\n", tmp2->k, tmp2->value);
		tmp2 = tmp2->next;
	}
}

void	show_export_list(t_mthings *minithings, int flag)
{
	t_extab	*tmp;
	t_extab	*tmp2;

	tmp = copy_list(*minithings->export, minithings);
	tmp2 = tmp;
	if (flag == 0)
	{
		ft_sort_list(tmp, ft_lstsize(tmp2));
		while (tmp2)
		{
			if (tmp2->k[0] != '?')
			{
				if (slen(tmp2->value) > 0)
					printf("declare -x %s=\"%s\"\n", tmp2->k, tmp2->value);
				else
					printf("declare -x %s\n", tmp2->k);
			}
			tmp2 = tmp2->next;
		}
	}
	else
		showenv(tmp2);
	delete_export(tmp);
	write(minithings->wcode, "0\n", 2);
}
