/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nathan <nathan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 10:56:04 by ncolin            #+#    #+#             */
/*   Updated: 2021/01/06 22:44:40 by nathan           ###   ########.fr       */
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

static void
	close_all(int pipes[], int nb)
{
	int i;

	i = 0;
	while (i < 2 * nb)
		close(pipes[i++]);
}

static void
	dup2_and_close_pipe(int pipes[], int i, int nb)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (i < nb)
		dup2(pipes[i * 2 + 1], 1);
	if (i > 0)
		dup2(pipes[(i - 1) * 2], 0);
	close_all(pipes, nb);
}

static void
	close_pipe_and_wait(int pipes[], int nb, int cpid[])
{
	int status;
	int	i;
	
	close_all(pipes, nb);
	i = 0;
	while (i < nb + 1)
	{
		waitpid(cpid[i], &status, 0);
		i++;
	}
	ft_get_exit_code(status, NO_EXCODE);
}

int
	create_pipes(int pipes[], int nb)
{
	int i;

	i = 0;
	while (i < nb)
	{
		if (pipe(pipes + (i * 2)) == -1)
			ft_exit_error();
		i++;
	}
	return (1);
}

int	ft_get_exit_code_return(int status, int excode)
{
	if (excode == -1)
	{
		if (WIFEXITED(status))
			get_minishell()->excode = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			get_minishell()->excode = 128 + WTERMSIG(status);
	}
	else
		get_minishell()->excode = excode;
	return(excode);
}

//main function for pipe handling
t_cmd *handle_pipe(t_cmd *cmd, int pipe_nb)
{
	int pipe_fds[pipe_nb * 2];
	int pids[pipe_nb + 1];
	int i;
	int btin_nb;

	i = 0;
	// create the pipes in array pipefds
	// eg : for 2 consecutive pipes : pipe_fds = [pipeA.0, pipeA.1, pipeB.0, pipeB.1]
	if (!create_pipes(pipe_fds, pipe_nb))
		return (0);
	i = 0;
	while (i < (pipe_nb + 1))
	{
		if ((pids[i] = fork()) == 0) //child process
		{
			dup2_and_close_pipe(pipe_fds, i, pipe_nb);
			if ((btin_nb = is_built_in(cmd->argv[0])) != -1)
				exit(ft_get_exit_code_return(NO_STATUS, ft_exec_builtin(btin_nb, cmd)));
			exec_cmd(cmd);
		}
		else if (pids[i] == -1)
			ft_exit_error();
		cmd = cmd->next;
		i++;
	}
	close_pipe_and_wait(pipe_fds, pipe_nb, pids);
	return (cmd);
}