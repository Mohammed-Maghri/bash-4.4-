/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 11:13:05 by mlouazir          #+#    #+#             */
/*   Updated: 2024/04/26 14:08:08 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_error(char *error, char *arg)
{
	int	i;

	i = -1;
	if (arg)
	{
		while (arg[++i])
			write(2, &arg[i], 1);
		write(2, ": ", 2);
	}
	i = -1;
	while (error[++i])
		write(2, &error[i], 1);
	write(2, "\n", 1);
}

void	add_fd(t_tree *leaf, int fd)
{
	int	*new_array;
	int	i;

	i = -1;
	while (leaf->tree_h->fds[++i])
		;
	new_array = gc(sizeof(int) * (i + 2), 0, 1, 0);
	i = -1;
	while (leaf->tree_h->fds[++i])
		new_array[i] = leaf->tree_h->fds[i];
	new_array[i] = fd;
	leaf->tree_h->fds = new_array;
}
