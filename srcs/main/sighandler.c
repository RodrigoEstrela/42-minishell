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

#include"../../inc/minishell.h"

extern char *g_ec;

static void	ctrlc(int s)
{
	if (s == 2)
	{
		write(1, "\n", 1);
		g_ec = ft_strdup("130\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sig_handler(void)
{
	signal(SIGINT, &ctrlc);
	signal(SIGQUIT, SIG_IGN);
}

static void	ctrl_c_block(int sig)
{
	if (sig == 2)
	{
		write(1, "\n", 1);
		g_ec = ft_strdup("130\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	else
		g_ec = NULL;
}

static void	ctrl_slash_block(int sig)
{
	(void) sig;
	write(1, "Quit (core dumped)\n", 19);
	g_ec = ft_strdup("131\n");
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	sig_handler_block(void)
{
	signal(SIGINT, &ctrl_c_block);
	signal(SIGQUIT, &ctrl_slash_block);
}
