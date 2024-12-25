/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:07:39 by mmaghri           #+#    #+#             */
/*   Updated: 2024/04/26 12:35:25 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*merge_path(char *string, char *path_add)
{
	t_all_vars	path;

	path.index = 0;
	path.increment = 0;
	path.allocation = gc(sizeof(char *) * (le_count(string) + 3), 0, 0, 0);
	if (!path.allocation)
		return (NULL);
	while (string[path.index])
	{
		path.allocation[path.increment] = string[path.index];
		path.increment++;
		path.index++ ;
	}
	path.index = 0;
	path.allocation[path.increment] = '/';
	path.increment++;
	while (path_add[path.index])
	{
		path.allocation[path.increment] = path_add[path.index];
		path.increment++;
		path.index++ ;
	}
	path.allocation[path.increment] = '\0';
	return (path.allocation);
}

char	*for_remove_cd_func(char *string, char *allocation)
{
	t_all_vars	every;

	every.index = 0;
	every.increment = 0;
	while (string[every.index] && string[every.index] \
	&& string[every.index] != ' ')
	{
		allocation[every.increment] = string[every.index];
		every.index++ ;
		every.increment++ ;
	}
	allocation[every.increment] = '\0';
	return (allocation);
}

char	*remove_cd(char *string, char *ignore)
{
	t_all_vars	every;

	every.index = 0;
	every.increment = 0;
	every.for_total = le_count(ignore);
	every.allocation = gc(sizeof(char **) * (le_count(string) + 3), 0, 0, 0);
	if (!every.allocation)
		return (NULL);
	while (string[every.index] && string[every.index] == ' ')
		every.index++ ;
	while (string[every.index] != ' ' && every.for_total != 0)
	{
		if (string[every.index] == ignore[every.increment])
		{
			every.index++ ;
			every.increment++ ;
		}
		every.for_total--;
	}
	while (string[every.index] && string[every.index] == ' ')
		every.index++ ;
	every.allocation = for_remove_cd_func(&string[every.index], \
	every.allocation);
	return (every.allocation);
}

char	*flag_last(char *string, char flag_this)
{
	int		index;
	int		flag ;
	char	*allocation ;

	flag = 0;
	index = 0;
	allocation = gc(sizeof(char *) * (le_count(string) + 1), 0, 0, 0);
	if (!allocation)
		return (NULL);
	if (le_count(string) == 1 && string[0] == '/')
		return ("/");
	while (string[index])
	{
		if (string[index] == flag_this)
			flag = index ;
		index++ ;
	}
	index = 0;
	while (string[index] && index <= flag)
	{
		allocation[index] = string[index];
		index++ ;
	}
	allocation[index] = '\0';
	return (allocation);
}
