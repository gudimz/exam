#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>

int id[64 * 1024];
int max, nextId;
fd_set active, readyRead, readyWrite;
char str[42 * 4096], bufRead[42 * 4096], bufWrite[42 * 4097];

void fatal_error(char* message) {
	write(2, message, strlen(message));
	exit(1);
}

void send_all(int clientSocket) {
	for (int s = 0; s <= max; s++) {
		if (FD_ISSET(s, &readyWrite) && s != clientSocket) {
			send(s, bufWrite, strlen(bufWrite), 0);
		}
	}
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		fatal_error("Wrong number of arguments\n");
	}
	int port = atoi(argv[1]);
	bzero(&id, sizeof(id));
	FD_ZERO(&active);
	int servSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (servSocket < 0) {
		fatal_error("Fatal error\n");
	}

	max = servSocket;
	FD_SET(servSocket, &active);

	struct sockaddr_in addr;
	socklen_t lenAddr = sizeof(addr);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	addr.sin_port = htons(port);

	if (bind(servSocket, (const struct sockaddr *)&addr, lenAddr) < 0) {
		fatal_error("Fatal error\n");
	}
	if (listen(servSocket, 128) < 0) {
		fatal_error("Fatal error\n");
	}

	while (21) {
		readyRead = readyWrite = active;
		if (select(max + 1, &readyRead, &readyWrite, NULL, NULL) < 0) {
			continue;
		}
		for (int s = 0; s <= max; s++) {
			if (FD_ISSET(s, &readyRead) && s == servSocket) {
				int clientSocket = accept(servSocket, (struct sockaddr *)&addr, &lenAddr);
				if (clientSocket < 0) {
					continue;
				}
				max = (clientSocket > max) ? clientSocket : max;
				id[clientSocket] = nextId++;
				FD_SET(clientSocket, &active);
				sprintf(bufWrite, "server: client %d just arrived\n", id[clientSocket]);
				send_all(clientSocket);
				break;
			}
			if (FD_ISSET(s, &readyRead) && s != servSocket) {
				int res = recv(s, bufRead, strlen(bufRead), 0);
				if (res <= 0) {
					sprintf(bufWrite, "server: client %d just left\n", id[s]);
					send_all(s);
					FD_CLR(s,&active);
					close(s);
					break;
				} else {
					for (int i = 0, j = 0; i < res; i++, j++) {
						str[j] = bufRead[i];
						if (str[j] == '\n') {
							str[j] = '\0';
							sprintf(bufWrite, "client %d: %s\n", id[s], str);
							send_all(s);
							j = -1;
						}
					}
				}
			}
		}
	}
}