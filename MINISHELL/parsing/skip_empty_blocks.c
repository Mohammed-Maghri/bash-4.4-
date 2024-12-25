/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_empty_blocks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:16:32 by mlouazir          #+#    #+#             */
/*   Updated: 2024/03/30 02:42:12 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_if_ended(t_pt *bool, int pass)
{
	if (pass && (bool->d_bool || bool->s_bool || \
	(bool->bo_bool - bool->bc_bool)))
		return (print_error("syntax error", NULL), 1);
	else
	{
		bool->s_bool = 0;
		bool->d_bool = 0;
		bool->e_bool = 0;
		bool->ex_bool = 0;
		bool->bo_bool = 0;
		bool->bc_bool = 0;
	}
	return (0);
}

int	check_bool(char *new_input, int index, t_pt *bool)
{
	if ((new_input[index] == '\'') && !(bool->s_bool) && !(bool->d_bool))
		bool->s_bool = 1;
	else if ((new_input[index] == '\"') && !(bool->s_bool) && !(bool->d_bool))
		bool->d_bool = 1;
	else if ((new_input[index] == '\'') && (bool->s_bool) && !(bool->d_bool))
		bool->s_bool = 0;
	else if ((new_input[index] == '\"') && !(bool->s_bool) && (bool->d_bool))
		bool->d_bool = 0;
	else if (new_input[index] == '(' && !(bool->s_bool) && !(bool->d_bool))
		bool->bo_bool++;
	else if (new_input[index] == ')' && !(bool->s_bool) && !(bool->d_bool))
		bool->bc_bool++;
	else if (is_delimiter(new_input[index], 1) && \
	!(bool->s_bool) && !(bool->d_bool))
		bool->e_bool = 0;
	if (new_input[index] == '&' && (((new_input[index + 1] \
	&& new_input[index + 1] != '&') || !new_input[index + 1]) \
	&& (index - 1 > -1 && new_input[index - 1] != '&')) \
	&& (!(bool->s_bool) && !(bool->d_bool)))
		return (print_error("syntax error", NULL), 1);
	return (0);
}

char	*skip_empty_blocks(char *input_r)
{
	t_pt	bool;
	char	*input;
	int		i;
	int		j;

	i = 0;
	check_if_ended(&bool, 0);
	input = ft_strtrim(input_r, " \t");
	while (input[i])
	{
		if (((!bool.d_bool && !bool.s_bool && !bool.e_bool)) \
		&& (input[i] == 32 || input[i] == 9))
		{
			j = i - 1;
			while (input[++j] && (input[j] == 32 || input[j] == 9))
				;
			input = cut_string(input, i++, j);
		}
		else
			if (check_bool(input, i++, &bool))
				return (NULL);
	}
	if (check_if_ended(&bool, 1))
		return (NULL);
	return (input);
}
