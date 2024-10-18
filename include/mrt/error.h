/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 18:26:23 by rgramati          #+#    #+#             */
/*   Updated: 2024/08/25 16:58:39 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <mrtlib.h>

typedef enum e_mrt_errtype
{
	MRT_ERR_ALLOC = 2,
	MRT_ERR_MLX,
	MRT_ERR_FILE_NONE,
	MRT_ERR_FILE_EXTE,
	MRT_ERR_FILE_PERM,
	MRT_ERR_FILE_PROC,
	MRT_ERR_FMT_TYPE,
	MRT_ERR_FMT_CONFIG,
	MRT_ERR_FMT_DATA,
}	t_errtype;

typedef struct e_mrt_error
{
	t_errtype	type;
	void		*func;
}	t_error;

# define MRT_MSG_DATA_FMT	" < \033[38;2;128;128;128m%s\033[0m >\n"

# define MRT_MSG_ALLOC		"Allocation failed"
# define MRT_MSG_MLX		"Mlx initialization failed"
# define MRT_MSG_FILE_NONE	"No such file or directory"
# define MRT_MSG_FILE_EXTE	"Wrong file extension"
# define MRT_MSG_FILE_PERM	"File cant be opened"
# define MRT_MSG_FILE_PROC	"File handling failed"
# define MRT_MSG_FMT_TYPE	"Unknown object"
# define MRT_MSG_FMT_CONFIG	"Wrong scene configuration"
# define MRT_MSG_FMT_DATA	"Unknown data"

t_error
mrt_error_print(t_error type);

#endif
