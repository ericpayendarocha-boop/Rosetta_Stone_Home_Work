/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ericpayen </var/spool/mail/ericpayen>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 18:10:00 by ericpayen         #+#    #+#             */
/*   Updated: 2026/10/18 16:10:22 by ericpayen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rosetta.h"

static void	assign_node_scales(t_entry *new_node, char *nb_buf, int n_idx)
{
	int	val;
	int	i;

	val = 0;
	i = -1;
	while (++i < n_idx && n_idx <= 3)
		val = (val * 10) + (nb_buf[i] - '0');
	new_node->value = val;
	new_node->triplet_count = 0;
	if (n_idx >= 4 && nb_buf[0] == '1')
	{
		new_node->value = -1;
		new_node->triplet_count = (n_idx - 1) / 3;
	}
}

void	save_entry(t_dict *d, char *nb_buf, int n_idx, int t_idx)
{
	t_entry	*new_node;

	if (d->arena_len + t_idx + 1 >= ARENA_SIZE)
	{
		d->error_state = 1;
		return ;
	}
	new_node = malloc(sizeof(t_entry));
	if (!new_node)
	{
		d->error_state = 1;
		return ;
	}
	d->text_arena[d->arena_len + t_idx] = '\0';
	new_node->text_offset = d->arena_len;
	d->arena_len += t_idx + 1;
	nb_buf[n_idx] = '\0';
	assign_node_scales(new_node, nb_buf, n_idx);
	new_node->next = d->head;
	d->head = new_node;
}
