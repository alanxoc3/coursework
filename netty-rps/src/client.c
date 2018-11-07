#include <stdio.h>  // printf...
#include <stdlib.h> // malloc...
#include <string.h> // strcat...
#include <math.h>   // log10...
#include <assert.h>   // log10...

#include <unistd.h>
#include <errno.h> // for errors, might be optional.

#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <netdb.h>

#include "client.h"

// DISCLAIMER:
// 	I haven't done c in a while, but I wanted to do this in pure c. So good luck.

int main(int argc, char ** argv) {
	// Network info first.

	if (argc != 3) {
		fprintf(stderr, "usage: rps_client <hostname> <port>\n");
		exit(1);
	}
	
	// Get the connection information.
	struct addrinfo * servinfo;
	if ((servinfo = get_servinfo(argv[1], argv[2])) == NULL) {
		exit(1);
	}

	printf("Ready to play a game of rock paper scissors?\n");
	printf("------------- By: Alan Morgan --------------\n");
	print_help();

	// Set up vars.
	int loop = 1; 
	const int BUF_LEN = 10;
	char str[BUF_LEN];
	strcpy(str, "");

	signed char ret_code = 0;

	while(loop) {
		printf("> ");
		get_input(str, BUF_LEN);
		ret_code = parse_input(str);

		// Executing all the commands.
		switch(ret_code) {
			case quit:
				loop = 0;
				break;
			case help:
				print_help();
				break;
			case rock:
			case paper:
			case scissors:
				exec_rps(ret_code, servinfo);
				break;
			case error:
				printf("Command not recognized, type \"h\" for help.\n");
		}
	}

	freeaddrinfo(servinfo);

	return 0;
}

char * get_hand_line(int hand_ind, int row) {
	if (hand_ind == 0) return ART_ROCK[row];
	if (hand_ind == 1) return ART_PAPER[row];
	if (hand_ind == 2) return ART_SCISSORS[row];
	return ART_NONE;
}

char * get_hand_line_mirrored(int hand_ind, int row) {
	if (hand_ind == 0) return ART_ROCK_MIRROR[row];
	if (hand_ind == 1) return ART_PAPER_MIRROR[row];
	if (hand_ind == 2) return ART_SCISSORS_MIRROR[row];
	return ART_NONE;
}

// pad is the padding in between both hands.
void display_rps_results(int lhs, int rhs, int pad) {
	int j, i;
	for (j = 0; j < pad + (ART_LINE_WIDTH-1) * 2; ++j) { putchar('-'); }

	putchar('\n');

	for (i = 0; i < ART_LINE_HEIGHT; ++i) {
		char * lhs_line = get_hand_line(lhs, i);
		char * rhs_line = get_hand_line_mirrored(rhs, i);

		printf("%s", lhs_line);
		for (j = 0; j < pad; ++j) putchar(' ');
		printf("%s\n", rhs_line);
	}

	putchar('\n');
	for (j = 0; j < pad + (ART_LINE_WIDTH-1) * 2; ++j) { putchar('-'); } putchar('\n');
}

void print_help() {
	printf("      r = rock, p = paper, s = scissors\n");
	printf("            q = quit, h = help\n");
}

// Grabs input and gets rid of the buffer.
// Max length includes the null character.
void get_input(char * const input, int max_length) {
	max_length -= 1;

	int old_num_of_digits = digit_len(max_length);

	// +1 for null char.
	char * digit_str = malloc((old_num_of_digits + 1)*sizeof(char));

	// int to string
	const int new_num_of_digits = sprintf(digit_str, "%d", max_length);
	assert(new_num_of_digits == old_num_of_digits);

	// +3 for %, s, and null char.
	char * const format_str = malloc((new_num_of_digits+3)*sizeof(char));

	// %##s
	strcpy(format_str, "%");
	strcat(format_str, digit_str);
	strcat(format_str, "s");

	// finally get the input!
	scanf(format_str, input);

	clear_input_buffer();

	free(format_str);
	free(digit_str);
}

#define COMP_LEN 5
signed char parse_input(const char * const input) {
	// scissors is 9 chars (including null), only 5 commands.
	char compares[COMP_LEN][9] = { "rock", "paper", "scissors", "quit", "help" };
	char shortcut[COMP_LEN][2] = { "r", "p", "s", "q", "h" };
	int i;

	for (i = 0; i < COMP_LEN; ++i) {
		if (strcmp(input, shortcut[i]) == 0 || strcmp(input, compares[i]) == 0) {
			return i;
		}
	}

	return -1;
}
#undef COMP_LEN

// Works with negatives too!
int digit_len(const int num) {
	return (int)((floor(log10(abs(num)))+1 + (num < 0 ? 1 : 0))*sizeof(char));
}

void clear_input_buffer() {
	char c;
	for(c; (c = getchar()) != '\n' && c != EOF;);
}

// NETWORKING PORTION

// This is where the bulk of the networking is contained.
// 0 = rock, 1 = paper, 2 = scissors
void exec_rps(int rps_code, struct addrinfo * servinfo) {
	struct serv_connection * coninfo = connect_servinfo(servinfo);

	char buf;
	int numbytes;

	if (!coninfo) return;

	char s[INET6_ADDRSTRLEN];
	get_ip_text(coninfo->loc, s, sizeof s);

	char new_code = rps_code;

	if (send(coninfo->sockfd, &new_code, sizeof(char), 0) == -1) {
		perror("send");
	}

	printf("       finding opponent... ");
	fflush(stdout); // want the text on the screen!


	if ((numbytes = recv(coninfo->sockfd, &buf, sizeof(char), 0)) == -1) {
		perror("recv");

		close(coninfo->sockfd);
		freeconinfo(coninfo);

		exit(1);
	}

	printf("LET IT RIP!\n");

	int p1, p2, win;
	byte_to_rps(buf, &p1, &p2, &win);
	display_rps_results(p1, p2, 8);

	if (win == 1) printf("YOU WON!!!!!\n");
	else if (win == 2) printf("YOU tied.\n");
	else     printf("YOU lost :(\n");

	close(coninfo->sockfd);
	freeconinfo(coninfo);
}

// Converts the byte to the players.
// Since it is only 1 byte, we don't have to worry about endianness.
void byte_to_rps(char byte, int * const p1, int * const p2, int * const win) {
	*p1 = byte & 0x03;
	byte = byte >> 2;
	*p2 = byte & 0x03;
	byte = byte >> 2;
	*win = byte & 0x03;
}

void freeconinfo(struct serv_connection * coninfo) {
	free(coninfo);
}

void *get_in_addr(struct sockaddr *sa) {
	if (sa->sa_family == AF_INET)
		return &(((struct sockaddr_in*)sa)->sin_addr);

	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

struct addrinfo * get_servinfo(const char * const addr, const char * const port) {
	struct addrinfo hints, *servinfo;
	int rv;

	// Hints, for getaddrinfo
	memset(&hints, 0, sizeof hints);
	hints.ai_family   = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	// A list of search results based on the search criteria.
	if ((rv = getaddrinfo(addr, port, &hints, &servinfo)) != 0) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		// perror("gai"); // this would return a "no such file or directory."
		// so, not network related.
		return NULL;
	}

	return servinfo;
}

// If there is an error, the program simple exits, doesn't return errors.
struct serv_connection * connect_servinfo(struct addrinfo *servinfo) {
	struct serv_connection * coninfo = malloc(sizeof(struct serv_connection));
	coninfo->servinfo = servinfo;

	int sockfd = 0;
	struct addrinfo * p;

	// here, we go through the possibilities.
	for(p = coninfo->servinfo; p != NULL; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype,
						p->ai_protocol)) == -1) {
			continue;
		}

		if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			continue;
		}
		break;
	}

	if (p == NULL) {
		perror("failed to connect");
		freeconinfo(coninfo);
		return NULL;
	}

	coninfo->loc = p;
	coninfo->sockfd = sockfd;

	return coninfo;
}

void get_ip_text(const struct addrinfo * loc, char * text, size_t text_len) {
	inet_ntop(loc->ai_family, get_in_addr((struct sockaddr *)loc->ai_addr), text, text_len);
}
