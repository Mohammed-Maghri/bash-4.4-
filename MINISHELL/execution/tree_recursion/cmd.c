/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaghri <mmaghri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:29:45 by mlouazir          #+#    #+#             */
/*   Updated: 2024/04/27 16:11:52 by mmaghri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	on_new(void)
{
	rl_replace_line("", 0);
	write(1, "➜ miniBash : exit\n", 21);
}

void	set_bq(char **res, t_tree *leaf, int index, int size)
{
	int	*new_bq;
	int	length;
	int	i;

	i = 0;
	length = count_twode(res);
	new_bq = gc(sizeof(int) * (length + size), 0, 1, 0);
	while (i < length)
	{
		new_bq[i] = leaf->b_q[i];
		i++;
	}
	while (i < length + size)
	{
		new_bq[i] = 0;
		if (leaf->content[index][0] == '\'' || leaf->content[index][0] == '\"')
			new_bq[i] = 1;
		i++;
	}
	leaf->b_q = new_bq;
}

int	cmd(t_tree *leaf)
{
	char		*tmp;
	struct stat	buf;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	leaf->content = generate_cmd(leaf->content);
	if (!(count_twode(leaf->content) || leaf->content[0]))
		return (close_fds(leaf), gc(0, 2, 0, 0), 0);
	tmp = check_access(leaf, leaf->tree_h, leaf->content[0]);
	if (stat(tmp, &buf))
		return (print_error("No such file or directory", tmp), \
		gc(0, 2, 0, 127), 1);
	if (access(tmp, X_OK))
		return (print_error("Permission denied", tmp), \
		gc(0, 2, 0, 126), 1);
	close_fds(leaf);
	if (execve(tmp, leaf->content, leaf->tree_h->env) == -1)
		return (print_error("command not found", tmp), \
		gc(0, 2, 0, 127), 1);
	return (0);
}
