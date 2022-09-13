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

void	*ft_memset(void *b, int c, size_t len)
{
    unsigned char	*ptr;

    ptr = b;
    while (len-- > 0)
        *ptr++ = c;
    return (b);
}

void	ft_bzero(void *s, size_t n)
{
    ft_memset(s, 0, n);
}

void	*ft_calloc(size_t count, size_t size)
{
    void	*ptr;

    ptr = (void *)malloc(count * size);
    if (!ptr)
        exit(0);
    ft_bzero(ptr, count * size);
    return (ptr);
}

static int	count_words(const char *str, char c)
{
    int	i;
    int	trigger;

    i = 0;
    trigger = 0;
    while (*str)
    {
        if (*str != c && trigger == 0)
        {
            trigger = 1;
            i++;
        }
        else if (*str == c)
            trigger = 0;
        str++;
    }
    return (i);
}

static char	*word_dup(const char *str, int start, int finish)
{
    char	*word;
    int		i;

    i = 0;
    word = ft_calloc((finish - start + 1), sizeof(char));
    while (start < finish)
        word[i++] = str[start++];
    word[i] = '\0';
    return (word);
}

char	**ft_split(char const *s, char c)
{
    int 	i;
    int 	j;
    int		index;
    char	**split;

    split = ft_calloc((count_words(s, c) + 1), sizeof(char *));
    if (!s || !(split))
        return (0);
    i = 0;
    j = 0;
    index = -1;
    while (i <= ft_strlen(s))
    {
        if (s[i] != c && index < 0)
            index = i;
        else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
        {
            split[j++] = word_dup(s, index, i);
            index = -1;
        }
        i++;
    }
    split[j] = 0;
    return (split);
}

static int	ft_char_in_set(char c, char const *set)
{
    size_t	i;

    i = 0;
    while (set[i])
    {
        if (set[i] == c)
            return (1);
        i++;
    }
    return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
    char	*str;
    size_t	i;
    size_t	start;
    size_t	end;

    if (!s1 || !set)
        return (0);
    start = 0;
    while (s1[start] && ft_char_in_set(s1[start], set))
        start++;
    end = ft_strlen(s1);
    while (end > start && ft_char_in_set(s1[end - 1], set))
        end--;
    str = (char *)malloc(sizeof(*s1) * (end - start + 1));
    if (!str)
        return (NULL);
    i = 0;
    while (start < end)
        str[i++] = s1[start++];
    str[i] = 0;
    return (str);
}