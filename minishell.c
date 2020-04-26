/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 12:54:46 by adorigo           #+#    #+#             */
/*   Updated: 2020/04/24 12:04:13 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cmd_count(void)
{
	int		i;
	int		j;
	int		cnt;
	char	**tokens;

	i = -1;
	j = -1;
	cnt = 1;
	tokens = get_minishell()->tokens;
	while (tokens[++i])
	{
		printf("%s\n", tokens[i]);
		if ((!ft_strcmp(tokens[i], ";") ||  !ft_strcmp(tokens[i], "|")) &&
			tokens[i - 1] && tokens[i + 1])
			cnt++;
		if ((tokens[i + 1] && !ft_strcmp(tokens[i], ";") && 
			!ft_strcmp(tokens[i + 1], ";")) || !ft_strcmp(tokens[0], "|") ||
			(tokens[i + 1] && !ft_strcmp(tokens[i], "|") && 
			!ft_strcmp(tokens[i + 1], "|")))
			return (-1);
	}
	if (!tokens[0])
		cnt = 0;
	return (cnt);
}

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
	int			x;

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
				return(0);
			while (++x < nbr_tokens)
				minishell->tokens[x] = ft_tokens_split(minishell->line, x + 1);
			minishell->tokens[x] = NULL;
			x = 0;
			minishell->nbr_cmd = ft_cmd_count();
			printf("%d\n", minishell->nbr_cmd);
			// split_cmd();
			// done = ft_exec_cmd();
		}
	}
	ft_printf("\n");
}
