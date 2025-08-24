#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <dlfcn.h>

int blockcount = 0;
bool Firewall1 = false;

// Original connect function pointer
int (*original_connect)(int, const struct sockaddr *, socklen_t);

// Custom connect function to hook into libc.so
int my_connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    char ip[INET_ADDRSTRLEN];

    if (addr->sa_family == AF_INET) {
        struct sockaddr_in *addr_in = (struct sockaddr_in *)addr;
        inet_ntop(AF_INET, &addr_in->sin_addr, ip, sizeof(ip));

        if (Firewall1 &&
            (strcmp(ip, "202.81.119.7") == 0 ||
             strcmp(ip, "47.83.4.232") == 0 ||
             strcmp(ip, "808") == 0 ||
             strcmp(ip, "202.81.119.9") == 0 ||
             strcmp(ip, "443") == 0 ||
             strcmp(ip, "1004") == 0 ||
             strcmp(ip, "39699") == 0 ||
             strcmp(ip, "443") == 0 ||
             strcmp(ip, "900") == 0 ||
             strcmp(ip, "39699") == 0 ||
             strcmp(ip, "1.20.541.128") == 0)) {
            printf("Connection to %s blocked\n", ip);
            blockcount++;
            return -1; // Block connection
        }
    }

    // Check blocked hostnames if Firewall is enabled
    struct hostent *host = gethostbyaddr(&(((struct sockaddr_in*)addr)->sin_addr), sizeof(struct in_addr), AF_INET);
    if (Firewall1 && host && 
        (strcmp(host->h_name, ("dl.gmc.freefiremobile.com")) == 0 ||
         strcmp(host->h_name, ("ff.dr.grtc.garenanow.com")) == 0 ||
         strcmp(host->h_name, ("ff.sdk.grtc.garenanow.com")) == 0 ||
         strcmp(host->h_name, ("dl.ctlin.freefiremobile.com")) == 0 ||
         strcmp(host->h_name, ("5d9e13.dns.nextdns.io")) == 0 ||
         strcmp(host->h_name, ("dns.google.com")) == 0 ||
         strcmp(host->h_name, ("hszxfreefiree.xdnz.xyz")) == 0 ||
         strcmp(host->h_name, ("c7c1e5.dns.nextdns.io")) == 0 ||
         strcmp(host->h_name, ("dl.ctlin.freefiremobile.com")) == 0 ||
         strcmp(host->h_name, ("dl.ctlin.freefiremobile.com")) == 0 ||
         strcmp(host->h_name, ("dl.ctlin.freefiremobile.com")) == 0 ||
         strcmp(host->h_name, ("dl.ctlin.freefiremobile.com")) == 0 ||
         strcmp(host->h_name, ("dl.ctlin.freefiremobile.com")) == 0 ||
         strcmp(host->h_name, ("dl.ctlin.freefiremobile.com")) == 0 ||      
         strcmp(host->h_name, "dl.cvs.freefiremobile.com") == 0)) {
        printf("Connection to %s blocked\n", host->h_name);
        blockcount++;
        return -1;
    }

    return original_connect(sockfd, addr, addrlen);
}
