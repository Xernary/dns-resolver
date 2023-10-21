all: dns

dns: dns.c 
	gcc dns.c -Wall -o dns
