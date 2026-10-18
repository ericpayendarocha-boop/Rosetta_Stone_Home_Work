/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_dictionary.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ericpayen </var/spool/mail/ericpayen>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 08:58:23 by ericpayen         #+#    #+#             */
/*   Updated: 2026/10/18 15:44:57 by ericpayen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rosetta.h"

int	reset_or_save(t_dict *d, char *num_buf, t_parse *p)
{
	if (p->n_idx > 0 || p->t_idx > 0)
	{
		if (!p->has_colon)
		{
			d->error_state = 1;
			return (-1);
		}
		if (p->mode == 1 && p->t_idx > 0)
			save_entry(d, num_buf, p->n_idx, p->t_idx);
	}
	p->mode = 0;
	p->n_idx = 0;
	p->t_idx = 0;
	p->has_colon = 0;
	return (1);
}

void	parse_char(t_dict *d, char c, char *buf, t_parse *p)
{
	if (p->mode == 0)
	{
		if (c == ':')
		{
			buf[p->n_idx] = '\0';
			p->mode = 1;
			p->has_colon = 1;
		}
		else if (c >= '0' && c <= '9' && p->n_idx < 120)
			buf[p->n_idx++] = c;
	}
	else if (p->mode == 1 && d->arena_len + p->t_idx < ARENA_SIZE - 2)
	{
		if (p->t_idx > 0 || (c != ' ' && c != '\t'))
		{
			d->text_arena[d->arena_len + p->t_idx] = c;
			p->t_idx++;
		}
	}
}

static void	read_dict_loop(int fd, t_dict *d, char *num_buf, t_parse *p)
{
	char	c;

	while (read(fd, &c, 1) > 0)
	{
		if (d->error_state != 0)
			break ;
		if (p->mode == 0 && (c == ' ' || c == '\t'))
			continue ;
		if (c == '\n' || c == '\r')
			reset_or_save(d, num_buf, p);
		else
			parse_char(d, c, num_buf, p);
	}
}

int	load_dictionary_from_file(t_dict *d, const char *filename)
{
	int		fd;
	char	num_buf[128];
	t_parse	p;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (-1);
	d->head = NULL;
	d->arena_len = 0;
	d->error_state = 0;
	p.mode = 0;
	p.n_idx = 0;
	p.t_idx = 0;
	p.has_colon = 0;
	read_dict_loop(fd, d, num_buf, &p);
	close(fd);
	if (d->error_state != 0)
	{
		free_dictionary(d);
		return (-1);
	}
	return (1);
}
