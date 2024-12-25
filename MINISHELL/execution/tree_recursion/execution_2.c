/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaghri <mmaghri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 22:31:16 by mlouazir          #+#    #+#             */
/*   Updated: 2024/04/26 21:06:03 by mmaghri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**set_res(char **res, char **tmp_3, int size)
{
	char	**new_res;
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (res[++i])
		;
	new_res = gc(sizeof(char *) * (i + size + 2), 0, 0, 0);
	i = 0;
	while (res[i])
	{
		new_res[i] = res[i];
		i++;
	}
	while (tmp_3[++j])
		new_res[i++] = tmp_3[j];
	new_res[i] = NULL;
	return (new_res);
}

char	**add_normal(char **res, char *tmp, t_tree *leaf, int index)
{
	char	**new_res;
	int		*new_bq;
	int		i;
	int		a;

	i = -1;
	a = -1;
	if (!tmp[0])
		return (res);
	while (res[++i])
		;
	new_res = gc(sizeof(char *) * (i + 2), 0, 0, 0);
	new_bq = gc(sizeof(int) * (i + 1), 0, 1, 0);
	while (++a < i)
		new_bq[a] = leaf->b_q[a];
	new_bq[a] = 0;
	if (leaf->content[index][0] == '\'' || leaf->content[index][0] == '\"')
		new_bq[a] = 1;
	i = -1;
	while (res[++i])
		new_res[i] = res[i];
	new_res[i++] = tmp;
	new_res[i] = NULL;
	return (leaf->b_q = new_bq, new_res);
}

char	**add_spilted(char **res, char *tmp, t_tree *leaf, int index)
{
	char	**tmp_2;
	char	**tmp_3;
	int		i;
	int		j;
	int		size;

	(1) && (i = -1, j = -1, 0);
	tmp_2 = tab_split(skip_empty_blocks(tmp));
	while (tmp_2[++i])
		;
	size = i + (i - 1);
	if (tmp[0] == 32 || tmp[0] == 9)
		size++;
	tmp_3 = gc(sizeof(char *) * (size + 1), 0, 0, 0);
	i = -1;
	if (tmp[0] == 32 || tmp[0] == 9)
		tmp_3[++j] = ft_substr(" ", 0, 1);
	while (tmp_2[++i])
	{
		tmp_3[++j] = tmp_2[i];
		tmp_3[++j] = ft_substr(" ", 0, 1);
	}
	tmp_3[j] = NULL;
	return (set_bq(res, leaf, index, size), set_res(res, tmp_3, size));
}

char	**build_cmd(t_tree *leaf)
{
	char	**res;
	char	*tmp;
	int		i;
	int		a;

	i = -1;
	res = gc(sizeof(char *), 0, 0, 0);
	res[0] = 0;
	while (!here_comp(leaf->content[count_twode(leaf->content) - 1], " ", 1) \
	|| !here_comp(leaf->content[count_twode(leaf->content) - 1], "\t", 1))
		leaf->content[count_twode(leaf->content) - 1] = NULL;
	while (leaf->content[++i])
	{
		a = 0;
		tmp = expand_factory(leaf->content[i], leaf->tree_h->env, NULL, 0);
		if (!here_comp("export", tmp, 7))
			a = 1;
		if ((tmp[0] != '\'' && tmp[0] != '\"') && here_comp(tmp, " ", 1) \
		&& here_comp(tmp, "\t", 1) && !is_space(tmp) && !a)
			res = add_spilted(res, tmp, leaf, i);
		else
			res = add_normal(res, tmp, leaf, i);
	}
	return (leaf->content = res, function_check_wild_card_cmds(leaf), \
	leaf->content);
}

int	exec_word(t_tree *leaf)
{
	char			**tmp_2;
	int				pid;
	struct termios	save;

	tcgetattr(STDIN_FILENO, &save);
	leaf->content = build_cmd(leaf);
	tmp_2 = copy_twode(leaf->content);
	if (!is_built(leaf))
	{
		leaf->content = tmp_2;
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_DFL);
		pid = my_fork();
		if (!pid)
			cmd(leaf);
		close_pipes(leaf);
		wait(&leaf->exit_status);
		if (!exit_status(0, 4))
			exit_status(WEXITSTATUS(leaf->exit_status), 0);
		else
			tcsetattr(STDIN_FILENO, TCSAFLUSH, &save);
	}
	signal(SIGINT, signals_handler);
	signal(SIGQUIT, signals_handler);
	return (0);
}
