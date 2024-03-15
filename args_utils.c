/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 12:44:27 by student          #+#    #+#             */
/*   Updated: 2024/02/18 14:35:16 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
	{
		free(args[i]);
		i++;
	}
	free(args);
}

char	*ft_get_cmd_path_from_path(char *cmd, char **path)
{
	int		i;
	char	*cmd_path;

	i = 0;
	while (path[i])
	{
		cmd_path = ft_strjoin(path[i], cmd);
		if (!cmd_path)
			return (NULL);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (ft_strdup(cmd));
}

char	**ft_strjoin_arr(char **arr, char *str)
{
	int		i;
	char	**new_arr;
	char	*temp;

	i = 0;
	while (arr[i])
		i++;
	new_arr = malloc(sizeof(char *) * (i + 1));
	if (!new_arr)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		temp = arr[i];
		new_arr[i] = ft_strjoin(arr[i], str);
		free(temp);
		i++;
	}
	new_arr[i] = NULL;
	i = 0;
	free(arr);
	return (new_arr);
}

char	*ft_get_cmd_path(char *cmd, char **envp)
{
	int		i;
	char	**path;
	char	*cmd_path;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_split(envp[i] + 5, ':');
			if (!path)
				return (NULL);
			path = ft_strjoin_arr(path, "/");
			if (!path)
				return (NULL);
			cmd_path = ft_get_cmd_path_from_path(cmd, path);
			free_args(path);
			return (cmd_path);
		}
		i++;
	}
	return (NULL);
}

void	child_free_exit(t_pipe_list *head, t_child_params *params, int isError)
{
	if (isError == 1)
		ft_pipeclear(&head);
	if (params->fd[0] != -1)
		close(params->fd[0]);
	if (params->fd[1] != -1)
		close(params->fd[1]);
	if (params->fd_in != -1)
		close(params->fd_in);
	if (params->fd_out != -1)
		close(params->fd_out);
	if (isError == 1)
		exit(EXIT_FAILURE);
}
