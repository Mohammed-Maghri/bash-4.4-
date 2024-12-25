/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_card.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 23:36:03 by mlouazir          #+#    #+#             */
/*   Updated: 2024/04/26 14:23:42 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*join_array_helper(t_tree *leaf, int *wild_expand, t_pt *bool)
{
	char	*res;

	(!wild_case(leaf->content[bool->d_bool])) \
	&& (wild_expand[bool->e_bool] = 1, 0);
	res = leaf->content[bool->d_bool];
	if (leaf->b_q[bool->d_bool])
		res = delete_opening_quotes_only(leaf->content[bool->d_bool]);
	if (!all_sapce(res))
		res = ft_strjoin(res, res);
	bool->d_bool += 1;
	return (res);
}

char	**join_the_array(t_tree *leaf, int *wild_expand)
{
	t_pt	bool;
	char	*tmp;
	char	**new;

	check_if_ended(&bool, 0);
	tmp = gc(1, 0, 0, 0);
	new = copy_twode(leaf->content);
	if_export(leaf->content, &bool);
	while (leaf->content[bool.d_bool])
	{
		if (here_comp(leaf->content[bool.d_bool], " ", 1) \
		&& here_comp(leaf->content[bool.d_bool], "\t", 1))
		{
			tmp[0] = 0;
			while (leaf->content[bool.d_bool] && (here_comp(leaf->content[bool. \
			d_bool], " ", 1) && here_comp(leaf->content[bool.d_bool], "\t", 1)))
				tmp = ft_strjoin(tmp, join_array_helper(leaf, \
				wild_expand, &bool));
			update_new(new, leaf->content, tmp, &bool);
		}
		else
			bool.d_bool++;
	}
	return (new[bool.e_bool] = NULL, leaf->content = new, new);
}

int	*delete_all_quotes(t_tree *leaf, int *wild_expand)
{
	int		i;
	int		l;

	i = -1;
	l = count_twode(leaf->content);
	wild_expand = gc((l) * sizeof(int), 0, 1, 0);
	while (++i < l)
		wild_expand[i] = 0;
	join_the_array(leaf, wild_expand);
	return (wild_expand);
}

void	function_check_wild_card_cmds(t_tree *leaf)
{
	char	**tmp;
	int		index;
	int		*wild_expand;

	if (!count_twode(leaf->content))
		return ;
	index = 0;
	wild_expand = NULL;
	wild_expand = delete_all_quotes(leaf, wild_expand);
	while (leaf->content[index])
	{
		if (search_in_for(leaf->content[index], '*') && !wild_expand[index])
		{
			tmp = wild_helper(cut_star(leaf->content[index]));
			if (count_twode(tmp))
			{
				wild_expand = re_size_array(wild_expand, \
				count_twode(tmp), count_twode(leaf->content), index);
				leaf->content = add_to_content(tmp, leaf->content, index);
				index += count_twode(tmp) - 1;
			}
		}
		index++;
	}
}

char	*function_check_wild_card_builts(char *string, int *var)
{
	char	**tmp;
	char	*res;
	int		i;

	i = -1;
	res = NULL;
	tmp = NULL;
	tmp = wild_helper(cut_star(string));
	if (count_twode(tmp))
	{
		res = function_array_line(tmp);
		tmp = tab_split(res);
		while (tmp[++i])
			;
	}
	if (i > 1)
		return (print_error("ambiguous redirect", string), \
		exit_status(1, 0), *var = 2, NULL);
	return (*var = 1, res);
}
