/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisers_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 02:10:45 by mmaghri           #+#    #+#             */
/*   Updated: 2024/04/26 15:02:45 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	my_dup(int file)
{
	int	fd;

	fd = dup(file);
	if (fd == -1)
		return (print_error("error in dup", NULL), \
		gc(0, 2, 0, -1), 0);
	return (fd);
}

int	my_dup2(int file_1, int file_2)
{
	int	fd;

	fd = dup2(file_1, file_2);
	if (fd == -1)
		return (print_error("error in my_dup2", NULL), \
		gc(0, 2, 0, -1), 0);
	return (fd);
}

void	close_pipes(t_tree *leaf)
{
	int	i;

	i = -1;
	while (leaf->tree_h->pipes[++i])
	{
		close(leaf->tree_h->pipes[i][0]);
		close(leaf->tree_h->pipes[i][1]);
	}
}

void	merge_and_sort_helper(char **res, char **arr_1, char **arr_2)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	if (arr_1)
		while (arr_1[++i])
			res[i] = arr_1[i];
	if (arr_2)
		while (arr_2[++j])
			res[i++] = arr_2[j];
	res[i] = NULL;
}

char	**merge_and_sort(char **arr_1, char **arr_2)
{
	char	**res;
	char	*tmp;
	int		i;

	i = 0;
	res = gc(sizeof(char *) * \
	((count_twode(arr_1) + count_twode(arr_2)) + 1), 0, 0, 0);
	merge_and_sort_helper(res, arr_1, arr_2);
	while (res[i])
	{
		if (res[i + 1] && ft_strcmp(res[i], res[i + 1]) > 0)
		{
			tmp = res[i];
			res[i] = res[i + 1];
			res[i + 1] = tmp;
			i = -1;
		}
		i++;
	}
	return (res);
}
