/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 15:10:59 by adorigo           #+#    #+#             */
/*   Updated: 2020/03/26 10:39:05 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <limits.h>
# include <sys/types.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

int					ft_atoi(const char *str);
char				*ft_itoa(int n);
char				*ft_itoa_base(long nbr, char *base, int b_len);
char				*ft_utoa_base(unsigned int n, char *base, int b_len);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
void				ft_bzero(void *s, unsigned int n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memset(void *b, int c, size_t len);

char				*ft_strrchr(const char *s, int c);
char				*ft_strnstr(const char *haystack, const char *needle,
					size_t len);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, unsigned int n);
size_t				ft_strlen(const char *src);
char				*ft_strcpy(char *s1, const char *s2);
char				*ft_strncpy(char *dest, const char *src, size_t n);
size_t				ft_strlcpy(char *dst, char const *src, size_t size);
char				*ft_strcat(char *s1, const char *s2);
char				*ft_strncat(char *s1, const char *s2, size_t n);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);
ssize_t				ft_strnbr(char *s);
char				*ft_strstr(const char *s1, const char *s2);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_substr(char const *s, unsigned int start, size_t len);
int					ft_numlen(int n, int minus);
char				**ft_split(char const *s, char c);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strnjoin(char const *s1, char const *s2, 
															ssize_t r_size);
int					ft_haschr(const char *s, int c);
char				*ft_strnew(size_t size);
int					ft_strlast(char const *str, char const *last);

void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);

int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint(int c);
int					ft_isspace(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);

int					ft_strfree(char **cache, int ret);
void				*ft_calloc(size_t count, size_t size);
char				*ft_strdup(const char *src);
char				*ft_strndup(const char *src, size_t n);
int					get_next_line(int fd, char **line);
int					ft_printf(const char *form, ...);


typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **alst, t_list *new);
void				ft_lstadd_back(t_list **alst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstclear(t_list **lst, void (*del)(void*));
void				ft_lstdelone(t_list *lst, void (*del)(void*));

#endif
