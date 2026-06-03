NAME    = libft.a
CC      = cc
CFLAGS  = -Wall -Wextra -Werror 

SRCS    = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c \
ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c \
ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c \
ft_memcmp.c ft_strnstr.c ft_atoi.c ft_strdup.c ft_calloc.c ft_strjoin.c \
ft_substr.c ft_strtrim.c ft_split.c ft_strmapi.c ft_striteri.c \
ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
ft_itoa.c ft_add_str_in_dba.c ft_contain_char.c ft_dba_dup.c \
ft_dba_len.c ft_extract_var_path.c ft_free_before_i.c \
ft_free_dba.c ft_rm_str_in_dba.c ft_skip_space.c ft_iswhitespace.c \
ft_lstadd_front.c ft_isonly_space.c ft_lstiter.c ft_lstsize.c ft_strcmp.c 

OBJ_DIR = obj/
OBJS    = $(addprefix $(OBJ_DIR), $(SRCS:%.c=%.o))
RM      = rm -rf

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	@ar rcs $(NAME) $(OBJS)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: %.c libft.h
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re