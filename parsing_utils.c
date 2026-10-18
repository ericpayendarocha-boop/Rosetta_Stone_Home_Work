/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ericpayen </var/spool/mail/ericpayen>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 08:59:55 by ericpayen         #+#    #+#             */
/*   Updated: 2026/10/18 15:24:56 by ericpayen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rosetta.h"

void	save_entry(t_dict *d, char *nb_buf, int n_idx, int t_idx);

int	reset_or_save(t_dict *d, char *num_buf, t_parse *p)
{
	if (p->n_idx > 0 || p->t_idx > 0)
	{
		if (!p->has_colon)
			return (-1);
		if (p->mode == 1 && p->t_idx > 0)
			save_entry(d, num_buf, p->n_idx, p->t_idx);
	}
	p->mode = 0;
	p->n_idx = 0;
	p->t_idx = 0;
	p->has_colon = 0;
	return (1);
}
