prefix=/usr/local

CFLAGS+=	-Wall
LDADD=		-lX11

SRCS=		xkblang.c
OBJS=		$(SRCS:.c=.o)

all:		xkblang clean

install: xkblang
	install -m 0755 xkblang $(prefix)/bin

xkblang:	$(OBJS)
	$(CC) $(CFLAGS) -o xkblang $(OBJS) $(LDADD)

clean:
	rm $(OBJS)
