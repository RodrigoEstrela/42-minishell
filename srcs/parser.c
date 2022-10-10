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


int    get_var_name(char *tmp, int start, int letra, t_cmds **lst)
{
    int i;
    int ctr;
    int var_len;

    i = start -1;
    ctr = 0;
    var_len = 0;
    printf("DOLLAR CENA\n");
    while (tmp[++i]) {
        while (tmp[i] && tmp[++i] != '$');
        while (tmp[i] && tmp[++i] != ' ' && tmp[i] != letra) {
            ctr++;
        }
        printf("\nctr = %d\n\n", ctr);
        ft_lstadd_back(lst, ft_lstnew(ft_strndup(tmp + i - ctr, ctr)));
        if (ctr != 0)
            var_len += ctr + 1;
        ctr = 0;
        i--;
        printf("i = %d\n", i);
        printf("tmp[i] = %c\n", tmp[i]);
    }
    printf("var_len = %d\n", var_len);
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
                printf("VALOR = %s\n", tmp->cmd);
                break;
            }
            tmp2 = tmp2->next;
        }
        if (tmp2 == NULL)
            tmp->cmd = ft_strdup("");
        tmp2 = *export;
        tmp = tmp->next;
    }
    printf("get val\n");
    print_stacks(*vars);
}

void dollar_str(char *tmp, int start, int letra, t_cmds **fds, t_exporttable **export)
{
    t_cmds   **vars;
    int     var_len;
    char   *new_str;

    vars = (t_cmds **)malloc(sizeof(t_cmds *) * 1);
    *vars = NULL;
    var_len = get_var_name(tmp, start, letra, vars);
    print_stacks(*vars);
    get_val_from_export(export, vars);
    printf("VALORES DOS DOLARES\n");
    print_stacks(*vars);
    printf("str_len = %i\n", ft_str_ui_len(tmp, start, letra) - var_len + ft_strlen_vars(*vars));
    new_str = (char *)malloc(sizeof(char) * (ft_str_ui_len(tmp, start, letra) - var_len + ft_strlen_vars(*vars) + 1));

    delete_linked_list(*vars);
    free(vars);
}

char ***parser(char *line, t_exporttable **export)
{
    t_cmds **fds = (t_cmds **)malloc(sizeof(t_cmds *) * 1);
    *fds = NULL;
    int i = -1;
    int size = ft_strlen(line);
    int start = 0;

    if (!line)
        return (NULL);
    while (++i < size) {
        if (line[i] == ' ') {
            ft_lstadd_back(fds, ft_lstnew(str_space_dup(line, start, ' ')));
            start = i + 1;
        }
        else if (line[i] == '"')
        {
            i++;
            start++;
            while (line[++i] != '"')
                ;
            ft_lstadd_back(fds, ft_lstnew(str_space_dup(line, start, '"')));
            dollar_str(line, start, '"', fds, export);
            i += 2;
            start = i;
        }
        else if (line[i] == '|') {
            ft_lstadd_back(fds, ft_lstnew(pipe_str()));
            i += 2;
            start = i;
        }
    }
    if (line[i - 3] != '\"')
        ft_lstadd_back(fds, ft_lstnew(str_space_dup(line, start, ' ')));
    if (line[i - 1] == 32)
        delete_last_node(*fds);
    int cmd_ctr = pipe_counter(*fds) + 1;
    char ***cmd = malloc(sizeof(char **) * (cmd_ctr + 1));
    i = -1;
    while (++i < cmd_ctr) {
        cmd[i] = cmd_maker(*fds, i + 1);
    }
    cmd[i] = NULL;
//    print_triple_pointer(cmd);
    delete_linked_list(*fds);
    free(fds);
    return (cmd);
}