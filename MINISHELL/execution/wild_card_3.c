/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_card_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/28 23:12:55 by mlouazir          #+#    #+#             */
/*   Updated: 2024/04/26 14:36:15 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	incrementt(int *flag, int *index, int *increment)
{
	*flag += 1;
	*index += 1;
	*increment += 1;
}

int	valid_wild_card(char *in)
{
	int	i;

	i = -1;
	while (in[++i])
		if (in[i] == '\'' || in[i] == '\"')
			return (1);
	return (0);
}

int	*re_size_array(int *first_array, int new_input, int old_input, int index)
{
	int	*new_array;
	int	size_1;
	int	size_2;
	int	i;

	i = 0;
	new_array = gc((new_input + (new_input - 1) \
	+ old_input) * sizeof(int), 0, 1, 0);
	while (i < index)
	{
		new_array[i] = first_array[i];
		i++;
	}
	size_1 = i + new_input;
	size_2 = i;
	while (i < size_1)
		new_array[i++] = 0;
	old_input -= i;
	while (size_2 < old_input)
		new_array[i++] = first_array[size_2++];
	return (new_array);
}

char	**wild_helper(char *string)
{
	char	**tmp;
	int		first_pos;

	first_pos = 0;
	tmp = NULL;
	string = cut_star(string);
	if (string[0] == '.')
		first_pos = 1;
	if (ft_strlen(string) == 1 && string[0] == '*')
		tmp = function_this_one(NULL, NULL, 10, first_pos);
	else if (string[0] == '*' && check_last_elem(string, '*') == -1)
		tmp = function_this_one(delete_first_and_last(&string[1]), \
		NULL, 2, first_pos);
	else if (string[0] != '*' && (check_last_elem(string, '*') == 0))
		tmp = function_this_one(copy_till_charac(string, '*'), \
		copy_after_find(string, '*'), 1, first_pos);
	else if (string[0] == '*')
		tmp = function_this_one(NULL, copy_after_find(string, '*'), \
		-1, first_pos);
	else if (string[0] != '*')
		tmp = function_this_one(copy_till_charac(string, '*'), \
		NULL, 0, first_pos);
	return (tmp);
}

char	*function_array_line(char **env)
{
	int		index ;
	char	*allocation;

	index = 0;
	if (!env)
		return (NULL);
	allocation = NULL;
	while (env[index])
	{
		if (!allocation)
			allocation = return_line(env[index]);
		else if (allocation)
			allocation = merge_both(allocation, env[index]);
		index++ ;
	}
	return (allocation);
}
