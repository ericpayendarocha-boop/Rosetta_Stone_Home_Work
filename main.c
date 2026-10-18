/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ericpayen </var/spool/mail/ericpayen>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 08:42:14 by ericpayen         #+#    #+#             */
/*   Updated: 2026/10/18 10:56:51 by ericpayen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rosetta.h"

int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	main(int argc, char **argv)
{
	t_dict		dict;
	const char	*dict_path;
	char		*num_str;

	if (!check_input(argc, argv, &dict_path, &num_str))
	{
		write(2, "Error\n", 6);
		return (1);
	}
	if (load_dictionary_from_file(&dict, dict_path) <= 0)
	{
		write(2, "Dict Error\n", 11);
		return (1);
	}
	print_large_number(&dict, num_str);
	return (0);
}
