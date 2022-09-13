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

static int cmpateaoigual(const char *s1, const char *s2)
{
    int i;

    i = 0;
    while (s1 && s2 && s1[i] == s2[i])
    {
        if (s1[i] == '=' && s2[i] == '=')
            return(1);
        i++;
    }
    if (s1[i] == s2[i] && s2[i + 1] == '\0')
        return(1);
    return(0);
}

int     check_duplicated(t_list *list, char *str)
{
    int i;

    i = 0;
    while (i < ft_lstsize(list))
    {
        if (cmpateaoigual(indx(list, i)->content, str) == 1)
            return (i);
        i++;
    }
    return (0);
}

void    value_modifier(t_list **export, int dup, char *str)
{
    indx((*export), dup)->content = str;
}