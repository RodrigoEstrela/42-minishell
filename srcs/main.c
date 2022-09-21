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

static t_lists *init_lists(t_lists *lists, char **envp)
{
    int i;

    i = 0;
    lists->env = malloc(sizeof(t_list));
    lists->export = malloc(sizeof(t_list));
    ft_lstadd_front(lists->env, ft_lstnew(envp[i]));
    ft_lstadd_front(lists->export, ft_lstnew(envp[i++]));
    while (envp[i]) {
        ft_lstadd_back(lists->env, ft_lstnew(envp[i]));
        ft_lstadd_back(lists->export, ft_lstnew(envp[i++]));
    }
    ft_sort_list(*lists->export, ft_lstsize(*lists->export));
    return (lists);
}

int main(int ac, char **av, char **envp)
{
    (void)ac;
    (void)av;
    t_lists *minithings;

    minithings = (t_lists *)malloc(sizeof(t_lists *) * 2);
    minithings = init_lists(minithings, envp);
    while(1)
    {
        sig_handler();
        minithings->line = readline(BLUE"amazing"YELLOW"shell: "RES);
        add_history(minithings->line);
        if (!minithings->line)
        {
            printf("exit\n");
            exit(1);
        }
        minithings->cmds = ft_split(minithings->line, '|');
        commands(minithings, envp);
    }
}
