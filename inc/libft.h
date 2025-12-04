
#ifndef LIBFT_H
# define LIBFT_H

# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);

int			ft_tolower(int c);
int			ft_toupper(int c);

size_t		ft_strlen(const char *s);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup(const char *s);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *big, const char *little, size_t len);
char		*ft_strrchr(const char *s, int c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char *));

int			ft_atoi(const char *nptr);
char		*ft_itoa(int n);
char		**ft_split(char const *s, char c);

void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);

void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memset(void *s, int c, size_t n);

// GNL

# define REASONABLE_SIZE 50000000

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

typedef struct s_gnl
{
	char	*line;
	char	*temp;
	size_t	i;
}			t_gnl;

char		*get_next_line(int fd);
char		*gnl_read_process(int fd, t_gnl *gnl, char **buffer, size_t *loc);
t_gnl		gnl_process_buffer(t_gnl gnl, size_t loc, char *buf,
				size_t buf_len);
char		*gnl_handle_eof(t_gnl *gnl, char **buffer, size_t *loc,
				ssize_t read_b);

size_t		ft_strlen_gnl(const char *s);
char		*ft_strjoin_gnl(char *s1, char *s2);
void		*ft_memset_gnl(void *s, int c, size_t n);
void		*ft_calloc_gnl(size_t nmemb, size_t size);
char		*ft_substr_gnl(const char *s, unsigned int start, size_t len);
char		*ft_strdup_gnl(const char *s);

// FT_PRINTF

# include <stdarg.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

int			ft_printf(const char *format, ...);
int			error_handle(va_list *word);
int			print_word(char format, int *word_num);
int			handle_conversion(char format, va_list *word, int *word_num);

int			print_char(va_list *word, int *io_error);
int			print_str(va_list *word, int *io_error);
int			print_deci(va_list *word, int *io_error);
int			print_hex(va_list *word, int *io_error, char format);
int			print_unsigned(va_list *word, int *io_error);
int			print_address(va_list *word, int *io_error);

char		*ft_unltoa_base(uintptr_t num, int base, char alph_cap);
size_t		unllen_base(unsigned long n, int base);

char		*ft_unitoa_base(unsigned int n, int base, char alph_cap);
size_t		unintlen_base(unsigned int n, int base);

char		*ft_itoa_printf(int n);
size_t		intlen_gnl(int n);

#endif