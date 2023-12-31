/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahani <itahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:39:04 by itahani           #+#    #+#             */
/*   Updated: 2023/08/14 14:41:05 by itahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <linux/limits.h>
#include <stdio.h>

char	*ft_strjoin_char(char const *s1, char s2)
{
	char	*res;
	int		i;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	res = malloc(sizeof (char) * ((ft_strlen((char *)s1) + 2)));
	if (!res)
		return (NULL);
	while (s1[i] != '\0')
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = s2;
	res[i + 1] = '\0';
	return (res);
}

int	the_real_pwd(t_init *init)
{
	char	buffer[PATH_MAX];
	char	*path;

	(void)init;
	path = get_env_value("PWD", init);
	if (path != NULL)
		return (printf("%s\n", path), 0);
	path = getcwd(buffer, PATH_MAX);
	if (path == NULL)
		return (printf("ERROR"), 1);
	printf("%s\n", path);
	return (0);
}
