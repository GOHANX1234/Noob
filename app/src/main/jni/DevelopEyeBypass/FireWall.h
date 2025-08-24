#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <android/log.h>
#include <time.h>

#define LOG_TAG "HQBLOCK"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN,  LOG_TAG, __VA_ARGS__)

const int blocked_ports[] = { 0, 443, 8080, 8443, 10012, 10014, 14006, 8012, 9006, 11006, 65535 };

typedef struct {
    char last_ip[64];
    int last_port;
    char last_lib[256];
    int blocked;
    char reason[128];
} HQBlockStatus;

HQBlockStatus g_hq_status = {"N/A", -1, "N/A", 0, "None"};

// === WRITE LOG TO FILE ===
void write_log(const char* tag, const char* msg) {
    FILE* fp = fopen("/sdcard/Nawar_log.txt", "a");
    if (fp) {
        time_t now = time(NULL);
        struct tm* t = localtime(&now);
        char time_str[64];
        strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", t);
        fprintf(fp, "[%s][%s] %s\n", time_str, tag, msg);
        fclose(fp);
    } else {
        __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, "Failed to write log: %s", strerror(errno));
    }
}


// === CHECK IP PRIVATE CLASS ===
bool is_private_ip(const char* ip) {
    if (!ip) return false;
    struct in_addr addr4;
    struct in6_addr addr6;
    
    if (inet_pton(AF_INET, ip, &addr4) == 1) {
        uint32_t ip_addr = ntohl(addr4.s_addr);

        if ((ip_addr >= 0x0A000000 && ip_addr <= 0x0AFFFFFF) ||    // 10.0.0.0 – 10.255.255.255
            (ip_addr >= 0xAC100000 && ip_addr <= 0xAC1FFFFF) ||    // 172.16.0.0 – 172.31.255.255
            (ip_addr >= 0xC0A80000 && ip_addr <= 0xC0A8FFFF)) {    // 192.168.0.0 – 192.168.255.255
            return true;
        }
    } else if (inet_pton(AF_INET6, ip, &addr6) == 1) {
        // IPv6 local addresses
        return (addr6.s6_addr[0] == 0xFE && (addr6.s6_addr[1] & 0xC0) == 0x80); // fe80::/10
    }
    return false;
}

// === KIỂM TRA PORT BLOCK ===
bool is_blocked_port(int port) {
    for (int i = 0; i < sizeof(blocked_ports) / sizeof(blocked_ports[0]); ++i) {
        if (port == blocked_ports[i]) return true;
    }
    return false;
}

// === KIỂM TRA IP LOCALHOST ===
bool is_localhost_ip(const char* ip) {
    return strcmp(ip, "127.0.0.1") == 0 || strcmp(ip, "::1") == 0 || strcmp(ip, "0.0.0.0") == 0 ||
           strncmp(ip, "localhost", 9) == 0;
}

// === CHECK LIB SHOULD BLOCK ===
bool should_block_lib(const char* lib) {
    if (!lib) return false;  // Check for null pointer
    const char* filename = strrchr(lib, '/');
    filename = filename ? filename + 1 : lib;
    return strcmp(filename, "libanogs.so") == 0 ||
           strcmp(filename, "libil2cpp.so") == 0 ||
           strcmp(filename, "libanort.so") == 0 ||
           strcmp(filename, "libGGP.so") == 0 ||
           strcmp(filename, "libmain.so") == 0 ||
           strcmp(filename, "libc.so") == 0 ||
           strcmp(filename, "libunity.so") == 0;
}

// === GET CALLING LIB ===
bool get_caller_lib(char* out_lib) {
    void* caller_addr = __builtin_return_address(0);
    if (!caller_addr) return false;  // Check for null pointer
    
    Dl_info info;
    if (dladdr(caller_addr, &info) && info.dli_fname) {
        strncpy(out_lib, info.dli_fname, 255);
        return true;
    }
    strcpy(out_lib, "Unknown");
    return false;
}

// === SOCKET HOOK ===
static int (*orig_socket)(int, int, int);
int hooked_socket(int domain, int type, int protocol) {
    return orig_socket(domain, type, protocol);
}
// === CONNECT HOOK ===
static int (*orig_connect)(int, const struct sockaddr*, socklen_t);
int hooked_connect(int sockfd, const struct sockaddr* addr, socklen_t addrlen) {
    if (!addr) return -1;  // Ensure addr is not NULL

    if (addr->sa_family == AF_INET || addr->sa_family == AF_INET6) {
        char ip[INET6_ADDRSTRLEN] = {0};
        int port = 0;

        if (addr->sa_family == AF_INET) {
            struct sockaddr_in* sin = (struct sockaddr_in*)addr;
            inet_ntop(AF_INET, &sin->sin_addr, ip, sizeof(ip));
            port = ntohs(sin->sin_port);
        } else {
            struct sockaddr_in6* sin6 = (struct sockaddr_in6*)addr;
            inet_ntop(AF_INET6, &sin6->sin6_addr, ip, sizeof(ip));
            port = ntohs(sin6->sin6_port);
        }

        char libName[256];
        if (!get_caller_lib(libName)) {
            return -1;  // Ensure libName is retrieved
        }

        bool block = false;
        const char* reason = "None";

        if (should_block_lib(libName)) {
            if (is_localhost_ip(ip)) {
                reason = "Localhost IP (Blocked)";
                block = true;
            } else if (is_private_ip(ip)) {
                reason = "Private IP Class (Blocked)";
                block = true;
            } else if (is_blocked_port(port)) {
                reason = "Blocked Port (Blocked)";
                block = true;
            }
        }

        if (block) {
            char logMsg[512];
            snprintf(logMsg, sizeof(logMsg), "%s:%d | Lib: %s | Status: BLOCKED | Reason: %s", 
                    ip, port, libName, reason);
            write_log("BLOCKED", logMsg);
            LOGW("%s", logMsg);

            strncpy(g_hq_status.last_ip, ip, sizeof(g_hq_status.last_ip));
            g_hq_status.last_port = port;
            strncpy(g_hq_status.last_lib, libName, sizeof(g_hq_status.last_lib));
            g_hq_status.blocked = 1;
            strncpy(g_hq_status.reason, reason, sizeof(g_hq_status.reason));

            errno = ECONNREFUSED;
            return -1;
        }
    }
    return orig_connect(sockfd, addr, addrlen);
}

// === GETADDRINFO HOOK ===
static int (*orig_getaddrinfo)(const char*, const char*, const struct addrinfo*, struct addrinfo**);
int hooked_getaddrinfo(const char *node, const char *service,
                      const struct addrinfo *hints,
                      struct addrinfo **res) {
    if (node && is_localhost_ip(node)) {
        char logMsg[512];
        snprintf(logMsg, sizeof(logMsg), "%s | Lib: DNS Resolve | Status: BLOCKED | Reason: Localhost DNS", node);
        write_log("BLOCKED_DOMAIN", logMsg);
        LOGW("%s", logMsg);

        strncpy(g_hq_status.last_ip, node, sizeof(g_hq_status.last_ip));
        g_hq_status.last_port = 0;
        strncpy(g_hq_status.last_lib, "DNS Block", sizeof(g_hq_status.last_lib));
        g_hq_status.blocked = 1;
        strncpy(g_hq_status.reason, "Blocked Localhost", sizeof(g_hq_status.reason));

        errno = EAI_FAIL;
        return EAI_FAIL;
    }
    return orig_getaddrinfo(node, service, hints, res);
}

// === KHỞI TẠO HQBLOCK ===
__attribute__((constructor))
void init_hqblock() {
    void* libc = dlopen("libc.so", RTLD_NOW);
    if (!libc) {
        LOGW("dlopen libc.so failed");
        return;
    }

    DobbyHook(dlsym(libc, "connect"), (void*)hooked_connect, (void**)&orig_connect);
    DobbyHook(dlsym(libc, "socket"), (void*)hooked_socket, (void**)&orig_socket);
    DobbyHook(dlsym(libc, "getaddrinfo"), (void*)hooked_getaddrinfo, (void**)&orig_getaddrinfo);

    write_log("INIT", "=== HQBLOCK ENABLED ===");
    write_log("INIT", "Blocking only libanogs.so, libi2cpp.so, libunity.so for Localhost, Private IP, and blocked Ports");
    LOGD("HQBLOCK active");
}
