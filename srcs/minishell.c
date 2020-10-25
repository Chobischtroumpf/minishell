/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 12:54:46 by adorigo           #+#    #+#             */
/*   Updated: 2020/10/25 16:37:41 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** signal_handler is the function called in case of a signal being received by
** the program, the function tells the program what to do in case of a SIGINT or
** SIGQUIT signal being received
*/

void		signal_handler(int signbr)
{
	if (signbr == SIGINT)
	{
		ft_putstr("\n");
		if (get_minishell()->executed == 1)
			get_minishell()->executed = 0;
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

static int	lexing(t_minishell *minishell)
{
	int			nbr_tokens;
	char		*tmp;
	int			x;

	x = 0;
	if ((nbr_tokens = ft_tokens_count(minishell->line)) == -1)
	{
		ft_printf("you need to close the brackets\n");
		return (0);
	}
	if (!(minishell->tokens = malloc(sizeof(char*) * (nbr_tokens + 1))))
		exit(ft_free_cmd() && 0);
	while (++x < nbr_tokens)
	{
		tmp = ft_tokens_split(minishell->line, x + 1);
		minishell->tokens[x] = ft_strtrim(tmp, " \t\n\v\f\r");
		free(tmp);
	}
	minishell->tokens[x] = NULL;
	return (1);
}

/*
**void	print_lst(t_cmd *cmd)
**{
**	int i = 0;
**	t_cmd *tmp;
**	t_rdir *in;
**	t_rdir *out;
**
**	in = cmd->in;
**	out = cmd->out;
**	tmp = cmd;
**	while (tmp != NULL)
**	{
**		while(tmp->argv[i])
**			printf("%s\n", tmp->argv[i++]);
**		printf("has_path :%d\nis_dir :%d\nis_pipe :%d\n", tmp->has_path, tmp->is_rdir, tmp->pipe);
**		while (in != NULL)
**		{
**			ft_printf("fd : %d\nfile : %s\ndbl : %d\n", in->fd, in->file, in->is_dbl);
**			in = in->next;
**		}
**		while (out != NULL)
**		{
**			ft_printf("fd : %d\nfile : %s\ndbl : %d\n", out->fd, out->file, out->is_dbl);
**			out = out->next;
**		}
**		tmp = tmp->next;
**		i = 0;
**	}
**}
*/

void	main_execution(void)
{
	char		*tmp;
	t_cmd		*tmp2;
	t_minishell	*minishell;

	minishell = get_minishell();
	while (1)
	{
		ft_free_cmd();
		ft_putstr("\033[32mminishell\033[0m$ ");
		if (!get_next_line(1, &tmp))
			break ;
		minishell->line = ft_strtrim(tmp, " \t\n\v\f\r");
		free(tmp);
		if (ft_strncmp(minishell->line, "\0", 1))
		{
			if (lexing(minishell))
				continue;
			if (!ft_cmd_parse(minishell->tokens))
				continue;
			tmp2 = minishell->cmd;
			while (tmp2)
			{
				ft_exec_cmd();
				tmp2 = tmp2->next;
			}
		}
	}
}

int			main(int ac, char **av, char **envv)
{
	t_minishell	*minishell;

	(void)ac;
	(void)av;
	minishell = get_minishell();
	ft_init_env(minishell, envv);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	main_execution();
	ft_free_cmd();
	ft_free_env();
	ft_printf("exit\n");
}
