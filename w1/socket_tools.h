#pragma once

#include <netdb.h>

struct addrinfo;

int create_dgram_socket(const char *address, const char *port, addrinfo *res_addr);
