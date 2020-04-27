default : linux.c ocw.pl
	chmod 644 ocw.pl
	cc -O3 -o linux linux.c
	cp ocw.pl ocw
	chmod 755 ocw

install : linux ocw
	cp linux /usr/local/bin/
	cp ocw /usr/local/bin/

clean :	linux
	rm linux
	rm ocw
