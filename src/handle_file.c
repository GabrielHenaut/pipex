/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 16:17:17 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/08/03 12:01:52 by ghenaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	get_file(char *infile, char *outfile, t_pipex *data)
{
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
}
