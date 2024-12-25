/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_functions_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouazir <mlouazir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:37:51 by mlouazir          #+#    #+#             */
/*   Updated: 2024/04/26 12:40:26 by mlouazir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_strlcat(char *dst, char *src, int dstsize)
{
	int	i;
	int	j;
	int	ls;
	int	ld;

	i = 0;
	j = 0;
	ls = ft_strlen(src);
	ld = ft_strlen(dst);
	while (dst[i])
		i++;
	while ((j + i) < (dstsize - 1) && src[j])
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	return (ld + ls);
}

int	ft_strlcpy(char *dst, const char *src, int dstsize)
{
	int		i;
	int		ls;

	i = 0;
	ls = ft_strlen((char *)src);
	if (dstsize == 0 || ls == 0)
		return (ls);
	while (src[i] && i < (dstsize - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ls);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		size;

	size = ft_strlen(s1) + ft_strlen(s2);
	str = gc(size + 1, 0, 0, 0);
	if (size == 0)
		str[0] = '\0';
	else
	{
		ft_strlcpy(str, (char *)s1, size + 1);
		if (ft_strlen(s2) == 0)
			str[size] = '\0';
		else
			ft_strlcat(str, (char *)s2, size + 1);
	}
	return (str);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] && s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	here_comp(char *s1, char *s2, int n)
{
	int	i;

	i = 0;
	if (!n)
		n = 1;
	if (!s1 || !s2)
		return (1);
	while ((s1[i] && s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
