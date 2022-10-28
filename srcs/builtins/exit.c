/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdas-nev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:08:35 by rdas-nev          #+#    #+#             */
/*   Updated: 2022/07/27 19:07:12 by rdas-nev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../inc/minishell.h"

void	exitin(char ****quad, t_minithings *minithings, int i)
{
	int	exitcode;

	printf("exit\n");
	if (quad[i][0][1])
	{
		if (!ft_isnumber(quad[i][0][1]))
		{
			printf("exit: %s: numeric argument required\n", quad[i][0][1]);
			exitcode = 2;
		}
		else if (quad[i][0][2])
		{
			printf("exit: too many arguments\n");
			change_errorcode(minithings->export, "1");
			return ;
		}
		else
			exitcode = ft_atoi(quad[i][0][1]);
	}
	else
		exitcode = 0;
	freequadpointer(quad);
	exit(exitcode);
}
