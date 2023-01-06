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

t_cmds	*ft_lstnew(void *content, int quotes, int redirect)
{
	t_cmds	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->cmd = ft_strdup(content);
	new->quotes = quotes;
	new->redirect = redirect;
	new->next = NULL;
	free(content);
	return (new);
}

void	ft_lstaddback(t_cmds **lst, t_cmds *new)
{
	t_cmds	*tmp;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

int	ft_lstsize(t_extab *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

t_cmds	*idx(t_cmds **cmds, int index)
{
	int		i;
	t_cmds	*lst;

	i = 0;
	lst = *cmds;
	while (lst && lst->next && i < index)
	{
		lst = lst->next;
		i++;
	}
	return (lst);
}
