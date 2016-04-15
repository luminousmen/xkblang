CFLAGS+=        -Wall
LDADD=		-lX11

SRCS=		prog.c
OBJS=		$(SRCS:.c=.o)

all:		prog

prog:	$(OBJS)
	$(CC) $(CFLAGS) -o prog $(OBJS) $(LDADD)
