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

#ifndef MINISHELL_H
# define MINISHELL_H

// Libraries

# include<stdio.h>
# include<readline/readline.h>
# include<readline/history.h>
# include<signal.h>
# include<unistd.h>
# include<stdlib.h>
# include<string.h>
# include"pipex.h"

// COLORS

# define YELLOW "\e[1;33m"
# define BLUE "\e[1;34m"
# define RES "\e[0m"

// Structures

typedef struct s_list
{
    char *content;
    struct s_list *next;
}               t_list;

typedef struct s_exporttable
{
    char *key;
    char *value;
    struct s_exporttable *next;
}               t_exporttable;

typedef struct s_cmds
{
    char *cmd;
    char **args;
    struct s_cmds *next;
}               t_cmds;

typedef struct s_lists
{
    t_list **env;
    t_exporttable **export;
//    t_cmds **cmds;
    char *line;
    char **cmds;
}               t_minithings;

// Functions

void sig_handler(void);
void commands(t_minithings *minithings, char **envp);
void builtins(t_minithings *minithings);
int is_builtin(char *str);
int ft_strncmp(const char *s1, const char *s2, size_t n);
char *ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
char *ft_substr(char const *s, int start, size_t len);
char	**ft_split(char const *s, char c);
void    pipex(int nbr_cmds, char **cmds, char **envp);
char *ft_strtrim(char *str);
int ft_strcmp(const char *s1, const char *s2);
char **quote_splitter(char *line);

t_minithings *export(t_minithings *minithings);
void show_export_list(t_minithings *minithings);
t_exporttable *add_export_node(void *key, void *value);
void add_export_node_front(t_exporttable **head, t_exporttable *new);
void add_export_node_back(t_exporttable **lst, t_exporttable *new);
t_exporttable 	*indxexport(t_exporttable *list, int index);
int ft_lstsize(t_exporttable *lst);
int     check_duplicated(t_exporttable **export, char *str);
void    value_modifier(t_exporttable **export, char *value, int i);

void    unset(t_minithings *minithings);

void    ft_sort_list(t_exporttable *tab, int size);
t_list *ft_lstnew(void *content);
void ft_lstadd_back(t_list **lst, t_list *new);
void ft_lstadd_front(t_list **lst, t_list *new);
t_list *indx(t_list *lst, int index);

#endif