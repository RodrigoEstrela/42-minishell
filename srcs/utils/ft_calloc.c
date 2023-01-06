/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-albe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 10:05:30 by fde-albe          #+#    #+#             */
/*   Updated: 2022/11/01 12:17:33 by fde-albe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

extern char	*g_ec;

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

void	megafree(t_mthings *mt)
{
	free_export_table(*mt->export);
	free(mt->export);
	free(mt->line);
	free(mt->efpath);
	delete_linked_list(*mt->ins);
	free(mt->ins);
	delete_linked_list(*mt->outs);
	free(mt->outs);
	free(mt);
	write(1, "exit\n", 5);
	exit(0);
}

