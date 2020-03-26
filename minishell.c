/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 12:54:46 by adorigo           #+#    #+#             */
/*   Updated: 2020/03/26 12:07:10 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_cmd_count()
{
	int ck;
	int cnt;
	char **tokens;

	tokens = get_minishell()->tokens;
	while (*tokens)
	return(cnt);
}


// t_cmd	ft_cmd_split()

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

int		main(void)
{
	int			done;
	int			nbr_tokens;

	t_minishell	*minishell;
	int x;

	minishell = get_minishell();	
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	done = 0;
	while (done == 0)
	{
		x = -1;
		ft_putstr("\n\033[32mminishell\033[0m$ ");
		if (!get_next_line(1, &(minishell->line)))
			break;
		minishell->line = ft_strtrim(minishell->line, " \t\n\v\f\r");
		if (ft_strncmp(minishell->line, "\0", 1))
		{
			if ((nbr_tokens = ft_tokens_count(minishell->line)) == -1)
				continue;
			minishell-> tokens = malloc(sizeof(char*) * nbr_tokens);
			while (++x < nbr_tokens && printf("%d\n", x))
				minishell->tokens[x] = ft_tokens_split(get_minishell()->line, x + 1);
			minishell->tokens[x] = NULL;

			done = ft_exec_cmd();
			// x = 0
			// while(minishell->tokens[++x])
			// 	free(minishell->tokens[x]);
			// free (minishell->tokens);
			// free(minishell->line);
		}
    }
	ft_printf("\n");
}