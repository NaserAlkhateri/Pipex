/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_lst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 12:37:12 by student          #+#    #+#             */
/*   Updated: 2024/02/18 14:54:15 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_pipeclear(t_pipe_list **lst)
{
	t_pipe_list	*temp;

	if (*lst)
	{
		while (*lst != NULL)
		{
			temp = *lst;
			*lst = (*lst)->next;
			free_args(temp->cmd_args);
			free(temp->cmd_path);
			free(temp);
		}
		*lst = NULL;
	}
}

t_pipe_list	*ft_lstnew(char *cmd, char **envp)
{
	t_pipe_list	*new;
	char		**cmd_args;
	char		*cmd_path;

	new = (t_pipe_list *)malloc(sizeof(t_pipe_list));
	if (!new)
		return (NULL);
	cmd_args = ft_split(cmd, ' ');
	if (!cmd_args)
	{
		free(new);
		return (NULL);
	}
	cmd_path = ft_get_cmd_path(cmd_args[0], envp);
	if (!cmd_path)
	{
		ft_putstr_fd("command not found: ", STDERR_FILENO);
		ft_putendl_fd(cmd_args[0], STDERR_FILENO);
		free_args(cmd_args);
		return (free(new), NULL);
	}
	new->cmd_args = cmd_args;
	new->cmd_path = cmd_path;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back(t_pipe_list **lst, t_pipe_list *new)
{
	t_pipe_list	*temp;

	if (*lst)
	{
		temp = *lst;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
	else
		*lst = new;
}

void	ft_putendl_fd(char *s, int fd)
{
	if (s)
	{
		ft_putstr_fd(s, fd);
		write(fd, "\n", 1);
	}
}

t_pipe_list	*init_pipe_list(int argc, char **argv, char **envp)
{
	t_pipe_list	*pipe_lst;
	int			i;
	t_pipe_list	*temp;

	i = 0;
	pipe_lst = NULL;
	while (i < argc - 3)
	{
		temp = ft_lstnew(argv[i + 2], envp);
		if (!temp)
		{
			ft_pipeclear(&pipe_lst);
			return (NULL);
		}
		ft_lstadd_back(&pipe_lst, temp);
		temp = NULL;
		i++;
	}
	return (pipe_lst);
}
