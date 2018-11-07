#ifndef _CLIENT_H
#define _CLIENT_H

struct serv_connection {
	int sockfd;
	struct addrinfo *servinfo, *loc;
};

// freeing memory for the serv_connection
void freeconinfo(struct serv_connection * coninfo);

// ip version agnostic of inet address.
void *get_in_addr(struct sockaddr *sa);

// get the addrinfo linked list from the string.
struct addrinfo * get_servinfo(const char * const addr, const char * const port);

// get the server connection
struct serv_connection * connect_servinfo(struct addrinfo *servinfo);

// gets the text of the addr info.
void get_ip_text(const struct addrinfo * loc, char * text, size_t text_len);

enum command_codes {error = -1, rock, paper, scissors, quit, help};

void get_input(char * const buffer, const int max_length);
int digit_len(const int num);
void clear_input_buffer();
signed char parse_input(const char * const input);
void print_help();
void exec_rps(int rps_code, struct addrinfo * servinfo);
void display_rps_results(int lhs, int rhs, int pad);
void byte_to_rps(char byte, int * const p1, int * const p2, int * const win);

char * get_hand_line(int hand_ind, int row);
char * get_hand_line_mirrored(int hand_ind, int row);

// Here is some nice art work!
#define ART_LINE_HEIGHT 6
#define ART_LINE_WIDTH 19

char ART_NONE[ART_LINE_WIDTH] = "                  ";

char ART_ROCK[ART_LINE_HEIGHT][ART_LINE_WIDTH] = {
	"    _______       ",
	"---'   ____)      ",
	"      (_____)     ",
	" YOU  (_____)     ",
	"      (____)      ",
	"---.__(___)       "
};

char ART_PAPER[ART_LINE_HEIGHT][ART_LINE_WIDTH] = {
	"    ________      ",
	"---'    ____)____ ",
	"           ______)",
	" YOU      _______)",
	"         _______) ",
	"---.__________)   "
};

char ART_SCISSORS[ART_LINE_HEIGHT][ART_LINE_WIDTH] = {
	"    _______       ",
	"---'   ____)____  ",
	"          ______) ",
	" YOU   __________)",
	"      (____)      ",
	"---.__(___)       "
};

// Unfortunately, I need mirrors, because of the stupid parenthesis.
// Actually, it is probably better this way.
char ART_ROCK_MIRROR[ART_LINE_HEIGHT][ART_LINE_WIDTH] = {
	"       _______    ",
	"      (____   '---",
	"     (_____)      ",
	"     (_____) OPP  ",
	"      (____)      ",
	"       (___)__.---"
};

char ART_PAPER_MIRROR[ART_LINE_HEIGHT][ART_LINE_WIDTH] = {
	"      ________    ",
	" ____(____    '---",
	"(______           ",
	"(_______     OPP  ",
	" (_______         ",
	"   (__________.---"
};

char ART_SCISSORS_MIRROR[ART_LINE_HEIGHT][ART_LINE_WIDTH] = {
	"       _______    ",
	"  ____(____   '---",
	" (______          ",
	"(__________  OPP  ",
	"      (____)      ",
	"       (___)__.---"
};

#endif
