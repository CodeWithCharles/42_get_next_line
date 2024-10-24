/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpoulain <cpoulain@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:07:20 by cpoulain          #+#    #+#             */
/*   Updated: 2024/10/24 14:46:58 by cpoulain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Includes */

#include "get_next_line.h"

/* Utils implementations */

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*(t_uchar *)s == (t_uchar)c)
			return ((char *)s);
		++s;
	}
	if (*(t_uchar *)s == (t_uchar)c)
		return ((char *)s);
	return (NULL);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((t_byte *)dest)[i] = ((t_byte *)src)[i];
		i++;
	}
	return (dest);
}

size_t	ft_strlen(const char *s)
{
	const char	*org = s;

	while (*s)
		++s;
	return (s - org);
}

void	ft_strcat(char **dst_ptr, const char *src)
{
	size_t	dst_len;
	size_t	src_len;
	char	*ans;

	dst_len = ft_strlen(*dst_ptr);
	src_len = ft_strlen(src);
	ans = malloc(dst_len + src_len + 1);
	if (ans)
	{
		ft_memcpy(ans, *dst_ptr, dst_len);
		ft_memcpy(ans + dst_len, src, src_len);
		ans[dst_len + src_len] = '\0';
	}
	free(*dst_ptr);
	*dst_ptr = ans;
}
