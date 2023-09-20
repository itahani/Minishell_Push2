/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_itcommand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nklingsh <nklingsh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 15:38:45 by nklingsh          #+#    #+#             */
/*   Updated: 2023/09/20 18:58:50 by nklingsh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_file_exist(char *path)
{
	if (!path)
		return (0);
	if (access(path, F_OK) != 0)
		return (1);
	return (0);
}

int	file_exec(char *path)
{
	if (!path)
		return (0);
	if (access(path, X_OK) == 0)
		return (1);
	return (0);
}

int	check_if_directory(char *path)
{
	struct stat	is_directory;

	if (stat(path, &is_directory) != 0)
		return (0);
	return (S_ISDIR(is_directory.st_mode));
}

int	check_infile_fd(t_token_list *tok_list, t_exec_init *exec_init , t_init *init)
{
	t_str_list	*in_file;
	int			fd;
	(void)init;
	(void)exec_init;

	in_file = tok_list->in_file;
	while (in_file)
	{
		if (check_file_exist(in_file->str_list) == 1)
		{	
			printf("Minishell: %s: No such file or directory\n", in_file->str_list);
			return (1);
		}
		fd = open(in_file->str_list, O_RDONLY);
		if (fd == -1)
			return (g_status_exit_code = 1, 1);
		close(fd);
		in_file = in_file->next;
	}
	// printf("FD == %i\n", fd);
	return (0);
}

int quitafterpipe(t_init *init)
{
	t_lex_list *head;
	int			res;

	head = init->lst_lex;
	res = 0;
	while (head)
	{
		if (head->operator == PIPE)
		{
			if ((head->next->operator == APP_OUT || head->next->operator == REDIR_OUT || head->next->operator == REDIR_IN || head->next->operator == HERE_DOC))
				return (1);
		}
	}
	return (0);
}

int	check_outfile_fd(t_token_list *tok_list, t_init *init)
{
	t_str_list	*out_file;
	int			fd;

	out_file = tok_list->out_file;
	while (out_file)
	{
		if (check_if_directory(out_file->str_list) == 1)
			return (g_status_exit_code = 1, 1);
		if (ft_strsame(out_file->str_list2, "O_TRUNC"))
			fd = open(out_file->str_list, O_RDWR | O_CREAT | O_TRUNC, 0666);
		else if (ft_strsame(out_file->str_list2, "O_APPEND"))
			fd = open(out_file->str_list, O_RDWR | O_CREAT | O_APPEND, 0666);
		if (fd == -1)
			return (g_status_exit_code = 1, 1);
		close(fd);
		out_file = out_file->next;
	}
	if (quitafterpipe(init) == 1)
		return (1);
	return (0);
}
