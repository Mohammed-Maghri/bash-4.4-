/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 12:10:41 by mlouazir          #+#    #+#             */
/*   Updated: 2024/04/26 14:09:17 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_signal_received;

void	set_tokens_2(t_list *tmp)
{
	if (!ft_strncmp(tmp->content, "$", 1))
		tmp->token_type = DOLLAR;
	else if (!ft_strncmp(tmp->content, "&&", 2))
		tmp->token_type = AND;
	else if (!ft_strncmp(tmp->content, "\"", 1))
		tmp->token_type = D_QU;
	else if (!ft_strncmp(tmp->content, "\'", 1))
		tmp->token_type = S_QU;
	else if (!ft_strncmp(tmp->content, "(", 1))
		tmp->token_type = PARA_OPEN;
	else if (!ft_strncmp(tmp->content, ")", 1))
		tmp->token_type = PARA_CLOSE;
	else if (!ft_strncmp(tmp->content, "|", 1))
		tmp->token_type = PIPE;
	else
		tmp->token_type = WORD;
}

void	set_tokens(t_tracker *holder)
{
	t_list	*tmp;

	tmp = holder->head;
	while (tmp)
	{
		if (!ft_strncmp(tmp->content, "<<", 2))
			tmp->token_type = HEREDOC;
		else if (!ft_strncmp(tmp->content, "<", 1))
			tmp->token_type = REDIR_IN;
		else if (!ft_strncmp(tmp->content, ">>", 2))
			tmp->token_type = REDIR_APPEND;
		else if (!ft_strncmp(tmp->content, ">", 1))
			tmp->token_type = REDIR_OUT;
		else if (!ft_strncmp(tmp->content, " ", 1) || \
		!ft_strncmp(tmp->content, "\t", 1))
			tmp->token_type = SPACEE;
		else if (!ft_strncmp(tmp->content, "||", 2))
			tmp->token_type = OR;
		else
			set_tokens_2(tmp);
		tmp = tmp->next;
	}
}

int	set_list(t_tracker *holder, char *input_r)
{
	char	*input;
	int		i;
	int		j;
	int		l;

	i = 0;
	j = 0;
	input = skip_empty_blocks(input_r);
	if (!input)
		return (free(input_r), 1);
	l = ft_strlen(input);
	while (j <= l)
	{
		if (is_delimiter(input[j], 0))
		{
			if (i == j)
				add_to_list_single(holder, input, &j);
			else
				add_to_list_double(holder, input, i, &j);
			i = j + 1;
		}
		j++;
	}
	return (free(input_r), 0);
}

void	set_things_up(t_tracker **holder, t_th **tree_h)
{
	(*holder) = gc(sizeof(t_tracker), 0, 1, 0);
	(*tree_h)->pipe_i = 0;
	(*tree_h)->pipes = gc(sizeof(int *), 0, 1, 0);
	(*tree_h)->pipes[0] = NULL;
	(*tree_h)->fds = gc(sizeof(int) * 1, 0, 1, 0);
	(*tree_h)->fds[0] = 0;
	(*tree_h)->path = path_maker((*tree_h)->env);
	(*tree_h)->next_target = NULL;
	(*tree_h)->root = NULL;
	(*holder)->head = NULL;
	(*holder)->tail = NULL;
}

t_tree	*parsing(char *input, t_th *tree_h)
{
	t_tracker			*holder;
	t_list				*tmp;

	if (!input[0] || !is_empty(input))
		return (free(input), NULL);
	set_things_up(&holder, &tree_h);
	if (set_list(holder, input))
		return (exit_status(258, 0), NULL);
	tmp = holder->tail;
	holder->tail = holder->tail->prev;
	if (holder->tail)
		holder->tail->next = NULL;
	tmp->next = NULL;
	tmp->prev = NULL;
	tmp = holder->tail;
	holder->env = tree_h->env;
	set_tokens(holder);
	if (check_validity(holder) || g_signal_received)
	{
		exit_status(258, 0);
		(g_signal_received) && (exit_status(1, 0));
		return (close_herefiles(holder), NULL);
	}
	tree_generator(holder->head, tree_h);
	return (tree_h->root);
}
