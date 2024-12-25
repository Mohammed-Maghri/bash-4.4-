/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_b_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 02:55:39 by mmaghri           #+#    #+#             */
/*   Updated: 2024/04/27 10:00:24 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	function_down_cd(t_tree *leaf, char *p)
{
	if (function_search_for("OLDPWD", leaf->tree_h->export) == 1)
		leaf->tree_h->export = delet_from(leaf->tree_h->export, \
		return_place("OLDPWD", leaf->tree_h->export));
	if (count_twode(leaf->content) > 2)
	{
		if (check_function_compare(leaf->content[2], "..") == 0)
			turn_dir(leaf->tree_h->env, leaf, p);
		else if (count_twode(leaf->content) > 2)
		{
			cd_function(merge_both(leaf->content[0], \
			leaf->content[2]), leaf->tree_h->env, leaf);
		}
	}
	else
		cd_function("cd", leaf->tree_h->env, leaf);
}

void	for_pwd(char *p)
{
	char	*res;
	char	*if_null ;

	if_null = getcwd(NULL, 0);
	if (!if_null)
		printf("%s\n", p);
	else
	{
		res = getcwd(NULL, 0);
		printf("%s\n", res);
		free(res);
		free(if_null);
	}
}

int	function_unset(t_tree *leaf)
{
	int	unset_index ;

	unset_index = 1;
	while (leaf->content[unset_index])
	{
		if (!(leaf->content[unset_index][0]) \
		|| on_all(leaf->content[unset_index], 1))
		{
			(leaf->content[unset_index][0] != ' ' && \
			le_count(leaf->content[unset_index]) != 0)
			&&
			(print_error("not a valid identifier", \
			NULL), here_para(0), here_para(1));
		}
		leaf->tree_h->env = \
		for_the_unset(leaf->tree_h->env, \
		delete_opening_quotes(leaf->content[unset_index], \
		what_qoutes(leaf->content[unset_index])));
		if (count_twode(leaf->tree_h->export) > 0)
			leaf->tree_h->export = for_the_unset(leaf->tree_h->export, \
			delete_opening_quotes(leaf->content[unset_index], \
			what_qoutes(leaf->content[unset_index])));
		unset_index++;
	}
	return (0);
}

long long	convert_number(char *string)
{
	t_all_not_vars	t;

	t.flag = 0;
	t.minis = 1;
	t.index = 0;
	t.res = 0;
	while (string[t.index] == '-' || string[t.index] == '+')
	{
		if (string[t.index] == '-')
			t.minis *= -1 ;
		t.index++;
		t.flag++ ;
	}
	while (string[t.index] >= '0' && string[t.index] <= '9')
	{
		t.res = ((t.res * 10) + (string[t.index] - '0'));
		if (t.res > 2147483647 || t.res < -2147483648 || t.index > 19)
			return (print_error("exit Numeric argument required", NULL), \
			gc(0, 2, 0, 255), 255);
		t.index++ ;
	}
	if (t.flag > 2)
		return (print_error("exit Numeric argument required", NULL), \
		gc(0, 2, 0, 255), 255);
	return (t.res *= t.minis, t.res);
}

int	if_else(char string)
{
	if ((string >= '0' && string <= '9'))
		return (0);
	if (string == '-')
		return (0);
	if (string == '+')
		return (0);
	return (-1);
}
