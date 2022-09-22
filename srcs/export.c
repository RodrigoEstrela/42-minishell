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

static void show_export_list(t_minithings *minithings) {
    t_list *tmp;

    tmp = *minithings->export;
    while (tmp) {
        printf("declare -x %s\n", tmp->content);
        tmp = tmp->next;
    }
}

void export(t_minithings *minithings)
{
    if (ft_strlen(minithings->line) == 6)
        show_export_list(minithings);
    else {
        char *str = ft_substr(minithings->line, 7, ft_strlen(minithings->line) - 7);
        int dup = check_duplicated(*minithings->export, str);
        if (dup == 0)
            ft_lstadd_back(minithings->export, ft_lstnew(str));
        else
            value_modifier(minithings->export, dup, str);
    }
}