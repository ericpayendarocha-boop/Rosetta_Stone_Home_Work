/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ericpayen </var/spool/mail/ericpayen>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 08:59:55 by ericpayen         #+#    #+#             */
/*   Updated: 2026/10/18 10:56:58 by ericpayen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rosetta.h"

void	compute_power_and_value(const char *num, int len, int *p, int *v)
{
	int	val;
	int	i;

	val = 0;
	i = 0;
	if (len < 3)
	{
		while (i < len)
			val = (val * 10) + (num[i++] - '0');
		*p = 0;
		*v = val;
		return ;
	}
	if (len == 3 && num[0] == '1' && num[1] == '0' && num[2] == '0')
	{
		*p = 0;
		*v = 100;
		return ;
	}
	*p = (len - 1) / 3;
	*v = 1;
}

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
