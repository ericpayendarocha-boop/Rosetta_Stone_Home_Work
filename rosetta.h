/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rosetta.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ericpayen </var/spool/mail/ericpayen>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/18 08:41:14 by ericpayen         #+#    #+#             */
/*   Updated: 2026/10/18 10:58:11 by ericpayen        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ROSETTA_H
# define ROSETTA_H

# include <unistd.h>
# include <fcntl.h>

# define MAX_EXCEPTIONS 200
# define MAX_STR_LEN 64
# define OUT_BUF_SIZE 4096

typedef struct s_parse
{
	int		mode;
	int		n_idx;
	int		t_idx;
	int		has_colon;
}			t_parse;

typedef struct s_buf
{
	char	str[OUT_BUF_SIZE];
	int		len;
}			t_buf;

typedef struct s_dict
{
	int		tab_powers[MAX_EXCEPTIONS];
	int		tab_values[MAX_EXCEPTIONS];
	char	tab_textes[MAX_EXCEPTIONS][MAX_STR_LEN];
	int		loaded_exceptions_count;
	t_buf	out_buf;
}			t_dict;

void		print_dict_word(t_dict *dict, int index);
int			lookup_exception(t_dict *dict, int power, int value);
void		print_triplet_value(t_dict *dict, int n);
void		print_large_number(t_dict *dict, const char *num_str);
int			load_dictionary_from_file(t_dict *dict, const char *filename);
void		compute_power_and_value(const char *num, int len, int *p, int *v);
void		save_entry(t_dict *d, char *nb_buf, int n_idx, int t_idx);
void		parse_char(t_dict *d, char c, char *buf, t_parse *p);
int			reset_or_save(t_dict *d, char *num_buf, t_parse *p);
int			ft_strlen(const char *str);
int			check_input(int argc, char **argv, const char **path, char **val_str);

#endif
