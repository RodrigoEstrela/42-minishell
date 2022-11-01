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

t_exporttable	*envvaradd(char *key, char *value, t_minithings *mt)
{
	t_exporttable	*new;

	new = malloc(sizeof(t_exporttable));
	if (!new)
		return (NULL);
	if (ft_strcmp(key, "") == 0)
	{
		printf("amazingshell: export: `=%s': not a valid identifier\n", value);
		write(mt->wcode, "1\n", 2);
		return (NULL);
	}
	if (!value)
		value = "";
	new->k = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}

void	nodefront(t_exporttable **head, t_exporttable *new)
{
	if (!head || !new)
		return ;
	new->next = *head;
	*head = new;
}

void	nodeback(t_exporttable **lst, t_exporttable *new)
{
	t_exporttable	*tmp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	tmp->next = (*lst)->next;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
