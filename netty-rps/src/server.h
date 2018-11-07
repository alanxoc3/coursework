#ifndef _SERVER_H
#define _SERVER_H

struct serv_connection {
	int sockfd;
	struct addrinfo *servinfo, *loc;
};

// keeps track of which 
struct player {
	pthread_t thread_id;
	int rps_val;
	int sockfd;
	int parent_sockfd;
};

struct player_group {
	struct player * p1;
	struct player * p2;
};

void *get_in_addr(struct sockaddr *sa);
struct serv_connection * connect_servinfo(const char * const port);
struct addrinfo * get_servinfo(const char * const port);
void freeconinfo(struct serv_connection * coninfo);
char calc_results_packet(char p1_val, char p2_val);
void * player_connection_thread(void *arg);
void *player_send_thread(void *arg);

#endif

