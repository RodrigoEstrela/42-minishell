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

int uneven_quotes(char *input, char duborsing)
{
    int i;
    int quotes;

    i = -1;
    quotes = 0;
    while (input[++i])
    {
        if (input[i] == duborsing)
            quotes++;
    }
    if (quotes % 2 != 0)
        return (1);
    return (0);
}

void    print_triple_pointer(char ***triple)
{
    int i;
    int j;

    i = 0;
    while (triple[i])
    {
        j = 0;
        printf("New Comand\n");
        while (triple[i][j])
        {
            printf("%s\n", triple[i][j]);
            j++;
        }
        i++;
    }
}

char ***parser(t_minithings *minithings)
{
    int i;
    int j;
    int k;
    int start;
    char ***cmds;

    i = 0;
    j = 0;
    k = 0;
    cmds = malloc(sizeof(char ***) * 1);

    while (minithings->line[i])
    {
        if (minithings->line[i] == '\'')
        {
            if (uneven_quotes(minithings->line, '\'') == 0)
            {
                i++;
                start = i;
                while (minithings->line[i] != '\'')
                    i++;
                cmds[k][j] = ft_substr(minithings->line, start, i - start);
                j++;
            }
            else
            {
                printf("missing closing single quote\n");
                return (NULL);
            }
        }
        else if (minithings->line[i] == '"')
        {
            if (uneven_quotes(minithings->line, '"') == 0)
            {
                i++;
                start = i;
                while (minithings->line[i] != '"')
                    i++;
                cmds[k][j] = ft_substr(minithings->line, start, i - start);
                j++;
            }
            else
                printf("missing closing double quote\n");
            return (NULL);
        }
        else if (minithings->line[i] == '|')
        {
            i++;
            j = 0;
            k++;
        }
        else if (minithings->line[i] == ' ')
        {
            while (minithings->line[i] == ' ')
                i++;
            i--;
            j++;
        }
        i++;
    }
//    print_triple_pointer(cmds);
    return (cmds);
}