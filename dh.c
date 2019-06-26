/* 
    A simple client program for server.c, 
    performed Diffie-Hellman key exchange
    modify from lab 5 client.c

    Author:         Qini Zhang
    Student Number: 901051
    Login Name:     qiniz
    Date:           May, 2019
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#define G 15
#define P 97

// // calc a * b % p , avoid 64bit overflow
// static inline uint64_t mul_mod_p(uint64_t a, uint64_t b) {
// 	uint64_t m = 0;
// 	while(b) {
// 		if(b&1) {
// 			uint64_t t = P-a;
// 			if ( m >= t) {
// 				m -= t;
// 			} else {
// 				m += a;
// 			}
// 		}
// 		if (a >= P - a) {
// 			a = a * 2 - P;
// 		} else {
// 			a = a * 2;
// 		}
// 		b>>=1;
// 	}
// 	return m;
// }

// // mod: p
// static inline uint64_t power(int a, int b){
//     uint64_t t;
//     if(b == 1)
//         return a;
//     t = power(a,b/2);
//     if(b % 2 == 0)
//         return (t * t) % P;
//     else
//         return (((t * t) % P) * a) % P;
// }

// Function to compute a^m mod n
// This codde is adopt from Techie Delight open source teaching website
// for more inormation: 
// https://www.techiedelight.com/c-program-demonstrate-diffie-hellman-algorithm/

int compute(int a, int m, int n)
{
	int r;
	int y = 1;

	while (m > 0)
	{
		r = m % 2;

		// fast exponention 
		if (r == 1)
			y = (y*a) % n;
		a = a*a % n;

		m = m / 2;
	}

	return y;
}

int main(int argc, char ** argv)
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent * server;

    char buffer[256];

    if (argc < 3)
    {
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        exit(0);
    }

    portno = atoi(argv[2]);


    /* Translate host name into peer's IP address ;
     * This is name translation service by the operating system
     */
    server = gethostbyname(argv[1]);

    if (server == NULL)
    {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }

    /* Building data structures for socket */

    bzero((char *)&serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;

    bcopy(server->h_addr_list[0], 
                        (char *)&serv_addr.sin_addr.s_addr, server->h_length);

    serv_addr.sin_port = htons(portno);

    /* Create TCP socket -- active open
    * Preliminary steps: Setup: creation of active open socket
    */

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
    {
        perror("ERROR opening socket");
        exit(0);
    }

    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("ERROR connecting");
        exit(0);
    }

    /* 
        Do processing => exchange key!!!!!
    */
    char* username = "qiniz\n";
    n = write(sockfd, username, strlen(username));

    // get b from stdin:
    printf("Please enter the b value: ");

    // converted b from char to int:
    bzero(buffer, 256);
    fgets(buffer, 255, stdin);
    int b = atoi(buffer);

    // calculate client's public key:
    int client_pub_key = compute(G, b, P);
    bzero(buffer, 256);
    sprintf(buffer, "%d\n", client_pub_key);

    // send it to server side:
    n = write(sockfd, buffer, strlen(buffer));

    if (n < 0)
    {
        perror("ERROR writing to socket");
        exit(0);
    }

    // receive server's public key:
    bzero(buffer, 256);

    n = read(sockfd, buffer, 255);

    if (n < 0)
    {
        perror("ERROR reading from socket");
        exit(0);
    }
    int server_pub_key = atoi(buffer);
    // find (g^b)^a(mod p):
    int key = compute(server_pub_key, b, P);
    bzero(buffer, 256);
    sprintf(buffer, "%d\n", key);
    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0){
        perror("ERROR writing to socket");
        exit(0);
    }
    bzero(buffer, 256);

    n = read(sockfd, buffer, 255);

    if (n < 0)
    {
        perror("ERROR reading from socket");
        exit(0);
    }
    printf("%s\n", buffer);
    return 0;
}
