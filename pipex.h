/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: student <student@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:45:09 by student          #+#    #+#             */
/*   Updated: 2024/02/18 13:15:58 by student         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h> 
# include <sys/wait.h>
# include <sys/types.h>

char		**ft_split(char const *s, char c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlen(const char *s);
void		free_args(char **args);
typedef struct s_cmd_list
{
	char				**cmd_args;
	char				*cmd_path;
	struct s_cmd_list	*next;
}	t_pipe_list;

typedef struct s_child_params
{
	int	fd[2];
	int	fd_in;
	int	fd_out;
	int	is_first;
}	t_child_params;

t_pipe_list	*init_pipe_list(int argc, char **argv, char **envp);
void		pipe_exec(t_pipe_list *head, int fd_in, int fd_out, char **envp);
void		create_pipe(t_child_params *params);
void		start_child(t_pipe_list *temp, t_child_params *params,
				t_pipe_list *head, char **envp);
void		continue_parent(t_child_params *params);
void		close_fds(int fd_in, int fd_out);
void		ft_pipeclear(t_pipe_list **lst);
t_pipe_list	*ft_lstnew(char *cmd, char **envp);
void		ft_lstadd_back(t_pipe_list **lst, t_pipe_list *new);
char		*ft_strdup(const char *s1);
char		*ft_get_cmd_path(char *cmd, char **envp);
char		**ft_strjoin_arr(char **arr, char *str);
char		*ft_get_cmd_path_from_path(char *cmd, char **path);
void		free_args(char **args);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		child_free_exit(t_pipe_list *head,
				t_child_params *params, int isError);
#endif