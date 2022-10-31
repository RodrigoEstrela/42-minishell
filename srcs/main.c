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

void	free_double_array(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free(array[i]);
	free(array);
}

char	*ft_strjoin_triple(char *s1, char *s2, char *s3)
{
	char	*str;
	int		i;
	int		j;
	int		l;

	i = -1;
	j = -1;
	l = -1;
	str = (char *)malloc(sizeof(char) * (slen(s1) + slen(s2) + slen(s3) + 1));
	while (s1[++i])
		str[i] = s1[i];
	while (s2[++j])
		str[i + j] = s2[j];
	while (s3[++l])
		str[i + j + l] = s3[l];
	str[i + j + l] = '\0';
	return (str);
}

char	*paint_prompt(char *str, char *color)
{
	char	*tmp;

	tmp = ft_strjoin_triple(color, str, RES);
	free(str);
	return (tmp);
}

char	*paint_prompt_2(char *str, char *color)
{
	char	*tmp;

	tmp = ft_strjoin_triple(color, str, RES);
	return (tmp);
}

char	*get_prompt(void)
{
	char	*prompt;
	char	*cwd;
	char	*user;
	char	*tmp;

	cwd = getcwd(NULL, 0);
	user = getenv("USER");
	cwd = paint_prompt(cwd, YELLOW);
	user = paint_prompt_2(user, GREEN);
	tmp = ft_strjoin_triple(user, ":", cwd);
	prompt = ft_strjoin_triple(tmp, " $> ", "");
	free(tmp);
	free(cwd);
	free(user);
	return (prompt);
}

static t_minithings	*build_export_table(t_minithings *mt, char **envp)
{
	int		i;
	char	**el;

	i = 0;
	el = ft_split(envp[i], '=');
	mt->export = malloc(sizeof(t_exporttable *));
	(*mt->export) = NULL;
	nodefront(mt->export, envvaradd("?", "0", mt->export));
	free_double_array(el);
	while (envp[i])
	{
		el = ft_split(envp[i], '=');
		nodeback(mt->export, envvaradd(el[0], el[1], mt->export));
		free_double_array(el);
		i++;
	}
	mt->writeexitcode = open("exitfile", O_WRONLY | O_CREAT, 0777);
	return (mt);
}

void	free_export_table(t_exporttable *export)
{
	t_exporttable	*tmp;

	while (export)
	{
		tmp = export;
		export = export->next;
		free(tmp->k);
		free(tmp->value);
		free(tmp);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_minithings	*mt;
	char			*colorful_path;
	char			*exitvalue;

	exitvalue = malloc(4);
	mt = (t_minithings *)malloc(sizeof(t_minithings) * 2);
	build_export_table(mt, envp);
	while (ac != slen(av[ac]))
	{
		sig_handler();
		colorful_path = get_prompt();
		mt->line = readline(colorful_path);
		free(colorful_path);
		if (!mt->line)
		{
			free_export_table(*mt->export);
			free(exitvalue);
			write(1, "exit\n", 5);
			execve("/bin/rm", (char *[]){"/bin/rm", "exitfile", NULL}, envp);
			exit(0);
		}
		add_history(mt->line);
		if (slen(mt->line) > 0)
		{
			mt->cmds = parser(mt->line, mt->export);
			if (mt->cmds)
			{
				commands(mt, envp);
				free_triple_pointer(mt->cmds);
				mt->readexitcode = open("exitfile", O_RDONLY);
				read(mt->readexitcode, exitvalue, 4);
				if (slen(exitvalue) > 0)
					change_errorcode(mt->export, exitvalue);
				close(mt->readexitcode);
			}
			else
				free(mt->cmds);
			free(mt->line);
		}
	}
}
