/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dict_word.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ericpayen </var/spool/mail/ericpayen>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 09:02:55 by ericpayen         #+#    #+#             */
/*   Updated: 2026/10/18 10:57:03 by ericpayen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dict_word.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ericpayen </var/spool/mail/ericpayen>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 09:02:55 by ericpayen         #+#    #+#             */
/*   Updated: 2026/10/18 09:32:00 by ericpayen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rosetta.h"

void	print_dict_word(t_dict *dict, int index)
{
	int	len;

	len = 0;
	if (index < 0 || index >= dict->loaded_exceptions_count)
		return ;
	while (dict->tab_textes[index][len] != '\0')
	{
		if (dict->out_buf.len < OUT_BUF_SIZE - 1)
		{
			dict->out_buf.str[dict->out_buf.len] = dict->tab_textes[index][len];
			dict->out_buf.len++;
		}
		len++;
	}
	dict->out_buf.str[dict->out_buf.len] = '\0';
}
