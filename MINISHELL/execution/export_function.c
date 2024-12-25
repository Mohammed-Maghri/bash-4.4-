/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_function.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaghri <mmaghri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:33:00 by mmaghri           #+#    #+#             */
/*   Updated: 2024/03/12 15:26:15 by mmaghri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_if_the_same(char *string, char *make_sure)
{
	t_all_vars	ch;

	ch.index = 0;
	ch.increment = 0;
	ch.flag = 0;
	ch.hold = 0;
	if (string[ch.index] == make_sure[0])
	{
		ch.index++;
		ch.increment++;
		ch.flag++;
		while (string[ch.index] && ch.increment <= 5)
		{
			if (string[ch.index] == make_sure[ch.increment])
				ch.flag++;
			ch.increment++;
			ch.index++ ;
		}
		if (ch.flag == le_count(make_sure))
			ch.hold = 1;
	}
	return (ch.hold);
}

char	*copy_for_export(char *string, char *for_res)
{
	int	index ;
	int	increment;

	increment = 0;
	index = 0;
	while (string[index])
	{
		if (string[index] == '"')
			index++ ;
		for_res[increment] = string[index];
		increment++ ;
		index++ ;
	}
	for_res[increment] = '\0';
	return (for_res);
}

char	*var_turn(char *string, char *worck_with)
{
	worck_with = remove_string(string, "export");
	worck_with = copy_till_charac(worck_with, '=');
	return (worck_with);
}

char	*for_the_while(char *string, char *for_res)
{
	t_all_vars	func;

	while (string[func.index])
	{
		if (string[func.index] == '=')
		{
			if (string[func.index + 1] == ' ')
				return (NULL);
			func.index++ ;
			for_res = copy_for_export(&string[func.index], for_res);
			break ;
		}
		func.index++ ;
	}
	return (func.for_res);
}
