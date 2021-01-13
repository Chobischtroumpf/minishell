/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 12:54:46 by adorigo           #+#    #+#             */
/*   Updated: 2021/01/13 16:40:18 by nathan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** void		print_lst(void);
*/

static void	prompt_msg(void)
{
	char		pwd[100];
	static int	too_long = 0;

	if (get_minishell()->was_eof == 0)
	{
		if (getcwd(pwd, 100))
		{
			too_long = 0;
			ft_putstr_fd("\033[32m", 2);
			ft_putstr_fd(pwd, 2);
			if (!ft_strcmp(pwd, "/"))
				ft_putstr_fd("\033[0m\n \033[36m->\033[0m ", 2);
			else
				ft_putstr_fd("/\033[0m\n \033[36m->\033[0m ", 2);
		}
		else
		{
			if (too_long == 0)
				ft_putstr_fd("\033[31;1;4mpath_name too long,\
					reverting back to original prompt\033[0m\n", 2);
			too_long = 1;
			ft_putstr_fd("\033[32mminishell\033[0m\n \033[36m->\033[0m ", 2);
		}
	}
}

/*
** signal_handler is the function called in case of a signal being received by
** the program, the function tells the program what to do in case of a SIGINT or
** SIGQUIT signal being received
*/

void		signal_handler(int signbr)
{
	if (signbr == SIGINT)
	{
		ft_putchar('\n');
		if (get_minishell()->executed == 1)
			get_minishell()->executed = 0;
		else
		{
			get_minishell()->was_eof = 0;
			prompt_msg();
			free(get_minishell()->line);
			get_minishell()->line = NULL;
		}
	}
	else if (signbr == SIGQUIT)
	{
		if (get_minishell()->executed == 1)
		{
			ft_putstr("Quit (core dumped)\n");
			get_minishell()->executed = 0;
		}
	}
}

void		main_execution(void)
{
	t_minishell	*minishell;

	minishell = get_minishell();
	while (1)
	{
		prompt_msg();
		if (!ft_line_handle(0))
			continue ;
		minishell->was_eof = 0;
		if (!ft_cmd_parse(minishell->tokens))
		{
			ft_free_minishell();
			continue;
		}
		ft_exec_cmd();
		ft_free_minishell();
	}
}

void		ft_init_pwd(void)
{
	char		cwd[PATH_MAX];

	if (!ft_find_by_key2("PWD"))
		ft_add_env2("PWD", getcwd(cwd, sizeof(cwd)));
}

int			main(int ac, char **av, char **envv)
{
	t_minishell	*minishell;

	minishell = get_minishell();
	ft_init_env(minishell, envv);
	ft_init_pwd();
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	ft_shlvl();
	update_lastcmd("minishell");
	if (ac == 1)
		main_execution();
	else if (ac >= 2 && !ft_strcmp(av[1], "-c"))
	{
		minishell->line = ft_strdup(av[2]);
		if (!(minishell->tokens = ft_lexing(minishell->line)))
			return (1 || ft_exit_error());
		if (!(ft_cmd_parse(minishell->tokens)))
			return (1 || ft_exit_error());
		if (!(ft_exec_cmd()))
			return (1 || ft_exit_error());
	}
	ft_free_minishell();
	ft_free_env();
	return (minishell->exval);
}
