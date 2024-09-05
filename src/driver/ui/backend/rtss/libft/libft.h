/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:16:35 by babonnet          #+#    #+#             */
/*   Updated: 2024/06/21 18:29:09 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Header file for 42 Libft project by babonnet.
   Copyright (C) 2024 babonnet.

This file is part of the 42 School Libft project.

The 42 Libft project is free software; you can redistribute it and/or modify
it under the terms of the babonnet General Public License as published by
the Free Software Foundation; either version 3 of the License, or
(at your option) any later version.

This Libft project is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
babonnet General Public License for more details.

You should have received a copy of the babonnet General Public License
along with this program.  If not, see <http://www.babonnet.org/licenses/>.
*/

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

# ifndef SHORT_MIN
#  define SHORT_MIN -32767
# endif

# ifndef SHORT_MAX
#  define SHORT_MAX 32767
# endif

# ifndef INT_MIN
#  define INT_MIN -2147483648
# endif

# ifndef INT_MAX
#  define INT_MAX 2147483647
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int					ft_isalpha(int c);
int					ft_isdigit(int num);
int					ft_isalnum(int i);
int					ft_isascii(int i);
int					ft_isprint(int i);
size_t				ft_strlen(const char *str);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strchr(const char *str, int c);
char				*ft_strrchr(const char *str, int c);
int					ft_strncmp(const char *first, const char *second,
						size_t length);
int					ft_strcmp(const char *first, const char *second);
void				*ft_memset(void *str, int c, size_t n);
void				*ft_memchr(const void *str, int c, size_t n);
void				ft_bzero(void *s, size_t n);
int					ft_memcmp(const void *ptr1, const void *ptr2, size_t num);
size_t				ft_strlcpy(char *dest, const char *src, unsigned int size);
size_t				ft_strlcat(char *dest, const char *src, unsigned int size);
char				*ft_strdup(const char *source);
void				*ft_memcpy(void *destination, const void *source,
						size_t num);
void				*ft_memmove(void *destination, const void *source,
						size_t num);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
int					ft_atoi(const char *str);
float				ft_atof(const char *str);
char				*ft_itoa(int n);
void				*ft_calloc(size_t nitems, size_t size);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_swap(int *a, int *b);
char				*ft_strcpy(char *dest, char *src);
char				*get_next_line(int fd);
long long			ft_atoll(const char *str);
void				free_strs(char **strs);
int					ft_isint(char *nb);
int					ft_strisnum(char *str);
int					ft_isspace(int c);
int					ft_atoi_base(char *nptr, int base);
long int			ft_strtol(char *nptr, char *base, int base_size);

t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

int					ft_printf(const char *format, ...);
double				ft_strtod(const char *str, char **endptr);

void				exit_message(int error_value, char *message);

#endif
