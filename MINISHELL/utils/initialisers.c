/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 12:21:39 by mlouazir          #+#    #+#             */
/*   Updated: 2024/04/26 15:07:57 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	my_fork(void)
{
	int	id;

	id = fork();
	if (id == -1)
		return (print_error("Resource temporarily unavailable", "fork"), \
		gc(0, 2, 0, -1), 1);
	return (id);
}

int	*my_pipe(void)
{
	int	*p;

	p = gc(sizeof(int) * 2, 0, 1, 0);
	if (pipe(p) == -1)
		return (print_error("Faile in pipe", NULL), \
		gc(0, 2, 0, -1), NULL);
	gc(p[0], 3, 1, 0);
	gc(p[1], 3, 1, 0);
	return (p);
}

int	*add_pipes(t_th *tree_h)
{
	int	**arr;
	int	i;

	i = -1;
	arr = gc(sizeof(int *) * (tree_h->pipe_i + 1), 0, 1, 0);
	while (++i < tree_h->pipe_i - 1)
		arr[i] = tree_h->pipes[i];
	arr[i] = my_pipe();
	arr[++i] = NULL;
	tree_h->pipes = arr;
	return (arr[i - 1]);
}

int	open_in(t_tree *leaf)
{
	char	*file_name;
	int		fd;

	file_name = file_check(leaf);
	if (!file_name)
		return (exit_status(1, 0), -5);
	fd = open(file_name, O_RDONLY);
	if (fd == -1 && !access(file_name, F_OK) \
	&& access(file_name, R_OK) == -1)
		return (print_error("Permission denied", file_name), \
		exit_status(1, 0), -5);
	else if (fd == -1)
		return (print_error("No such file or directory", file_name), \
		exit_status(1, 0), -5);
	return (gc(fd, 3, 1, 0), add_fd(leaf, fd), fd);
}

int	open_out(t_tree *leaf, int token_type)
{
	char	*file_name;
	int		fd;
	int		var;

	file_name = file_check(leaf);
	if (!file_name)
		return (exit_status(1, 0), -5);
	var = 0x0400;
	if (token_type == REDIR_APPEND)
		var = 0x0008;
	fd = open(file_name, O_WRONLY | O_CREAT | var, 0777);
	if (fd == -1 && !access(file_name, F_OK) \
	&& access(file_name, W_OK) == -1)
		return (print_error("Permission denied", file_name), \
		exit_status(1, 0), -5);
	if (fd == -1)
		return (print_error("No such file or directory", file_name), \
		exit_status(1, 0), -5);
	return (gc(fd, 3, 1, 0), add_fd(leaf, fd), fd);
}
