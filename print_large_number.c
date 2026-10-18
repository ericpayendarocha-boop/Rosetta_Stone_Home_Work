/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_large_number.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ericpayen </var/spool/mail/ericpayen>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 08:45:50 by ericpayen         #+#    #+#             */
/*   Updated: 2026/10/18 10:57:34 by ericpayen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rosetta.h"

static int	get_chunk_val(const char *s, int end, int len)
{
	int	val;
	int	start;

	val = 0;
	start = end - len;
	while (start < end)
	{
		val = (val * 10) + (s[start] - '0');
		start++;
	}
	return (val);
}

static int	process_chunk(t_dict *dict, int val, int power, int *pb)
{
	int	scale_idx;

	if (dict->loaded_exceptions_count == -1)
		return (-1);
	if (val > 0)
	{
		if (*pb && dict->out_buf.len < OUT_BUF_SIZE - 1)
			dict->out_buf.str[dict->out_buf.len++] = ' ';
		print_triplet_value(dict, val);
		if (power > 0)
		{
			scale_idx = lookup_exception(dict, power, 1);
			if (scale_idx == -1)
				return (-1);
			if (dict->out_buf.len < OUT_BUF_SIZE - 1)
				dict->out_buf.str[dict->out_buf.len++] = ' ';
			print_dict_word(dict, scale_idx);
		}
		*pb = 1;
	}
	return (0);
}

static int	split_and_print(t_dict *dict, const char *s, int total_len)
{
	int	pb;
	int	rem;
	int	c_len;
	int	curr_power;
	int	idx;

	pb = 0;
	rem = total_len % 3;
	curr_power = (total_len - 1) / 3;
	idx = 0;
	while (idx < total_len)
	{
		c_len = 3;
		if (idx == 0 && rem > 0)
			c_len = rem;
		if (process_chunk(dict, get_chunk_val(s, idx + c_len, c_len),
				curr_power, &pb) == -1)
			return (-1);
		idx += c_len;
		curr_power--;
	}
	return (0);
}

static void	handle_zero(t_dict *dict)
{
	int	idx;

	idx = lookup_exception(dict, 0, 0);
	if (idx != -1)
		print_dict_word(dict, idx);
	write(1, dict->out_buf.str, dict->out_buf.len);
	write(1, "\n", 1);
}

void	print_large_number(t_dict *dict, const char *num_str)
{
	int		len;

	dict->out_buf.len = 0;
	dict->out_buf.str[0] = '\0';
	len = ft_strlen(num_str);
	while (*num_str == '0' && len > 1)
	{
		num_str++;
		len--;
	}
	if (len == 1 && *num_str == '0')
	{
		handle_zero(dict);
		return ;
	}
	if (split_and_print(dict, num_str, len) == -1
		|| dict->loaded_exceptions_count == -1)
	{
		write(2, "Dict Error\n", 11);
		return ;
	}
	write(1, dict->out_buf.str, dict->out_buf.len);
	write(1, "\n", 1);
}
