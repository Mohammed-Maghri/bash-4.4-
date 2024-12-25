/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expo_u.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 03:08:26 by mmaghri           #+#    #+#             */
/*   Updated: 2024/04/26 12:36:24 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*copy_till_charac(char *string, char to_here)
{
	t_all_vars	till;
	int			flag;

	till.index = 0;
	flag = 0;
	till.allocation = gc(sizeof(char **) * \
	(le_count(string) + 3), 0, 0, 0);
	if (search_in_for(string, to_here) != 1)
		return (string);
	while (string[till.index])
	{
		if (string[till.index] == to_here)
		{
			flag = 1;
			break ;
		}
		till.allocation[till.index] = string[till.index];
		till.index++ ;
	}
	if (flag == 1)
	{
		till.allocation[till.index] = '\0';
		return (till.allocation);
	}
	return (NULL);
}

char	*return_this(char *string, char *merge)
{
	t_all_vars	till;

	till.index = 0;
	till.increment = 0;
	till.allocation = gc(sizeof(char **) * \
	((le_count(string) + 1) + (le_count(merge) + 1)), 0, 0, 0);
	while (merge[till.index])
	{
		till.allocation[till.increment] = merge[till.index];
		till.index++ ;
		till.increment++;
	}
	while (string[till.index])
	{
		till.allocation[till.increment] = string[till.index];
		till.increment++;
		till.index++;
	}
	till.allocation[till.increment] = '\0';
	return (till.allocation);
}
