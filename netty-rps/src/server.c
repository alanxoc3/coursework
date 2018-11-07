#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>

#include "server.h"

#define BACKLOG 10

static pthread_mutex_t mutex;

int main(int argc, char ** argv) {
	if (argc != 2) {
		fprintf(stderr, "usage: rps_server <port>\n");
		exit(1);
	}

	// Create the mutex.
	pthread_mutex_init(&mutex, NULL);

	// Connect to localhost.
	struct serv_connection * coninfo = connect_servinfo(argv[1]);
	printf("server: waiting for connections...\n");

	pthread_mutex_init(&mutex, NULL);

	while(1) {
		struct player p1 = { .rps_val = -1, .parent_sockfd = coninfo->sockfd };
		struct player p2 = { .rps_val = -1, .parent_sockfd = coninfo->sockfd };
		struct player_group pg1 = { .p1 = &p1, .p2 = &p2 };
		struct player_group pg2 = { .p1 = &p2, .p2 = &p1 };

		pthread_create(&p1.thread_id, NULL, player_connection_thread, &p1);
		pthread_create(&p2.thread_id, NULL, player_connection_thread, &p2);

		pthread_join(p1.thread_id, NULL);
		pthread_join(p2.thread_id, NULL);

		pthread_create(&p1.thread_id, NULL, player_send_thread, &pg1);
		pthread_create(&p2.thread_id, NULL, player_send_thread, &pg2);

		pthread_join(p1.thread_id, NULL);
		pthread_join(p2.thread_id, NULL);

		close(p1.sockfd);
		close(p2.sockfd);
	}

	pthread_mutex_destroy(&mutex);
	close(coninfo->sockfd);
	freeconinfo(coninfo);

	return 0;
}

struct serv_connection * connect_servinfo(const char * const port) {
	struct serv_connection * coninfo = malloc(sizeof(struct serv_connection));
	int yes=1;

	if ((coninfo->servinfo = get_servinfo(port)) == NULL) {
		freeconinfo(coninfo);
		exit(1);
	}

	int sockfd = 0;
	struct addrinfo * p;

	// here, we go through the possibilities.
	for(p = coninfo->servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype,
						p->ai_protocol)) == -1) {
			perror("server: socket");
			continue;
		}

		if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
			perror("setsockopt");
			exit(1);
		}

		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			perror("server: bind");
			continue;
		}

		break;
	}

	if (p == NULL) {
		perror("failed to connect");
		freeconinfo(coninfo);
		exit(1);
	}

	if (listen(sockfd, BACKLOG) == -1) {
		perror("listen");
		exit(1);
	}

	coninfo->loc = p;
	coninfo->sockfd = sockfd;

	return coninfo;
}

struct addrinfo * get_servinfo(const char * const port) {
	struct addrinfo hints, *servinfo;
	int rv;

	// Hints, for getaddrinfo
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;     // IPv4 or IPv6
	hints.ai_socktype = SOCK_STREAM; // TCP
	hints.ai_flags = AI_PASSIVE;     // Local IP

	// A list of search results based on the search criteria.
	if ((rv = getaddrinfo(NULL, port, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		return NULL;
	}

	return servinfo;
}

void *get_in_addr(struct sockaddr *sa) {
	if (sa->sa_family == AF_INET)
		return &(((struct sockaddr_in*)sa)->sin_addr);

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

void freeconinfo(struct serv_connection * coninfo) {
	freeaddrinfo(coninfo->servinfo);
	free(coninfo);
}

// -- for threading --
void * player_connection_thread(void *arg) {
	struct player * p = (struct player *) arg;

	while (1) {

		// Thes vars are really used for display type things.
		socklen_t sin_size;
		struct sockaddr_storage their_addr;
		char s[INET6_ADDRSTRLEN];
		sin_size = sizeof their_addr;

		// for recv
		int numbytes;
		char buf;

		// Create the connection.
		p->sockfd = accept(p->parent_sockfd, (struct sockaddr *) &their_addr, &sin_size);
		if (p->sockfd == -1) {
			pthread_mutex_lock(&mutex);
			perror("accept");
			pthread_mutex_unlock(&mutex);
			continue;
		}

		if ((numbytes = recv(p->sockfd, &buf, sizeof(char), 0)) == -1) {
			pthread_mutex_lock(&mutex);
			perror("recv");
			pthread_mutex_unlock(&mutex);
			close(p->sockfd);
			continue;
		}

		// Printing Connection.
		inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *) &their_addr), s, sizeof s);

		pthread_mutex_lock(&mutex);
		printf("server: got rps value from %s\n", s);
		p->rps_val = buf;
		pthread_mutex_unlock(&mutex);

		break;
	}
}

void *player_send_thread(void *arg) {
	struct player_group * pg = (struct player_group *) arg;
	char sending = calc_results_packet(pg->p1->rps_val, pg->p2->rps_val);

	// Send the results
	if (send(pg->p1->sockfd, &sending, sizeof(char), 0) == -1) {
		pthread_mutex_lock(&mutex);
		perror("send");
		pthread_mutex_unlock(&mutex);
	}
}

char calc_results_packet(char p1_val, char p2_val) {
	// 0 = lose, 1 = win, 2 = tie
	// 0 = rock, 1 = paper, 2 = scissors
	char result = 0;

	if (p1_val == ((p2_val + 1) % 3)) {
		result = 1;
	} else if (p1_val == p2_val) {
		result = 2;
	} // default condition is handled with initial 0 value.

	result <<= 2;

	// p2 then p1
	result |= (p2_val & 0x03);
	result <<= 2;
	result |= (p1_val & 0x03);

	return result;
}

