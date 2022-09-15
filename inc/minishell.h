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

// Functions

void sig_handler(void);
void commands(char *line, t_list **env, t_list **export, char **cmds, char **envp);
void builtins(char *line, t_list **env, t_list **export, char **cmds, char **envp);
int ft_strncmp(const char *s1, const char *s2, size_t n);
void    ft_sort_list(t_list *tab, int size);
char *ft_strchr(const char *s, int c);
int     check_duplicated(t_list *list, char *str);
char	*ft_strdup(const char *s1);
char *ft_substr(char const *s, int start, size_t len);
void    value_modifier(t_list **export, int dup, char *str);
char	**ft_split(char const *s, char c);
void    pipex(int ac, char **av, char **envp);
char *ft_strtrim(char *str);

t_list *ft_lstnew(void *content);
void ft_lstadd_back(t_list **lst, t_list *new);
void ft_lstadd_front(t_list **lst, t_list *new);
int ft_lstsize(t_list *lst);
t_list *indx(t_list *lst, int index);

#endif