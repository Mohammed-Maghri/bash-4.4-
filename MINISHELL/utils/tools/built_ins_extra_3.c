/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_extra_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:05:16 by mmaghri           #+#    #+#             */
/*   Updated: 2024/04/26 12:41:32 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*return_from_here(char *string, char this)
{
	t_all_not_vars	t;

	t.index = 0;
	t.increment = 0;
	t.aloca = gc(sizeof(char *) * \
	(le_count(string) + 1), 0, 0, 0);
	if (!t.aloca)
		return (NULL);
	while (string[t.index])
	{
		if (string[t.index] == this)
		{
			t.index++ ;
			while (string[t.index])
			{
				t.aloca[t.increment] = string[t.index];
				t.index++ ;
				t.increment++ ;
			}
			t.aloca[t.increment] = '\0';
			return (t.aloca);
		}
		t.index++ ;
	}
	return (NULL);
}

char	*for_herdoc(char *string, char **env)
{
	t_all_not_vars	t;

	if (search_in_for(string, '$') == 0)
		return (NULL);
	t.var = return_from_here(string, '$');
	t.index = 0;
	t.increment = 0;
	t.flag = 0;
	while (env[t.index])
	{
		while (t.var[t.increment])
		{
			if (t.var[t.increment] == env[t.index][t.increment])
				t.flag++ ;
			t.increment++ ;
		}
		if (t.flag == le_count(t.var) && \
		(le_count(copy_till_charac(env[t.index], '=')) == le_count(t.var)))
			return (return_from_here(env[t.index], env[t.index][t.increment]));
		t.increment = 0;
		t.flag = 0;
		t.index++ ;
	}
	return (NULL);
}

char	*copy_from(char *string, char here)
{
	t_all_not_vars	t;

	t.aloca = gc(sizeof(char **) * \
	(le_count(string) + 3), 0, 0, 0);
	if (!t.aloca)
		return (NULL);
	while (string[t.index])
	{
		if (string[t.index] == here)
		{
			t.index++ ;
			while (string[t.index])
			{
				t.aloca[t.increment] = string[t.index];
				t.index++ ;
				t.increment++ ;
			}
			t.aloca[t.increment] = '\0';
			return (t.aloca);
		}
		t.index++ ;
	}
	return (NULL);
}

char	*keep_one_space(char *string)
{
	t_all_not_vars	t;

	t.index = 0;
	t.increment = 0;
	t.aloca = gc(sizeof(char **) * (le_count(string) + 1), 0, 0, 0);
	if (!t.aloca)
		return (NULL);
	while (string[t.index])
	{
		while (string[t.index] && string[t.index] != ' ')
		{
			t.aloca[t.increment] = string[t.index];
			t.increment++;
			t.index++;
		}
		if (string[t.index] && string[t.index] == ' ' \
		&& string[t.index + 1] != ' ')
		{
			t.aloca[t.increment] = ' ';
			t.increment++;
		}
		t.index++;
	}
	t.aloca[t.increment] = '\0';
	return (t.aloca);
}

char	**for_the_unset(char **env, char *var_name)
{
	t_all_not_vars	t;

	t.flag = 0;
	t.allocation = gc(sizeof(char *) * (count_twode(env) + 1), 0, 0, 0);
	adress_unset(&t.flag, &t.increment, &t.index, -1);
	t.up = 0;
	while (env[t.index])
	{
		while (var_name[t.increment])
		{
			if (env[t.index][t.increment] == var_name[t.increment])
				t.flag++;
			t.increment++;
		}
		if (t.flag == le_count(var_name) && \
		le_count(copy_till_charac(env[t.index], '=')) == t.flag)
			t.increment = 0;
		else
		{
			t.allocation[t.up] = return_line(env[t.index]);
			t.up++;
		}
		adress_unset(&t.flag, &t.increment, &t.index, 0);
	}
	return (t.allocation[t.up] = NULL, t.allocation);
}
