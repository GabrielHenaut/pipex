/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 16:17:17 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/07/12 19:52:15 by Ghenaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	get_file(char *infile, char *outfile, t_pipex *data)
{
	char	buf[1];

	data->infile = open(infile, O_RDONLY);
	data->outfile = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 0000644);
	if (data->infile < 0 && data->outfile >= 0)
	{
		close(data->outfile);
		msg_error("Invalid infile\n", 0);
	}
	else if (data->outfile < 0 && data->infile >= 0)
	{
		close(data->infile);
		msg_error("Invalid Outfile\n", 1);
	}
	else if (data->outfile < 0 && data->infile < 0)
		msg_error("Invalid infile and outfile\n", 0);
	if (read(data->infile, buf, 1) == 0)
	{
		close(data->outfile);
		close(data->infile);
		exit(1);
	}
}
