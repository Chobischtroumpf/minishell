/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessandro <alessandro@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 12:54:46 by adorigo           #+#    #+#             */
/*   Updated: 2020/10/21 16:16:15 by alessandro       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** signal_handler is the function called in case of a signal being received by
** the program, the function tells the program what to do in case of a SIGINT or
** SIGQUIT signal being received
*/

void	signal_handler(int signbr)
{
	if (signbr == SIGINT)
	{
		ft_putstr("\n");
		if (get_minishell()->executed == 1)
			get_minishell()->executed = 0;
		else
			ft_putstr("\033[32mminishell\033[0m$ ");
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

int		main(void)
{
	int			done;
	int			nbr_tokens;
	t_minishell	*minishell;
	int			x;
	char		*tmp;
	t_cmd		*tmp2;

	minishell = get_minishell();
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	done = 0;
	while (done == 0)
	{
		x = -1;
		ft_putstr("\033[32mminishell\033[0m$ ");
		if (!get_next_line(1, &(minishell->line)))
			break ;
		minishell->line = ft_strtrim(minishell->line, " \t\n\v\f\r");
		if (ft_strncmp(minishell->line, "\0", 1))
		{
			if ((nbr_tokens = ft_tokens_count(minishell->line)) == -1)
			{
				ft_printf("you need to close the brackets\n");
				continue;
			}
			if (!(minishell->tokens = malloc(sizeof(char*) * (nbr_tokens + 1))))
				return (0);
			while (++x < nbr_tokens)
			{
				tmp = ft_tokens_split(minishell->line, x + 1);
				minishell->tokens[x] = ft_strtrim(tmp, " \t\n\v\f\r");
				free(tmp);
			}
			minishell->tokens[x] = NULL;
			if (!ft_cmd_parse(minishell->tokens))
				continue;
			tmp2 = minishell->cmd;
			while (tmp2)
			{
				// ft_check_dollar();
				ft_exec_cmd();
				// ft_printf("minishell : %p\n", minishell);
				// ft_printf("cmd : %p\n", minishell->cmd);
				// ft_printf("line : %p\n", minishell->line);
				// ft_printf("tokens : %p\n", minishell->tokens);
				// ft_printf("cmd->argv : %p\n", minishell->cmd->argv);
				// ft_printf("cmd->next : %p\n", minishell->cmd->next);
				tmp2 = tmp2->next;
			}
		}
		ft_free_cmd();
	}
	ft_printf("\n");
}
