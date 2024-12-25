/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:16:56 by mmaghri           #+#    #+#             */
/*   Updated: 2024/04/26 16:16:57 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*return_malloc(char *string)
{
	char	*res;
	int		i;

	i = ft_strlen(string);
	res = malloc(i + 1);
	if (!res)
		return (gc(0, 2, 0, 1), NULL);
	i = -1;
	while (string[++i])
		res[i] = string[i];
	return (res[i] = 0, res);
}

int	function_for_exit(char *string)
{
	if ((check_string("exit", string)) == 0)
	{
		printf("exit");
		return (-1);
	}
	return (0);
}

char	*dollar_exp(char *to_modify, int *b, int i)
{
	char	*tmp;

	if (!is_digit(to_modify[*b + 1]) && to_modify[*b + 1] != '?' \
	&& to_modify[*b + 1] != '*')
		while (to_modify[*b + 1] && is_alnumex(to_modify[*b + 1]))
			*b += 1;
	else
		*b += 1;
	tmp = ft_substr(to_modify, i, *b - i + 1);
	return (tmp);
}

char	*delete_opening_quotes_only(char *string)
{
	char	*res;
	char	*c;
	int		i;

	c = gc(2, 0, 0, 0);
	if (!string[0])
		return (c[0] = 0, c);
	res = string;
	i = 0;
	res = cut_string(res, i - 1, i + 1);
	i = ft_strlen(res) - 1;
	res = cut_string(res, i - 1, i + 1);
	return (res);
}

int	turn_dir(char **env, t_tree *leaf, char *p)
{
	t_all_not_vars	t;

	((!leaf->saved)) && (leaf->saved = return_line(p), 0);
	t.res_type = gc(sizeof(char *) * (count_twode(env) + 1), 0, 0, 0);
	t.for_current = getcwd(NULL, 0);
	if (!t.for_current)
	{
		t.saftey = function_helper_two(leaf);
		if (t.saftey == -1)
			return (free(t.for_current), \
			check_if_to_turn("cd", leaf->content, leaf), -1);
		else
		{
			check_if_to_turn("cd", leaf->content, leaf);
			free(t.for_current);
		}
	}
	if (t.for_current)
	{
		add_function_helper(t.for_current, leaf);
		chdir(flag_last(t.for_current, '/'));
	}
	return_extra(leaf, "Mohamed-Maghri");
	return (free(t.for_current), 0);
}
