/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rediractions_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 01:37:34 by mlouazir          #+#    #+#             */
/*   Updated: 2024/04/26 12:39:46 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ambiguous_check(char *tmp, char **env)
{
	char	*tmp_2;
	int		a;

	a = 0;
	tmp_2 = expand_factory(tmp, env, &a, 0);
	if (a && tmp[0] != '\"')
		return (print_error("ambiguous redirect", tmp), \
		exit_status(1, 0), NULL);
	return (tmp_2);
}

void	is_quotes_with_star(char *string, int *var)
{
	t_pt	helper;
	int		i;

	i = -1;
	helper.s_bool = 0;
	if (string[++i] == '\'' || string[i] == '\"')
		helper.s_bool = 1;
	while (string[++i])
		if (string[i] == '*' && helper.s_bool)
			*var = 1;
}

char	*file_decision(char	*file, int *var)
{
	char	*tmp;

	if (*var != 0)
		return (file);
	tmp = NULL;
	if (!all_sapce(file))
		return (print_error("ambiguous redirect", NULL), NULL);
	(*var == 0 && search_in_for(file, '*')) && (tmp = \
	function_check_wild_card_builts(file, var), 0);
	if (!tmp && *var == 2)
		return (NULL);
	if (!tmp && *var == 1)
		return (ft_strtrim(file, " \t"));
	return (file);
}

char	*file_check_helper(char *tmp, int var2)
{
	if (var2)
		tmp = delete_opening_quotes(tmp, what_qoutes(tmp));
	else if (!var2 && tmp[0] && all_sapce(tmp))
		tmp = ft_strtrim(tmp, " \t");
	return (tmp);
}

char	*file_check(t_tree *leaf)
{
	char	*file;
	char	*tmp;
	int		j;
	int		var;
	int		var2;

	j = 0;
	var = 0;
	tmp = expand_factory(leaf->content[j], leaf->tree_h->env, NULL, 0);
	if (leaf->content[j][0] == '$' && ft_strlen(leaf->content[j]) > 1 && \
	!(leaf->content[j + 1]) && !tmp[0])
		return (print_error("ambiguous redirect", leaf->content[j]), NULL);
	file = gc(1, 0, 0, 0);
	while (leaf->content[j])
	{
		(1) && (var2 = 0, tmp = leaf->content[j++], 0);
		(tmp[0] == '\"' || tmp[0] == '\'') && (var2 = 1, 0);
		is_quotes_with_star(tmp, &var);
		tmp = ambiguous_check(tmp, leaf->tree_h->env);
		if (!tmp)
			return (NULL);
		tmp = file_check_helper(tmp, var2);
		file = ft_strjoin(file, tmp);
	}
	return (file_decision(file, &var));
}
