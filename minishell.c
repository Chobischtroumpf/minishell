/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 12:54:46 by adorigo           #+#    #+#             */
/*   Updated: 2020/03/05 17:31:55 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_minishell	*get_minishell(void)
{
	static t_minishell	minishell;
		
	return (&minishell);
}

char		**get_built_in(void)
{
	static char* built_in[8] = {
		"echo",
		"cd",
		"pwd",
		"export",
		"unset",
		"env",
		"exit",
		NULL
	};
	return (built_in);
}

void		init_env_list(char **env)
{
	char		**cut;
	int			i;
	t_minishell	*minishell;

	minishell = get_minishell();


int			ft_exec_pwd(void)
{
	char cwd[PATH_MAX];

	if (!(getcwd(cwd, sizeof(cwd))))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (EXIT_FAILURE);
	}
	ft_printf("%s\n", cwd);
	return (EXIT_SUCCESS);
}

// int fd_exec_echo();

static int 	ft_parse_line(char *line)
{
	int ret;
	
	line = ft_strtrim(line, " \t\n\v\f\r");
	if (!strncmp(line, "echo", 4))
		ret = 0;
		// ret = ft_exec_cd();
	if (!ft_strncmp(line, "pwd", 3))
		ret = ft_exec_pwd();
	else if (!ft_strncmp(line, "exit", 4))
		ret = 1;
	else
	{
		ret = 0;
	}
	return (ret);
}

void		signal_handler(int signbr)
{
	if (signbr == SIGINT)
	{
		ft_putstr("\n");
		if (get_minishell()->executed == 1)
			get_minishell()->executed = 0;
		else
		ft_putstr("\033[32mminishell\033[0m$ ");	
	} else if (signbr == SIGQUIT)
	{
		if (get_minishell()->executed == 1)
		{
			ft_putstr("Quit (core dumped)\n");
			get_minishell()->executed = 0;
		}
	}
}


int			main(void)
{
	int			done;
	t_minishell	*minishell;

	init_minishell();
	minishell = get_minishell();	
	// signal(SIGINT, signal_handler);
	// signal(SIGQUIT, signal_handler);
	done = 1;
	while (done != 0)
	{
		ft_putstr("\033[32mminishell\033[0m$ ");
		get_next_line(1, &(minishell->line));
		// ft_printf("%d", done);
		// if (done != 1)
			// break;
		// ft_printf("%s\n", line);
		done = ft_parse_line(minishell->line);
    }
}