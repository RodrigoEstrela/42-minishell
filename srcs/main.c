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
    ft_lstadd_front(minithings->env, ft_lstnew(envp[i]));
    while (envp[i]) {
        ft_lstadd_back(minithings->env, ft_lstnew(envp[i++]));
    }
    return (minithings);
}

static t_minithings *build_export_table(t_minithings *minithings, char **envp)
{
    int i;
    char **envp_line;

    i = 0;
    envp_line = ft_split(envp[i], '=');
    minithings->export = malloc(sizeof(t_exporttable));
    add_export_node_front(minithings->export, add_export_node(envp_line[0], envp_line[1]));
    i++;
    while (envp[i])
    {
        envp_line = ft_split(envp[i], '=');
        add_export_node_back(minithings->export, add_export_node(envp_line[0], envp_line[1]));
        i++;
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
    minithings = build_export_table(minithings, envp);
    while(ac)
    {
        sig_handler();
        minithings->line = readline(BLUE"amazing"YELLOW"shell: "RES);
        add_history(minithings->line);
        if (!minithings->line)
            exit(1);
        minithings->cmds = ft_split(minithings->line, '|');

       /* int i = -1;
        int first_q = -1;
        int second_q = -1;
        char *tmp;
        while (minithings->cmds[++i]) {
            //printf("minithings->cmds[++i] = %s\n", minithings->cmds[i]);
            tmp = ft_strchr(minithings->cmds[i], '"');
            if (tmp) {
                first_q = i;
                while (minithings->cmds[i]) {
                    *tmp++;
                    if (ft_strchr(tmp, '"')) {
                        second_q = i;
                        break;
                    }
                    i++;
                }
                if (second_q == -1) {
                    printf("Error: missing closing quote\n");
                    break;
                }
             //   minithings->cmds[first_q] = ft_strtrim(minithings->cmds[first_q], "\"");
                if (second_q != first_q) {
                    printf("fuwefwenfweufwenfweu\n");
                    minithings->cmds[first_q] = ft_strjoin(minithings->cmds[first_q], "|");
                    minithings->cmds[first_q] = ft_strjoin(minithings->cmds[first_q], minithings->cmds[second_q]);
                    minithings->cmds[second_q] = NULL;
                }
            }
        }
        //printf("minithings->cmds[0] = %s\n", minithings->cmds[0]);*/
        commands(minithings, envp);
    }
}
