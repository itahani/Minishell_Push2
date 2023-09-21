/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 17:12:35 by nklingsh          #+#    #+#             */
/*   Updated: 2023/09/20 21:12:09 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char *str1, char *str2)
{
	int		i;
	int		y;
	char	*str;

	i = 0;
	y = 0;
	if (!str2)
		return (NULL);
	str = malloc((ft_strlen(str1) + ft_strlen(str2) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (str1[i])
		str[y++] = str1[i++];
	i = 0;
	while (str2[i])
		str[y++] = str2[i++];
	str[y] = '\0';
	return (str);
}

int	check_infile_fd(t_token_list *tok_list)
{
	t_str_list	*in_file;
	int			fd;

	in_file = tok_list->in_file;
	while (in_file)
	{
		if (check_file_exist(in_file->str_list) == 1)
		{	
			printf("Minishell: %s: No such file or directory\n", \
			in_file->str_list);
			return (1);
		}
		fd = open(in_file->str_list, O_RDONLY);
		if (fd == -1)
			return (g_status_exit_code = 1, 1);
		close(fd);
		in_file = in_file->next;
	}
	return (0);
}

char	*get_env_value(char *name, t_init *init)
{
	t_env_list	*env_list;

	env_list = init->lst_env;
	while (env_list)
	{
		if (ft_strsame(name, env_list->name))
			return (env_list->value);
		env_list = env_list->next;
	}
	return (NULL);
}
