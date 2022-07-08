/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 16:17:17 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/07/07 22:59:16 by ghenaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static void	here_doc(char *argv, t_pipex *pipex)
{
	int		file;
	char	*buf;

	file = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (file < 0)
		msg_error("Error to create here_doc_tmp\n", 9);
	while (1)
	{
		write(1, "heredoc> ", 9);
		buf = get_next_line(0);
		if (!ft_strncmp(argv, buf, ft_strlen(argv)))
			break ;
		write(file, buf, ft_strlen(buf));
		write(file, "\n", 1);
		free(buf);
	}
	free(buf);
	close(file);
	pipex->infile = open(".here_doc_tmp", O_RDONLY);
	if (pipex->infile < 0)
	{
		unlink(".heredoc_tmp");
		msg_error("error to open here_doc_tmp", 1);
	}
}

void	get_infile(char **argv, t_pipex *data)
{
	if (!ft_strncmp("here_doc", argv[1], 9))
		here_doc(argv[2], data);
	else
	{
		data->infile = open(argv[1], O_RDONLY);
		if (data->infile < 0)
			msg_error("Invalid infile\n", 7);
	}
}

void	get_outfile(char *argv, t_pipex *data)
{
	if (data->here_doc)
		data->outfile = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0000644);
	else
		data->outfile = open(argv, O_CREAT | O_RDWR | O_TRUNC, 0000644);
	if (data->outfile < 0)
	{
		close(data->infile);
		msg_error("Invalid Outfile\n", 8);
	}
}
