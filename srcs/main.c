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

static t_minithings *init_lists(t_minithings *minithings, char **envp)
{
    int i;

    i = 0;
    minithings->env = malloc(sizeof(t_list));
    minithings->export = malloc(sizeof(t_list));
    ft_lstadd_front(minithings->env, ft_lstnew(envp[i]));
    ft_lstadd_front(minithings->export, ft_lstnew(envp[i++]));
    while (envp[i]) {
        ft_lstadd_back(minithings->env, ft_lstnew(envp[i]));
        ft_lstadd_back(minithings->export, ft_lstnew(envp[i++]));
    }
    ft_sort_list(*minithings->export, ft_lstsize(*minithings->export));
    return (minithings);
}

int main(int ac, char **av, char **envp)
{
    (void)av;
    t_minithings *minithings;

    minithings = (t_minithings *)malloc(sizeof(t_minithings *) * 2);
    minithings = init_lists(minithings, envp);
    while(ac)
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
