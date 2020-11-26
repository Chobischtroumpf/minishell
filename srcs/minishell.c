/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 12:54:46 by adorigo           #+#    #+#             */
/*   Updated: 2020/11/24 16:48:19 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	prompt_msg(void)
{
	if (get_minishell()->was_eof == 0)
		ft_putstr("\033[32mminishell\033[0m$ ");
}

/*
** signal_handler is the function called in case of a signal being received by
** the program, the function tells the program what to do in case of a SIGINT or
** SIGQUIT signal being received
*/

void		signal_handler(int signbr)
{
	t_minishell	*minishell;

	minishell = get_minishell();
	if (signbr == SIGINT)
	{
		if (minishell->executed == 1)
		{
			minishell->executed = 0;
			ft_putstr("\n");
		}
		if (minishell->was_eof == 1)
		{
			minishell->was_eof = 0;
			ft_putstr("\n");
		}
	}
	else if (signbr == SIGQUIT)
	{
		if (minishell->executed == 1)
		{
			ft_putstr("Quit (core dumped)\n");
			minishell->executed = 0;
		}
		else
			ft_putstr("  \b\b");
	}
}

void		print_lst(void)
{
	int i = 0;
	t_minishell *minish;
	t_cmd *tmp;
	t_rdir *in;
	t_rdir *out;

	minish = get_minishell();
	in = minish->cmd->in;
	out = minish->cmd->out;
	tmp = minish->cmd;

	ft_printf("line : %s\n", minish->line);
	while (minish->tokens[i])
	{
		printf("token: %s\n", minish->tokens[i]);
		i++;
	}
	i = 0;
	while (tmp != NULL)
	{
		while(tmp->argv[i])
			printf("%s\n", tmp->argv[i++]);
		printf("has_path :%d\nis_dir :%d\nis_pipe :%d\n", tmp->has_path, tmp->is_rdir, tmp->pipe);
		while (in != NULL)
		{
			ft_printf("fd : %d\nfile : %s\ndbl : %d\n", in->fd, in->file, in->is_dbl);
			in = in->next;
		}
		while (out != NULL)
		{
			ft_printf("fd : %d\nfile : %s\ndbl : %d\n", out->fd, out->file, out->is_dbl);
			out = out->next;
		}
		tmp = tmp->next;
		i = 0;
	}
}

void		main_execution(void)
{
	t_minishell *minishell;

	minishell = get_minishell();
	while (1)
	{
		prompt_msg();
		if (!ft_line_handle())
			continue;
		if (!ft_cmd_parse(minishell->tokens))
		{
			ft_free_minishell();
			continue;
		}
		// print_lst();
		ft_exec_cmd();
		ft_free_minishell();
	}
	ft_printf("exit\n");
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
	if (ac == 1)
		main_execution();
	else if (ac >= 2 && !ft_strcmp(av[1], "-c"))
	{
		while (1)
		{
			minishell->line = ft_strdup(av[2]);
			if (!ft_lexing())
				exit(minishell->excode);
			if (!(ft_cmd_parse(minishell->tokens)))
			{
				ft_get_exit_code(NO_STATUS, 2);
				break ;
			}
			if (!(ft_exec_cmd()))
			{
				ft_get_exit_code(NO_STATUS, 2);
				break ;
			}
			break ;
		}
	}
	ft_free_minishell();
	ft_free_env();
	return (minishell->excode);
}
