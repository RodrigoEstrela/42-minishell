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

int	pipepipe(char *input)
{
	int	flag;
	int	i;

	flag = 0;
	i = -1;
	while (input[++i])
	{
		if (input[i] == '\'')
		{
			if (flag == 0)
				flag = 1;
			else if (flag == 1)
				flag = 0;
		}
		else if (input[i] == '"')
		{
			if (flag == 0)
				flag = 2;
			else if (flag == 2)
				flag = 0;
		}
		if (input[i] == '|' && input[i + 1] == '|' && flag == 0)
		{
			printf("minishell: syntax error near unexpected token `||'");
			return (1);
		}
	}
	return (0);
}

int	redirectcounter(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (str[0] == '>' || str[0] == '<')
		count = -1;
	while (str[i] != '\0')
	{
		while (str[i] && str[i] != '>' && str[i] != '<')
			i++;
		if (str[i] && (str[i] == '>' || str[i] == '<'))
		{
			if (str[i + 1] && (str[i + 1] == '>' || str[i + 1] == '<'))
				i++;
			i++;
		}
		count++;
	}
	return (count);
}

char	*ft_redirdup(char *str)
{
	char	*dest;
	int		i;

	i = 0;
	dest = malloc(sizeof(char) * (slen(str) + 1));
	if (!dest)
		return (NULL);
	if (str[i] == '>' || str[i] == '<')
	{
		dest[i] = str[i];
		i++;
	}
	if (str[i] == '>' || str[i] == '<')
	{
		dest[i] = str[i];
		i++;
	}
	while (str[i] && (str[i] != '<' && str[i] != '>'))
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	cleanup_redirsnomeio(t_cmds **cmds)
{
	t_cmds	*tmp;
	char	*str;
	char	*str2;
	int		i;
	int		counter;

	tmp = *cmds;
	i = 0;
	while (tmp)
	{
		counter = redirectcounter(tmp->cmd);
		if (counter >= 2 && tmp->quotes == 0)
		{
			while (counter > 1 && tmp)
			{
				str = ft_redirdup(tmp->cmd);
				addinindex(cmds, ft_lstnew(
						ft_strdup(tmp->cmd + slen(str)), 0, 0), i + 1);
				free(tmp->cmd);
				str2 = ft_strdup(str);
				tmp->cmd = ft_strjoin(str2, " ");
				free(str);
				free(str2);
				i++;
				tmp = tmp->next;
				counter--;
			}
		}
		i++;
		tmp = tmp->next;
	}
}
