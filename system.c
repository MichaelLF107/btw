#include "system.h"
#include "colors.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/utsname.h>

void print_OS(char *os) {
  FILE *os_release = fopen("/etc/os-release", "r");
  if (os_release == NULL) {
    printf("error opening /etc/os-release\n");
    return;
  }

  char line[256];
  while (fgets(line, sizeof(line), os_release)) {
    if (strstr(line, "PRETTY_NAME") != NULL) {
      char *start = strchr(line, '"') + 1;
      char *end = strchr(start, '"');
      if (end != NULL) {
        *end = '\0';
      }
      os += sprintf(os, "%s%sOS:%s %s%s%s", RESET, GRN, RESET, CYN, start, RESET);
      break;
    }
  }
}

void print_kernel(char *kernel) {
  struct utsname unameData;

  uname(&unameData);

  kernel += sprintf(kernel, "%s%sKernel:%s %s%s%s", RESET, GRN, RESET, CYN, unameData.release, RESET);
}

void print_uptime(char *uptime) {
  FILE *uptime_file = fopen("/proc/uptime", "r");
  if (uptime_file == NULL) {
    printf("error opening /proc/uptime\n");
    return;
  }

  double uptime_seconds;
  fscanf(uptime_file, "%lf", &uptime_seconds);
  fclose(uptime_file);

  int days = uptime_seconds / 86400;
  int hours = (uptime_seconds - days * 86400) / 3600;
  int minutes = (uptime_seconds - days * 86400 - hours * 3600) / 60;

  uptime += sprintf(uptime, "%s%sUptime:%s%s %d days, %d hours, %d minutes%s", RESET, GRN, RESET, CYN, days, hours, minutes, RESET);
}

void print_shell(char *shell) {
  char *shell_path = getenv("SHELL");
  if (shell_path == NULL) {
    printf("error getting shell path\n");
    return;
  }

  char *shell_name = strrchr(shell_path, '/');
  if (shell_name == NULL) {
    printf("error getting shell name\n");
    return;
  }

  shell += sprintf(shell, "%s%sShell:%s %s%s%s", RESET, GRN, RESET, CYN, shell_name + 1, RESET);
}