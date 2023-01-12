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

#include"../../inc/minishell.h"

void	til(t_mthings *mt, int indx)
{
	chdir(getenv("HOME"));
	if (chdir(mt->cmds[indx][1] + 2) != 0)
	{
		printf("minishell: %s: Invalid directory\n", mt->cmds[indx][1]);
		write(mt->wcode, "1\n", 2);
	}
	else
		write(mt->wcode, "0\n", 2);
}

void	cd(t_mthings *mt, int indx)
{
	printf("cd\n");
	if (mt->cmds[indx][2])
	{
		printf("amazingshell: cd: too many arguments\n");
		write(mt->wcode, "1\n", 2);
	}
	else if (!mt->cmds[indx][1] || ft_strcmp(mt->cmds[indx][1], "~") == 0)
	{
		if (chdir(getenv("HOME")) != 0)
		{
			printf("amazingshell: cd: HOME not set\n");
			write(mt->wcode, "1\n", 2);
		}
		else
			write(mt->wcode, "0\n", 2);
	}
	else if (mt->cmds[indx][1][0] == '~' && mt->cmds[indx][1][1] == '/')
		til(mt, indx);
	else if (chdir(mt->cmds[indx][1]) != 0)
	{
		printf("minishell: %s: Invalid directory\n", mt->cmds[indx][1]);
		write(mt->wcode, "1\n", 2);
	}
	else
		write(mt->wcode, "0\n", 2);
}

void	pwd(t_mthings *mt)
{
	char	cwd[1024];

	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
	write(mt->wcode, "0\n", 2);
}
