/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 19:06:00 by student          #+#    #+#             */
/*   Updated: 2024/02/18 14:08:14 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipe_list	*pipe_lst;
	int			fd_in;
	int			fd_out;

	if (argc != 5)
		return (ft_putendl_fd("Error: invalid number of arguments", 2), 1);
	fd_in = open(argv[1], O_RDONLY);
	if (fd_in == -1)
		perror(argv[1]);
	fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
		perror(argv[argc - 1]);
	pipe_lst = init_pipe_list(argc, argv, envp);
	if (!pipe_lst)
	{
		close_fds(fd_in, fd_out);
		return (0);
	}
	dup2(fd_in, STDIN_FILENO);
	pipe_exec(pipe_lst, fd_in, fd_out, envp);
	close_fds(fd_in, fd_out);
	return (0);
}
