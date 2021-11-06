TARGET = libkevas.a

CC = clang
CFLAGS = -std=c99 -Wall -Wextra -Werror -g -I ./include
AR = ar rcs
RM = rm -f

SRCS = source/entry.c source/hash.c source/kevas.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(AR) $(TARGET) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(TARGET)

.PHONY: all clean fclean
