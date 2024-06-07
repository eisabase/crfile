# Makefile
NAME=	crfile
VERSION=	1.0
DISTFILES=	crfile-src.tar.gz
LICENSE=	./LICENSE
PLIST_FILES=	usr/bin/crfile

all: clean do-test do-build

do-test:
	cc -c -Wall -Wextra -Wpedantic -g3 -Og -std=c99 *.c
do-build:
	cc -o crfile -pipe -O2 -std=c99 *.c
clean:
	-rm crfile *.o
install:
	cp ./crfile /usr/bin/crfile && rm crfile *.o
uninstall:
	rm /usr/bin/crfile
remove:
	rm /usr/bin/crfile
