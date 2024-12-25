/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaghri <mmaghri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 17:16:59 by mmaghri           #+#    #+#             */
/*   Updated: 2024/04/27 16:11:59 by mmaghri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_signal_received = 0;

char	*string_move(char *string)
{
	int		index ;
	char	*allocation ;

	allocation = gc(sizeof(char *) * (le_count(string) + 1), 0, 0, 0);
	index = 0;
	while (string[index])
	{
		allocation[index] = string[index];
		index++ ;
	}
	allocation[index] = '\0';
	return (allocation);
}

char	**list_to_array(char **content)
{
	t_all_vars	this;

	this.index = 0;
	this.increment = 0;
	this.twode = gc(sizeof(char **) * (count_twode(content) + 1), 0, 0, 0);
	while (content[this.index])
	{
		if (le_count(content[this.index]) == 1 && content[this.index][0] == ' ')
			this.index++ ;
		this.twode[this.increment] = string_move(content[this.index]);
		this.increment++ ;
		this.index++ ;
	}
	this.twode[this.increment] = NULL ;
	return (this.twode);
}

void	signals_handler(int sign)
{
	if (sign == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		exit_status(1, 0);
	}
}

int	red_line(char *input, t_tree *root, t_th *tree_h, int *fd)
{
	while (1)
	{
		input = readline("➜ miniBash : ");
		if (!input)
			return (on_new(), gc(0, 2, 0, exit_status(0, 1)), 0);
		if (input[0] && is_empty(input))
			add_history(input);
		root = parsing(input, tree_h);
		if (!root)
		{
			gc(0, 4, 0, 0);
			continue ;
		}
		if (!g_signal_received)
		{
			execution(root);
			my_dup2(fd[0], 0);
			my_dup2(fd[1], 1);
		}
		gc(0, 4, 0, 0);
		exit_status(0, 3);
	}
	return (gc(0, 2, 0, exit_status(0, 1)), 0);
}

int	main(int ac, char **av, char **env)
{
	t_th	*tree_h;
	t_tree	*root;
	char	*input;
	int		fd[2];

	(void) av;
	if (ac != 1)
		return (0);
	rl_catch_signals = 0;
	if (initial_checks())
		return (1);
	input = NULL;
	(1) && (root = NULL, tree_h = gc(sizeof(t_th), 0, 0, 0), 0);
	tree_h->env = move_env(env);
	tree_h->export = add_it_to_env(tree_h->export, "OLDPWD");
	signal(SIGINT, signals_handler);
	signal(SIGQUIT, signals_handler);
	fd[0] = my_dup(0);
	fd[1] = my_dup(1);
	gc(fd[0], 3, 0, 0);
	gc(fd[1], 3, 0, 0);
	tree_h->sav_in = fd[0];
	tree_h->sav_out = fd[1];
	red_line(input, root, tree_h, fd);
	return (0);
}
