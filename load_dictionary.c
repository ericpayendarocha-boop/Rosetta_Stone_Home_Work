/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_dictionary.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ericpayen </var/spool/mail/ericpayen>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 08:58:23 by ericpayen         #+#    #+#             */
/*   Updated: 2026/10/18 10:56:40 by ericpayen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rosetta.h"

void	save_entry(t_dict *d, char *nb_buf, int n_idx, int t_idx)
{
	int	p;
	int	v;
	int	c;

	p = 0;
	v = 0;
	c = d->loaded_exceptions_count;
	d->tab_textes[c][t_idx] = '\0';
	nb_buf[n_idx] = '\0';
	compute_power_and_value(nb_buf, n_idx, &p, &v);
	d->tab_powers[c] = p;
	d->tab_values[c] = v;
	d->loaded_exceptions_count++;
}

void	parse_char(t_dict *d, char c, char *buf, t_parse *p)
{
	int	curr;

	curr = d->loaded_exceptions_count;
	if (p->mode == 0)
	{
		if (c == ':')
		{
			buf[p->n_idx] = '\0';
			p->mode = 1;
			p->has_colon = 1;
		}
		else if (c >= '0' && c <= '9' && p->n_idx < 63)
			buf[p->n_idx++] = c;
	}
	else if (p->mode == 1 && p->t_idx < MAX_STR_LEN - 1)
	{
		if (p->t_idx > 0 || (c != ' ' && c != '\t'))
			d->tab_textes[curr][p->t_idx++] = c;
	}
}

static int	process_char(t_dict *d, char c, char *num_buf, t_parse *p)
{
	if (c == '\n' || c == '\r')
		return (reset_or_save(d, num_buf, p));
	if (p->mode == 0 && (c == ' ' || c == '\t'))
		return (1);
	parse_char(d, c, num_buf, p);
	return (1);
}

int	load_dictionary_from_file(t_dict *d, const char *filename)
{
	int		fd;
	char	c;
	char	num_buf[64];
	t_parse	p;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (-1);
	d->loaded_exceptions_count = 0;
	p.mode = 0;
	p.n_idx = 0;
	p.t_idx = 0;
	p.has_colon = 0;
	while (read(fd, &c, 1) > 0 && d->loaded_exceptions_count < MAX_EXCEPTIONS)
	{
		if (process_char(d, c, num_buf, &p) == -1)
			return (-1);
	}
	close(fd);
	return (d->loaded_exceptions_count);
}
