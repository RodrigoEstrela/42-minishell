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

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
    size_t i;

    i = 0;
    if (!s1 || !s2)
        return (-1);
    while (i < n && s1[i] && s2[i])
    {
        if (s1[i] != s2[i])
            return (s1[i] - s2[i]);
        i++;
    }
    if (i == n)
        return (0);
    return (s1[i] - s2[i]);
}

int ft_strlen(const char *s)
{
    int i;

    i = 0;
    while (s[i])
        i++;
    return (i);
}

char	*ft_strdup(const char *s1)
{
    char	*str;
    size_t	i;

    str = (char *)malloc(sizeof(*s1) * (ft_strlen(s1) + 1));
    if (!str)
        return (NULL);
    i = 0;
    while (s1[i])
    {
        str[i] = s1[i];
        i++;
    }
    str[i] = 0;
    return (str);
}

char *ft_strchr(const char *s, int c)
{
    while (*s)
    {
        if (*s == c)
            return ((char *)s);
        s++;
    }
    if (c == 0)
        return ((char *)s);
    return (NULL);
}

char *ft_substr(char const *s, int start, size_t len)
{
    char *str;
    size_t i;

    if (!s)
        return (NULL);
    if (start > ft_strlen(s))
        return (ft_strdup(""));
    str = (char *)malloc(sizeof(char) * (len + 1));
    if (!str)
        return (NULL);
    i = 0;
    while (i < len && s[start])
    {
        str[i] = s[start];
        i++;
        start++;
    }
    str[i] = 0;
    return (str);
}