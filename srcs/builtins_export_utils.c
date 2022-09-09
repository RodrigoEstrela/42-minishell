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

#include"../inc/minishell.h"

void    ft_sort_list(t_list *tab, int size)
{
    int i;
    int j;
    char *tmp;

    i = 0;
    while (i < size)
    {
        j = i + 1;
        while (j < size)
        {
            if (ft_strncmp(indx(tab, i)->content,
                           indx(tab, j)->content,
                           ft_strlen(indx(tab, i)->content)) > 0)
            {
                tmp = indx(tab, i)->content;
                indx(tab, i)->content = indx(tab, j)->content;
                indx(tab, j)->content = tmp;
            }
            j++;
        }
        i++;
    }
}

int     check_duplicated(t_list *list, char *str)
{
    int i;
    int j;

    i = 0;
    if (!ft_strchr(str, '='))
        j = 0;
    else
        j = ft_strlen(ft_strchr(str, '='));
    while (i < ft_lstsize(list))
    {
        if (ft_strncmp(indx(list, i)->content, str, ft_strlen(str) - j) == 0)
            return (1);
        i++;
    }
    return (0);
}