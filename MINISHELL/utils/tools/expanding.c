/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:45:36 by mlouazir          #+#    #+#             */
/*   Updated: 2024/04/25 21:18:17 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_alnumex(char c)
{
	return (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') \
	|| (('0' <= c && c <= '9')) || c == '_');
}

int	is_digit(char c)
{
	return (('0' <= c && c <= '9'));
}

void	check_ambigious(char *input, int *am)
{
	char	**tmp;
	int		a;

	a = -1;
	tmp = tab_split(input);
	while (tmp[++a])
		;
	if (a > 1 && am)
		*am = 1;
	else if (am)
		*am = 0;
}

char	*modify_string(char *to_modify, char **env, int *i, int *am)
{
	char	*tmp;
	int		b;
	int		new_size;

	b = *i;
	new_size = 0;
	tmp = for_herdoc(dollar_exp(to_modify, &b, *i), env);
	if (to_modify[b] == '?')
		tmp = add_to_string(to_modify, ft_itoa(exit_status(0, \
		1)), *i - 1, b + 1);
	else if (!tmp)
	{
		tmp = cut_string(to_modify, *i - 1, b + 1);
		(*i > 0) && (*i -= 1, 0);
	}
	else if (tmp)
	{
		new_size = *i;
		new_size += ft_strlen(tmp);
		check_ambigious(tmp, am);
		tmp = add_to_string(to_modify, tmp, *i - 1, b + 1);
		*i = new_size;
	}
	return (tmp);
}

char	*expand_factory(char *to_expand, char **env, int *am, int pass)
{
	int		i;
	int		a;

	i = 0;
	a = 0;
	if (to_expand[0] == '\'' && !pass)
		a = 1;
	while (to_expand[i])
	{
		if (to_expand[i] == '$' && to_expand[i + 1] && \
		(is_alnumex(to_expand[i + 1]) || to_expand[i + 1] == '?' \
		|| to_expand[i + 1] == '*') && !a)
			to_expand = modify_string(to_expand, env, &i, am);
		else
			i++;
	}
	return (to_expand);
}
