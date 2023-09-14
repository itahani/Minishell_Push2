/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahani <itahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 16:14:56 by nklingsh          #+#    #+#             */
/*   Updated: 2023/09/06 22:03:19 by itahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*heredoc_name(char *delimiteur, t_init *init)
{
	char		*filename;
	static int	i = 1;
	char		*stock_itoa;
	char		*tmp;

	filename = "/tmp/heredoc_tmp";
	stock_itoa = ft_itoa(i);
	tmp = ft_strjoin(filename, stock_itoa);
	lstaddback_malloc(init, lstnew_malloc(tmp));
	filename = ft_strjoin(tmp, ".txt");
	lstaddback_malloc(init, lstnew_malloc(filename));
	i++;
	delimiteur = ft_strdup(filename);
	lstaddback_malloc(init, lstnew_malloc(delimiteur));
	init->lst_token->delimeter->str_list2 = delimiteur;
	free(stock_itoa);
	signal(SIGINT, heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
	return (filename);
}

void	closer_totally_spies(int fd, int oui)
{
	close(fd);
	dup2(oui, 0);
	close(oui);
}

void	closer_the_magasine(int fd, char *filename, int oui, t_init *init)
{
	(void)fd;
	printf("warning: here-document delimited by end-of-file\n");
	close(oui);
	unlink(filename);
	init->here_doc_tinker = 1;
}

void	the_writer(int fd, char *str, int size_str)
{
	write(fd, str, size_str);
	write(fd, "\n", 1);
}
