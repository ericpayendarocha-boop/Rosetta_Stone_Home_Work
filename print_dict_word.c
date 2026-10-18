/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dict_word.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ericpayen </var/spool/mail/ericpayen>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 09:02:55 by ericpayen         #+#    #+#             */
/*   Updated: 2026/10/18 15:45:55 by ericpayen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rosetta.h"

void	print_dict_word(t_dict *dict, t_entry *node)
{
	int	i;
	int	offset;

	if (!node)
		return ;
	offset = node->text_offset;
	i = 0;
	while (dict->text_arena[offset + i] != '\0')
	{
		if (dict->out_buf.len < OUT_BUF_SIZE - 1)
		{
			dict->out_buf.str[dict->out_buf.len] = dict->text_arena[offset + i];
			dict->out_buf.len++;
		}
		i++;
	}
	dict->out_buf.str[dict->out_buf.len] = '\0';
}
