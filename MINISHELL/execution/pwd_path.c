/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:23:35 by mmaghri           #+#    #+#             */
/*   Updated: 2024/04/03 18:09:52 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**function_this_one(char *much_start, char \
*much_end, int choose, int first_pos)
{
	t_all_not_vars	t;

	t.increment = 0;
	t.curenet_dir = opendir(".");
	t.allocation = return_it_for_sure(first_pos, t.curenet_dir);
	if (choose == 10)
		return (closedir(t.curenet_dir), t.allocation);
	if (choose == 2)
		t.allocation = check_in_every(t.allocation, much_start);
	else if (choose == -1)
		t.allocation = check_both(t.allocation, much_end);
	else if (choose == 0)
		t.allocation = keep_only_what_to_start_find(t.allocation, much_start);
	else if (choose == 1)
		t.allocation = check_sides(t.allocation, much_start, much_end);
	return (closedir(t.curenet_dir), t.allocation);
}

int	return_int_pwd_path(char **env, char *new_env)
{
	t_all_vars	for_pwd;
	char		*pwd ;

	pwd = "PWD";
	for_pwd.index = 0;
	for_pwd.increment = 0;
	for_pwd.flag = 0;
	adress_unset(&for_pwd.flag, &for_pwd.increment, &for_pwd.index, -1);
	while (env[for_pwd.index])
	{
		while (for_pwd.increment < 3)
		{
			if (env[for_pwd.index][for_pwd.increment] == pwd[for_pwd.increment])
				for_pwd.flag++ ;
			for_pwd.increment++ ;
		}
		if (for_pwd.flag == 3)
		{
			new_env = getcwd(NULL, 0);
			env[for_pwd.index] = merge_to("PWD=", new_env);
			return (free(new_env), 0);
		}
		adress_unset(&for_pwd.flag, &for_pwd.increment, &for_pwd.index, 0);
	}
	return (0);
}

void	return_extra(t_tree *leaf, char *new_env)
{
	t_all_vars	for_pwd;
	char		*pwd;

	pwd = "PWD=";
	adress_unset(&for_pwd.flag, &for_pwd.increment, &for_pwd.index, -1);
	while (leaf->tree_h->env[for_pwd.index])
	{
		while (for_pwd.increment < 3)
		{
			if (leaf->tree_h->env[for_pwd.index][for_pwd.increment] \
			== pwd[for_pwd.increment])
				for_pwd.flag++ ;
			for_pwd.increment++ ;
		}
		if (for_pwd.flag == 3)
		{
			new_env = getcwd(NULL, 0);
			leaf->tree_h->env = add_it_to_env_index(leaf->tree_h->env, \
			merge_to("PWD=", new_env), for_pwd.index);
			free(new_env);
			return ;
		}
		adress_unset(&for_pwd.flag, &for_pwd.increment, &for_pwd.index, 0);
	}
}
