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

int ft_str_ui_len(const char *s, int start, int letra) {
    int i;

    i = start;
    while (s[i] && s[i] != letra) {
        i++;
    }
    return (i - start);
}

char *pipe_str(void){
    char *str;

    str = malloc(sizeof(char) * 2);
    str[0] = '|';
    str[1] = '\0';
    return (str);
}

char *str_space_dup(const char *s1, int start, int letra)
{
    char *str;
    size_t i;
    size_t j;

    j = 0;
    if (!s1) {
        exit(42);
    }
    str = (char *)malloc(ft_str_ui_len(s1, start, letra) + 1);
    if (!str) {
        return (NULL);
    }
    i = start;
    while (s1[i] && s1[i] != letra)
    {
        str[j] = s1[i];
        j++;
        i++;
    }
    str[j] = '\0';
    ft_strlen(str);
    return (str);
}

int pipe_counter(t_cmds *fds) {
    int i;

    i = 0;
    while (fds) {
        if (fds->cmd[0] == '|')
            i++;
        fds = fds->next;
    }
    return (i);
}

int arg_ctr(t_cmds *fds, int nbr) {
    int i;

    i = 0;
    while (fds && nbr > 0) {
        if (nbr == 1)
            i++;
        if (fds->cmd[0] == '|') {
            nbr--;
        }
        if (fds->next == NULL)
            i++;
        fds = fds->next;
    }
    return (i - 1);
}


char **cmd_maker(t_cmds *fds, int nbr)
{
    char **cmd;
    int argn;
    int i;

    i = -1;
    argn = arg_ctr(fds, nbr);
    cmd = malloc(sizeof(char *) * (argn + 1));
    while (nbr > 1 && fds->next)
    {
        if (fds->cmd[0] == '|' || fds->next == NULL)
            nbr--;
        fds = fds->next;
    }
    while (++i < argn && fds)
    {
        cmd[i] = ft_strdup(fds->cmd);
        fds = fds->next;
    }
    cmd[i] = NULL;
    return (cmd);
}


void    delete_linked_list(t_cmds *list)
{
    t_cmds *tmp;

    while (list)
    {
        tmp = list;
        list = list->next;
        free(tmp->cmd);
        free(tmp);
    }
}

void free_triple_pointer(char ***triple)
{
    int i;
    int j;

    i = 0;
    while (triple[i])
    {
        j = 0;
        while (triple[i][j])
        {
            free(triple[i][j]);
            j++;
        }
        free(triple[i]);
        i++;
    }
    free(triple);
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

void delete_last_node(t_cmds *node)
{
    t_cmds *tmp;

    while (node->next)
    {
        tmp = node;
        node = node->next;
    }
    free(tmp->next->cmd);
    free(tmp->next);
    tmp->next = NULL;
}

void    print_stacks(t_cmds *stck_a)
{
    printf("\n################\n");
    while (stck_a)
    {
        printf("%s\n", stck_a->cmd);
        stck_a = stck_a->next;
    }
    printf("\n################\n");
}

char *ft_strndup(const char *s1, size_t n)
{
    char *str;
    size_t i;

    i = -1;
    if (!s1) {
        exit(42);
    }
    str = (char *)malloc(n + 1);
    if (!str) {
        return (NULL);
    }
    while (s1[++i] && i < n)
        str[i] = s1[i];
    str[i] = '\0';
    return (str);
}

int ft_strlen_vars(t_cmds *vars)
{
    int i;
    t_cmds *tmp;

    i = 0;
    tmp = vars;
    while (tmp)
    {
        i += ft_strlen(tmp->cmd);
        tmp = tmp->next;
    }
    return (i);
}


int    get_var_name(char *input, int start, int divider, t_cmds **lst)
{
    int i;
    int ctr;
    int var_len;

    i = start -1;
    ctr = 0;
    var_len = 0;
    while (input[++i]) {
        while (input[i] && input[++i] != '$');
        while (input[i] && input[++i] != ' ' && input[i] != divider) {
            ctr++;
        }
        ft_lstadd_back(lst, ft_lstnew(ft_strndup(input + i - ctr, ctr)));
        if (ctr != 0)
            var_len += ctr + 1;
        ctr = 0;
        i--;
    }
    return (var_len);
}

void get_val_from_export(t_exporttable **export, t_cmds **vars)
{
    t_cmds *tmp;
    t_exporttable *tmp2;

    tmp = *vars;
    tmp2 = *export;
    while (tmp)
    {
        while (tmp2)
        {
            if (ft_strcmp(tmp->cmd, tmp2->key) == 0)
            {
                free(tmp->cmd);
                tmp->cmd = ft_strdup(tmp2->value);
                break;
            }
            tmp2 = tmp2->next;
        }
        if (tmp2 == NULL)
            tmp->cmd = ft_strdup("");
        tmp2 = *export;
        tmp = tmp->next;
    }
}

void dollar_expanded(char *input, char *new_str, int start, int divider, t_cmds **vars)
{
    int i;
    int j;
    int g;
    t_cmds *tmpvars;

    tmpvars = *vars;
    i = start - 1;
    j = -1;
    g = -1;
    while (input[++i] != divider)
    {
        if (input[i] == '$')
        {
            while (tmpvars->cmd[++g])
                new_str[++j] = tmpvars->cmd[g];
            while (input[++i] != ' ' && input[i] != divider)
                ;
        }
        else
            new_str[++j] = input[i];
    }
    new_str[++j] = '\0';
    printf("chegou ao fim desta cena\n");
}

char  *dollar_expansion(char *input, int start, int divider, t_exporttable **export)
{
    t_cmds   **vars;
    int     var_len;
    char   *new_str;

    vars = (t_cmds **)malloc(sizeof(t_cmds *) * 1);
    *vars = NULL;
    var_len = get_var_name(input, start, divider, vars);
    get_val_from_export(export, vars);
    new_str = (char *)malloc(sizeof(char) * (ft_str_ui_len(input, start, divider) - var_len + ft_strlen_vars(*vars) + 1));
    printf("passou do malloc\n");
    dollar_expanded(input, new_str, start, divider, vars);
    printf("passou do dollar_expanded\n");
    delete_linked_list(*vars);
    free(vars);
    return (new_str);
}

char ***parser(char *input, t_exporttable **export)
{
    t_cmds **cmds = (t_cmds **)malloc(sizeof(t_cmds *) * 1);
    *cmds = NULL;
    int i = -1;
    int size = ft_strlen(input);
    int start = 0;

    if (!input)
        return (NULL);
    while (++i < size) {
        if (input[i] == ' ') {
            ft_lstadd_back(cmds, ft_lstnew(str_space_dup(input, start, ' ')));
            start = i + 1;
        }
        else if (input[i] == '"')
        {
            i++;
            start++;
            while (input[++i] != '"')
                ;
            if (ft_strchr(input + start, '$'))
                ft_lstadd_back(cmds, ft_lstnew(dollar_expansion(input, start, '"', export)));
            else
                ft_lstadd_back(cmds, ft_lstnew(str_space_dup(input, start, '"')));
            i += 2;
            start = i;
        }
        else if (input[i] == '$')
        {
            printf("dollar\n");
            i++;
            start++;
            while (input[++i] != ' ' && input[i] != '\0')
                ;
            ft_lstadd_back(cmds, ft_lstnew(dollar_expansion(input, start, ' ', export)));
            printf("passou do ft_lstadd_back\n");
            start = i;
        }
        else if (input[i] == '|') {
            ft_lstadd_back(cmds, ft_lstnew(pipe_str()));
            i += 2;
            start = i;
        }
    }
    printf("passou do while\n");
    if (input[i - 3] != '\"') {
        ft_lstadd_back(cmds, ft_lstnew(str_space_dup(input, start, ' ')));
    }
    printf("1\n");
    if (input[i - 1] == 32) {
        delete_last_node(*cmds);
    }
    printf("2\n");
    int cmd_ctr = pipe_counter(*cmds) + 1;
    printf("3 - cmd counter = %d\n", cmd_ctr);
    char ***cmd = malloc(sizeof(char **) * (cmd_ctr + 1));
    i = -1;
    printf("4\n");
    while (++i < cmd_ctr) {
        cmd[i] = cmd_maker(*cmds, i + 1);
    }
    cmd[i] = NULL;
    printf("5\n");
    delete_linked_list(*cmds);
    free(cmds);
    printf("chegou ao return\n");
    return (cmd);
}