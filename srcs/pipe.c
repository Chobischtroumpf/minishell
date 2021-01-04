/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolin <ncolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 10:56:04 by ncolin            #+#    #+#             */
/*   Updated: 2021/01/04 15:18:43 by ncolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_pipes(t_cmd *cmd)
{
	int i;

	i = 0;
	while (cmd)
	{
		if (cmd->pipe)
			i++;
		else
			break ;
		cmd = cmd->next;
	}
	return (i);
}

void handle_pipe(t_cmd *cmd, int pipe_nb)
{
	int pipe_fds[pipe_nb * 2];
	// int pids[pipe_nb + 1];
	int i;
	
	printf("number of pipes : %d \n", count_pipes(cmd));
	i = 0;
	while (i < pipe_nb)
	{
		if (pipe(&pipe_fds[i * 2]) == -1)
			printf("error pipe\n");
		i++;
	}
	// int pid = fork();
	// if (pid == 0)
	// {
	// 	close(pipe_fds[0]);
	// 	write(pipe_fds[1], &cmd->argv[0][0], sizeof(int));
	// }
	// else
	// {
	// 	int message;
	// 	close(pipe_fds[1]);
	// 	read(pipe_fds[0], &message, sizeof(int));
	// 	printf("received : %c\n", (char)message);
	// }
}