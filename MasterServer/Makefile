all: http_server http_client

http_server:
	gcc -o http_server http_server.c

http_client:
	gcc -o http_client http_client.c

.PHONY: clean

clean:
	rm http_server http_client
