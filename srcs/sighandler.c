/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdas-nev <rdas-nev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 4242/42/42 42:42:42 by rdas-nev          #+#    #+#             */
/*   Updated: 4242/42/42 42:42:42 by rdas-nev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../inc/minishell.h"

extern int g_exitcode;

static void	ctrlc(int s)
{
	if (s == 2)
	{
		g_exitcode = 130;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sig_handler(t_minithings *minithings)
{
	(void) minithings;
	signal(SIGINT, &ctrlc);
}

static void	ctrl_c_block(int sig)
{
	if (sig == 2)
	{
		g_exitcode = 130;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	else
		g_exitcode = 0;
}

static void	ctrl_slash_block(int sig)
{
	(void) sig;
	g_exitcode = 131;
	write(1, "Quit (core dumped)\n", 19);
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	sig_handler_block(t_minithings *minithings)
{
	(void) minithings;
	signal(SIGINT, &ctrl_c_block);
	signal(SIGQUIT, &ctrl_slash_block);
}
