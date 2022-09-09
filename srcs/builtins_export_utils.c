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

void    ft_sort_int_tab(t_list *tab, unsigned int size)
{
    unsigned int i;
    unsigned int j;
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
