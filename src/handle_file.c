/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghenaut- <ghenaut-@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 16:17:17 by ghenaut-          #+#    #+#             */
/*   Updated: 2022/07/07 22:30:05 by ghenaut-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	get_infile(char *argv, t_pipex *data)
{
	data->infile = open(argv, O_RDONLY);
	if (data->infile < 0)
		msg_error("Invalid infile\n", 7);
}

void	get_outfile(char *argv, t_pipex *data)
{
	data->outfile = open(argv, O_CREAT | O_RDWR | O_TRUNC, 0000644);
	if (data->outfile < 0)
	{
		close(data->infile);
		msg_error("Invalid Outfile\n", 8);
	}
}
