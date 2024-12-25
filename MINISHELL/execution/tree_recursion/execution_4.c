/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:15:01 by mlouazir          #+#    #+#             */
/*   Updated: 2024/04/27 09:40:28 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	setsig(void)
{
	struct termios	t;

	tcgetattr(STDIN_FILENO, &t);
	t.c_cflag = ~NOFLSH;
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

void	exit_c(int sign)
{
	if (sign == SIGINT)
	{
		write(1, "\n", 1);
		exit_status((130), 0);
	}
	else if (sign == SIGQUIT)
	{
		setsig();
		exit_status((131), 0);
		printf("Quit");
	}
	exit_status(0, 2);
}

int	exit_status(int state, int mode)
{
	static int	status;
	static int	is_sig;

	if (!mode)
		status = state;
	if (mode == 2)
		is_sig = 1;
	if (mode == 3)
		is_sig = 0;
	if (mode == 4)
		return (is_sig);
	return (status);
}

int	is_space(char *string)
{
	int	i;

	i = -1;
	while (string[++i])
		if (string[i] == 9 || string[i] == 32)
			return (0);
	return (1);
}
