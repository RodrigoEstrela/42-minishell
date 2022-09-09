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

int main(int ac, char **av, char **envp)
{
    (void)ac;
    (void)av;
    char *line;
    t_list **env;
    t_list **export;
    int i;

    i = 0;
    env = malloc(sizeof(t_list));
    export = malloc(sizeof(t_list));
    ft_lstadd_front(env, ft_lstnew(envp[i]));
    ft_lstadd_front(export, ft_lstnew(envp[i++]));
    while (envp[i]) {
        ft_lstadd_back(env, ft_lstnew(envp[i]));
        ft_lstadd_back(export, ft_lstnew(envp[i++]));
    }
    ft_sort_list(*export, ft_lstsize(*export));
    while(1)
    {
        sig_handler();
        line = readline(BLUE"amazing"YELLOW"shell: "RES);
        add_history(line);
        commands(line, env, export);
        if (!line)
        {
            printf("exit\n");
            exit(1);
        }
    }
}
