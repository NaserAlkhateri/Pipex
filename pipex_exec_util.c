/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 11:39:43 by student          #+#    #+#             */
/*   Updated: 2024/02/18 13:11:09 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	create_pipe(t_child_params *params)
{
	if (pipe(params->fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

void	start_child(t_pipe_list *temp, t_child_params *params,
	t_pipe_list *head, char **envp)
{
	if (temp == NULL || temp->cmd_path == NULL)
		child_free_exit(head, params, 1);
	if (params->is_first && params->fd_in == -1)
		child_free_exit(head, params, 1);
	if (temp->next)
	{
		dup2(params->fd[1], STDOUT_FILENO);
	}
	else
	{
		if (params->fd_out == -1)
			child_free_exit(head, params, 1);
		dup2(params->fd_out, STDOUT_FILENO);
	}
	child_free_exit(head, params, 0);
	if (execve(temp->cmd_path, temp->cmd_args, envp) == -1)
	{
		ft_putstr_fd("command not found: ", STDERR_FILENO);
		ft_putendl_fd(temp->cmd_args[0], STDERR_FILENO);
		child_free_exit(head, params, 1);
	}
}

void	continue_parent(t_child_params *params)
{
	close(params->fd[1]);
	dup2(params->fd[0], STDIN_FILENO);
	params->is_first = 0;
	close(params->fd[0]);
}

void	close_fds(int fd_in, int fd_out)
{
	close(fd_in);
	close(fd_out);
}

void	pipe_exec(t_pipe_list *head, int fd_in, int fd_out, char **envp)
{
	t_child_params	params;
	pid_t			pid;
	t_pipe_list		*temp;
	int				status;

	temp = head;
	params.fd_in = fd_in;
	params.fd_out = fd_out;
	params.is_first = 1;
	while (temp != NULL)
	{
		if (temp->next != NULL)
			create_pipe(&params);
		pid = fork();
		if (pid == -1)
			return ((perror("fork"), exit(EXIT_FAILURE)));
		if (pid == 0)
			start_child(temp, &params, head, envp);
		else
			continue_parent(&params);
		temp = temp->next;
	}
	waitpid(pid, &status, 0);
	return (ft_pipeclear(&head), close_fds(fd_in, fd_out),
		exit(WEXITSTATUS(status)));
}
