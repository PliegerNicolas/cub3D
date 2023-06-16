/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emis <emis@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:48:08 by emis              #+#    #+#             */
/*   Updated: 2023/03/12 16:11:51 by emis             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include "libftprintf.h"
# include "get_next_line_bonus.h"

// CONVERT //
int		ft_atoi(char *str);
char	*ft_itoa(int n);
int		ft_toupper(int c);
int		ft_tolower(int c);

// STRINGS //
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
size_t	ft_strlen(char *str);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_strdup(char *src);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjointab(int size, char **strs, char *sep);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
int		ft_strncmp(char *s1, char *s2, size_t n);
size_t	ft_strlcat(char *dest, char *src, size_t size);
size_t	ft_strlcpy(char *dest, char *src, size_t size);
char	**ft_split(char *str, char c);
char	**ft_splitset(char *str, char *charset);

// MEMORY //
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);

// OUTPUT //
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_memcmp(const void *s1, const void *s2, size_t n);

// LIST //
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

// CIRCULAR LIST //
typedef struct s_clist
{
	void			*cont;
	struct s_clist	*prev;
	struct s_clist	*next;
}	t_clist;

t_clist	*ft_clstnew(void *content);
void	ft_clstadd_front(t_clist **lst, t_clist *new);
int		ft_clstsize(t_clist *lst);
t_clist	*ft_clstlast(t_clist *lst);
void	ft_clstadd_back(t_clist **lst, t_clist *new);
void	ft_clstdelone(t_clist *lst, void (*del)(void *));
void	ft_clstclear(t_clist **lst, void (*del)(void *));
void	ft_clstiter(t_clist *lst, void (*f)(void *));
t_clist	*ft_clstmap(t_clist *lst, void *(*f)(void *), void (*del)(void *));

#endif
