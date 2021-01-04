/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolin <ncolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 10:56:04 by ncolin            #+#    #+#             */
/*   Updated: 2021/01/04 15:47:27 by ncolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//counts the consecutive pipes in the chain of commands
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

//main function for pipe handling
void handle_pipe(t_cmd *cmd, int pipe_nb)
{
	int pipe_fds[pipe_nb * 2];
	int pids[pipe_nb + 1];
	int i;
	printf("number of pipes : %d \n", count_pipes(cmd));
	i = 0;
	// create the pipes in array pipefds
	// eg : for 2 consecutive pipes : pipe_fds = [pipeA.0, pipeA.1, pipeB.0, pipeB.1]
	while (i < pipe_nb)
	{
		if (pipe(&pipe_fds[i * 2]) == -1)
			printf("error pipe\n");
		i++;
	}
	i = 0;
	while (i <= pipe_nb)
	{
		pids[i] = fork();
		if (!pids[i]) //child process
		{
			//exec commands
		}
		else if (pids[i] == -1)
			exit(0); //needs a proper exit + error
		cmd = cmd->next;
		i++;
	}
	//close pipes
	// /return (cmd);
}