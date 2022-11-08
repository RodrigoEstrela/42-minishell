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

char	*g_ec = NULL;

void	free_double_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}

void	build_export_table(t_minithings *mt, char **envp)
{
	int		i;
	char	**el;
	char	tmp[1024];

	i = 0;
	el = ft_split(envp[i], '=');
	getcwd(tmp, sizeof(tmp));
	mt->efpath = ft_strjoin(tmp, "/e");
	mt->export = malloc(sizeof(t_exporttable *));
	(*mt->export) = NULL;
	mt->wcode = open(mt->efpath, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	nodefront(mt->export, envvaradd("?", "0", mt));
	free_double_array(el);
	while (envp[i])
	{
		el = ft_split(envp[i], '=');
		nodeback(mt->export, envvaradd(el[0], el[1], mt));
		free_double_array(el);
		i++;
	}
}

void	free_export_table(t_exporttable *export)
{
	t_exporttable	*tmp;

	while (export)
	{
		tmp = export;
		free(tmp->k);
		free(tmp->value);
		export = export->next;
		free(tmp);
	}
	free(export);
}

void	do_things(t_minithings *mt, char **envp)
{
	char	*exitvalue;

	if (g_ec != NULL)
	{
		change_errorcode(mt->export, g_ec);
		g_ec = NULL;
	}
	mt->cmds = parser(mt->line, mt->export);
	if (mt->cmds)
	{
		commands(mt, envp);
		free_triple_pointer(mt->cmds);
		mt->rcode = open(mt->efpath, O_RDONLY);
		exitvalue = get_next_line(mt->rcode);
		while (exitvalue)
		{
			if (slen(exitvalue) > 0)
				change_errorcode(mt->export, exitvalue);
			free(exitvalue);
			exitvalue = get_next_line(mt->rcode);
		}
		free(exitvalue);
		close(mt->rcode);
	}
	else
		free(mt->cmds);
	free(mt->line);
}

int	main(int ac, char **av, char **envp)
{
	t_minithings	*mt;
	char			*colorful_path;

	mt = (t_minithings *) malloc(sizeof(t_minithings));
	build_export_table(mt, envp);
	while (ac != slen(av[ac]))
	{
		sig_handler();
		colorful_path = get_prompt();
		mt->line = readline(colorful_path);
		free(colorful_path);
		if (!mt->line)
			megafree(mt);
		if (!only_space(mt->line))
		{
			add_history(mt->line);
			if (slen(mt->line) > 0)
				do_things(mt, envp);
		}
		else
		{
			free(mt->line);
			free(g_ec);
		}
	}
}
