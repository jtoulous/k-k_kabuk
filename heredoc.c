/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agoichon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 16:35:22 by agoichon          #+#    #+#             */
/*   Updated: 2023/03/07 09:39:36 by agoichon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_doc_argz(int fd, char *lim)
{
	char	*buf;

	while (1)
	{
		ft_putstr_fd(">", 1);
		buf = get_next_line(0);
		if (ft_strncmp(buf, lim, ft_strlen(lim)) == 0
			&& ft_strlen(buf) == ft_strlen(lim) + 1)
		{
			free(buf);
			return ;
		}		
		write (fd, buf, ft_strlen(buf));
		free (buf);
	}
}

void	replace_hdoc(t_data *data, char *file, int spot)
{
	char	*ante;
	char	*pre;
	int		end_hd;
	int		end_line;

	end_hd = spot;
	while ((data->line[end_hd] == '<' || data->line[end_hd] == ' ')
		&& data->line[end_hd])
		end_hd++;
	while ((data->line[end_hd] != ' ' || in_or_out(data->line, end_hd) != 0)
		&& valid_pipe(data->line, end_hd) != 1
		&& data->line[end_hd])
		end_hd++;
	end_line = end_hd;
	while (data->line[end_line])
		end_line++;
	ante = ft_substr(data->line, 0, spot + 1);
	pre = ft_substr(data->line, end_hd, end_line - end_hd);
	free (data->line);
	data->line = triple_strjoin(ante, file, pre);
	mega_free(ante, pre, NULL, NULL);
}

void	prep_hdoc(t_data *data, int z, char *lim)
{
	char	*file;
	char	*fileno;
	int		fd;

	fileno = ft_itoa(z);
	file = ft_strjoin(".heredoc", fileno);
	free (fileno);
	fd = open(file, O_WRONLY | O_RDONLY | O_CREAT, 0777);
	get_doc_argz(fd, lim);
	replace_hdoc(data, file, z);
	unlinkz(file);
	close (fd);
}

void	fake_prep_hdoc(char *lim)
{
	char	*buf;

	while (1)
	{
		ft_putstr_fd(">", 1);
		buf = get_next_line(0);
		if (ft_strncmp(buf, lim, ft_strlen(lim)) == 0
			&& ft_strlen(buf) == ft_strlen(lim))
		{
			free (buf);
			return ;
		}
		free (buf);
	}
}

void	hdoc_scan(t_data *data)
{
	int		z;
	char	*lim;

	z = 0;
	while (data->line[z])
	{
		if (data->line[z] == '<'
			&& valid_hd(data->line, z) == 1)
		{
			lim = hdoc_limit(data->line, z);
			if (check_if_used(data->line, z, end_of_cmd(data->line, z)) == 1)
				prep_hdoc(data, z, lim);
			else
			{
				fake_prep_hdoc(lim);
				trim_hdoc(data->line, z);
			}
			free (lim);
		}
		z++;
	}
}
