/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:00:54 by mmaghri           #+#    #+#             */
/*   Updated: 2024/04/26 12:37:03 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**copy_twode(char **string)
{
	int		index ;
	char	**allocation;

	index = 0;
	allocation = gc(sizeof(char **) * (count_twode(string) + 3), 0, 0, 0);
	if (!allocation)
		return (NULL);
	while (string[index])
	{
		allocation[index] = return_line(string[index]);
		index++ ;
	}
	allocation[index] = NULL ;
	return (allocation);
}
