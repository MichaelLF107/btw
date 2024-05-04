#include "host.h"
#include "colors.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>

void print_host_info(char *host, char *divider) {
  char *username = getlogin();
  char hostname[128];

  if (gethostname(hostname, sizeof(hostname)) != 0) {
    printf("error getting hostname\n");
    return;
  }

  if (username == NULL) {
    printf("error getting username\n");
    return;
  }

  size_t username_size = strlen(username);
  size_t hostname_size = strlen(hostname);

  size_t total_size = username_size + hostname_size + 2;
  char line[total_size];
  memset(line, '-', total_size - 1);
  line[total_size - 1] = '\0';

  host += sprintf(host, " %s%s%s%s@%s%s%s", RESET, BLU, username, RESET, CYN, hostname, RESET);
  divider += sprintf(divider, "%s%s<%s>%s", RESET, MAG, line, RESET);
}