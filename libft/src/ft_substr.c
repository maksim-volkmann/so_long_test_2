/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvolkman <mvolkman@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 13:53:15 by mvolkman          #+#    #+#             */
/*   Updated: 2024/03/14 12:37:41 by mvolkman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t n)
{
	size_t	strlen;
	size_t	sublen;
	char	*newstr;
	size_t	i;

	strlen = ft_strlen(s);
	if (!s)
		return (NULL);
	if (start >= strlen)
		return (ft_strdup(""));
	sublen = n;
	if (sublen > (strlen - start))
		sublen = strlen - start;
	newstr = (char *)malloc(sublen + 1);
	if (!newstr)
		return (NULL);
	i = 0;
	while (i < sublen)
	{
		newstr[i] = s[start + i];
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}
