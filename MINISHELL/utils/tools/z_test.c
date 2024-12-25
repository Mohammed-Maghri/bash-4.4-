/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_test.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 03:00:07 by mmaghri           #+#    #+#             */
/*   Updated: 2024/04/26 12:42:19 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	here_para(int pass)
{
	static int	check;

	if (pass == 1)
		check = 1;
	if (!pass)
		check = 0;
	else
		return (check);
	return (check);
}

char	**return_it_for_sure(int first_pos, DIR	*curenet_dir)
{
	t_all_not_vars	t;
	struct dirent	*this;

	this = readdir(curenet_dir);
	t.allocation = gc((sizeof(struct dirent) + 1), 0, 0, 0);
	t.increment = 0;
	while (this)
	{
		if (first_pos == 0)
		{
			if (this->d_name[0] != '.')
			{
				t.allocation[t.increment] = return_line(this->d_name);
				t.increment++ ;
			}
		}
		else
		{
			t.allocation[t.increment] = return_line(this->d_name);
			t.increment++ ;
		}
		this = readdir(curenet_dir);
	}
	t.allocation[t.increment] = NULL;
	return (t.allocation);
}

int	count_how_many(char *string, char what)
{
	int		index;
	int		flag;

	flag = 0;
	index = 0;
	while (string[index])
	{
		if (string[index] == what)
			flag++ ;
		index++ ;
	}
	return (flag);
}

int	only_pass(t_tree *leaf)
{
	t_path		*save;
	static char	*p;

	save = gc(sizeof(t_path) * 1, 0, 0, 0);
	save->save = getcwd(NULL, 0);
	if (save && save->save && le_count(save->save) > 2)
	{
		p = return_line(save->save);
		leaf->tree_h->extra_save = return_line(p);
	}
	(save->save) && (free(save->save), 0);
	if (!here_comp(leaf->content[0], "export", 7))
	{
		if (!export_check(leaf) && count_twode(leaf->content) == 1)
			return (function_export(leaf, 0), 1);
		return (for_the_export(leaf->content, leaf), 1);
	}
	else if (check_function_compare(leaf->content[0], "cd") == 0)
		return (function_down_cd(leaf, p), 1);
	else if (!here_comp(leaf->content[0], "pwd", 4))
		return (for_pwd(p), 1);
	else if (!here_comp(leaf->content[0], "echo", 5))
		return (function_for_echo(leaf), 1);
	return (0);
}

void	function_export(t_tree *leaf, int up)
{
	char	**res ;

	res = merge_and_sort(leaf->tree_h->env, \
	leaf->tree_h->export);
	if (count_twode(res) >= 1)
	{
		if (res[up])
		{
			while (res[up])
			{
				if (here_comp(copy_till_charac(res[up], \
				'='), "_", 1))
				{
					if (search_in_for(res[up], '=') == 1)
						printf("declare -x %s\"\n", add_to_string(res[up], \
						"\"", turn_position(res[up], '='), \
						turn_position(res[up], '=') + 1));
					else
						printf("declare -x %s\n", res[up]);
				}
				up++ ;
			}
		}
	}
}
