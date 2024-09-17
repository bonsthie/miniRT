/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   __rtss.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bonsthie <bonsthie@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:31:04 by bonsthie          #+#    #+#             */
/*   Updated: 2024/09/11 16:31:10 by bonsthie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __RTSS_H
# define __RTSS_H

# include "htab.h"

struct s_rtss_lex_file;

char	*rtss_file_to_buffer(const char *filename);
char	**fuck_norminette(void);
void	**rtss_parser_function(void);
t_htab	*rtss_parse(struct s_rtss_lex_file file);

#endif /* __RTSS_H */
