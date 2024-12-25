/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_functions_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 12:46:15 by mlouazir          #+#    #+#             */
/*   Updated: 2024/04/26 12:40:35 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_n(char **string, int *index)
{
	char	*tmp;
	int		i;
	int		tmp_i;

	i = -1;
	tmp = gc(1, 0, 0, 0);
	tmp[0] = 0;
	tmp_i = *index;
	if (!here_comp(string[tmp_i], " ", 1) || !here_comp(string[tmp_i], "\t", 1))
		tmp_i += 1;
	tmp_i -= 1;
	while (string[++tmp_i] && here_comp(string[tmp_i], " ", 1) && \
	here_comp(string[tmp_i], "\t", 1))
		tmp = ft_strjoin(tmp, string[tmp_i]);
	if (!tmp)
		return (1);
	if (tmp[++i] != '-')
		return (1);
	while (tmp[++i])
		if (tmp[i] != 'n')
			return (1);
	if (i == 1 && tmp[i] != 'n')
		return (1);
	return (*index = tmp_i, 0);
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		*(char *)b = (unsigned char)c;
		b++;
		i++;
	}
	return (b - i);
}

static	void	ft_stockn(char *str, int n, int *p)
{
	long	ln;

	ln = n;
	if (ln < 0)
	{
		ln = -ln;
		ft_memset((str + *p), '-', 1);
		*p += 1;
	}
	if (ln > 9)
	{
		ft_stockn(str, ln / 10, p);
		ft_stockn(str, ln % 10, p);
	}
	else
	{
		ft_memset((str + *p), (ln + '0'), 1);
		*p += 1;
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	long	ln;
	int		s;
	int		p;

	ln = n;
	p = 0;
	s = 0;
	if (ln < 0)
	{
		ln = -ln;
		s++;
	}
	while (ln >= 10)
	{
		ln /= 10;
		s++;
	}
	s++;
	str = gc(s + 1, 0, 0, 0);
	ft_stockn(str, n, &p);
	str[s] = '\0';
	return (str);
}
