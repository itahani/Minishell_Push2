/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itahani <itahani@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 16:54:28 by nklingsh          #+#    #+#             */
/*   Updated: 2023/09/11 17:42:32 by itahani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_heredoc(char *delimiteur, t_init *init)
{
	char		*filename;
	char		*line;
	int			fd;
	int			oui;

	filename = heredoc_name(init->lst_token->delimeter->str_list, init);
	fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, 0777);
	oui = dup(0);
	g_status_exit_code = 0;
	if (!filename)
		ft_print_fd("Malloc error\n", 2);
	// signal(SIGINT, heredoc_sigint);
	// signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("> ");
		// printf("LINE === %s\n", line);
		// printf("G STATUS === %i\n", g_status_exit_code);
		if (!line)
		{
			if (g_status_exit_code == 130)
				break ;
			closer_the_magasine(fd, filename, oui, init);
			break ;
		}
		if (ft_strcmp(delimiteur, line) == 0)
		{
			if (line)
				free(line);
			break ;
		}
		else
			the_writer(fd, expand_env_and_quote(line, init), \
				ft_strlen(expand_env_and_quote(line, init)));
		if (line)
			free(line);
	}
	closer_totally_spies(fd, oui);
}

void	while_here_doc_exist(t_init *init)
{
	t_token_list	*token;
	t_str_list		*head;

	token = init->lst_token;
	while (init->lst_token)
	{
		head = init->lst_token->delimeter;
		while (init->lst_token->delimeter)
		{
			if (init->here_doc_tinker == 1)
				break ;
			ft_heredoc(init->lst_token->delimeter->str_list, init);
			init->lst_token->delimeter = init->lst_token->delimeter->next;
		}
		init->lst_token->delimeter = head;
		init->lst_token = init->lst_token->next;
	}
	init->lst_token = token;
}

void	heredoc_supp(t_token_list *token_lst)
{
	while (token_lst)
	{
		while (token_lst->delimeter)
		{
			unlink(token_lst->delimeter->str_list2);
			token_lst->delimeter = token_lst->delimeter->next;
		}
		token_lst = token_lst->next;
	}
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
