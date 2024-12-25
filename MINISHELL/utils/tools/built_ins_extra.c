/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_extra.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:57:29 by mmaghri           #+#    #+#             */
/*   Updated: 2024/04/26 12:41:47 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	what_qoutes(char *s)
{
	int	i;

	i = -1;
	if (!s)
		return (0);
	while (s[++i])
	{
		if (s[i] == '\"')
			return (D_QU);
		if (s[i] == '\'')
			return (S_QU);
	}
	return (0);
}

char	*merge_both(char *add, char *string_added)
{
	t_all_not_vars	t;

	t.increment = 0;
	t.index = 0;
	t.aloca = gc(sizeof(char *) * \
	(le_count(string_added) + le_count(add) + 1), 0, 0, 0);
	if (!t.aloca)
		return (NULL);
	while (add[t.index])
	{
		t.aloca[t.index] = add[t.index];
		t.index++;
	}
	if (!string_added)
		return (t.aloca[t.index] = '\0', t.aloca);
	t.aloca[t.index] = ' ';
	t.index++;
	while (string_added[t.increment])
	{
		t.aloca[t.index] = string_added[t.increment];
		t.increment++;
		t.index++;
	}
	t.aloca[t.index] = '\0';
	return (t.aloca);
}
