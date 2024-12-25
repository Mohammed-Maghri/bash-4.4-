/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_add_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 07:08:42 by mmaghri           #+#    #+#             */
/*   Updated: 2024/04/26 12:35:37 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_com(char *for_cd, char **env, t_tree *leaf)
{
	if (for_cd[0] == '/' && (for_cd[1] == '\0' \
	|| for_cd[1] == ' ' || for_cd[1] == '\t'))
	{
		add_function_helper("/", leaf);
		chdir("/");
		return_int_pwd_path(env, "/");
		return (0);
	}
	if (for_cd[0] == '/' && (for_cd[1] != '\0' \
	|| for_cd[1] != ' ' || for_cd[1] != '\t'))
	{
		add_function_helper(for_cd, leaf);
		chdir(for_cd);
		if (chdir(for_cd) == -1)
		{
			printf("");
			print_error("No such file or directory * ", for_cd);
			(here_para(0), here_para(1));
			return (-1);
		}
		return_int_pwd_path(env, for_cd);
		return (0);
	}
	return (-1);
}

int	com(char *see_path, char *get_path, char *path, t_tree *leaf)
{
	t_all_vars	for_func;

	(void)see_path ;
	for_func.index = 0;
	if (get_path)
	{
		for_func.for_cd = remove_cd(path, "cd");
		if (for_func.for_cd[0] == '/')
			return (check_com(for_func.for_cd, leaf->tree_h->env, leaf), 0);
		for_func.path_to = merge_path(get_path, for_func.for_cd);
		add_function_helper((for_func.path_to), leaf);
		for_func.res_type = chdir(for_func.path_to);
		if (for_func.res_type == -1)
		{
			printf("");
			print_error("No such file or directory * ", path);
			(here_para(0), here_para(1));
			return (-1);
		}
		return_int_pwd_path(leaf->tree_h->env, &see_path[for_func.index]);
	}
	return (0);
}

int	cd_function(char *path, char **env, t_tree *leaf)
{
	t_all_vars	f;

	f.index = 0;
	f.hold = check_cd(path);
	f.flag = check_if_to_turn(path, env, leaf);
	if (f.flag == -1 || f.hold == -1)
		return (0);
	if (le_count(path) > 2)
	{
		f.see_path = gc(sizeof(char *) * (le_count(path) + 1), 0, 0, 0);
		f.get_path = getcwd(NULL, 0);
		f.know = com(f.see_path, f.get_path, path, leaf);
		if (f.know == -1)
			return (free(f.get_path), 0);
		if (!f.get_path)
		{
			print_error("No such file or directory", path);
			return (here_para(0), here_para(1), free(f.get_path), 0);
		}
		if (check_res_type(f.res_type, path, f.for_cd) == -1)
			return (free(f.get_path), 0);
	}
	(f.check_flag == -1) && (print_error("cd: no \
	such file or directory:", NULL), here_para(0), here_para(1), 0);
	return (free(f.get_path), 0);
}

char	*return_env(char *string)
{
	int		index ;
	char	*allocation ;

	index = 0;
	allocation = gc(sizeof(char *) * (le_count(string) + 1), 0, 0, 0);
	while (string[index] && string[index] == ' ' && le_count(string) > 2)
		index++ ;
	while (string[index])
	{
		allocation[index] = string[index];
		index++ ;
	}
	allocation[index] = '\0';
	return (allocation);
}

char	**move_env(char **env)
{
	t_path	t;

	t.increment = 0;
	t.flag = 0;
	t.place = -1;
	t.index = 0;
	t.allocation = gc(sizeof(char **) * (count_twode(env) + 1), 0, 0, 0);
	if (return_place("OLDPWD=", env) > -1)
	{
		t.flag = -1 ;
		t.place = return_place("OLDPWD=", env);
	}
	while (env[t.index])
	{
		if (t.flag == 0)
			t.allocation[t.increment++] = return_env(env[t.index]);
		else
		{
			if (t.index != t.place)
				t.allocation[t.increment++] = return_env(env[t.index]);
		}
		t.index++ ;
	}
	t.allocation[t.increment] = NULL ;
	return (t.allocation);
}
