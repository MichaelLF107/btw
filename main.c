#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "host.h"
#include "cpu.h"
#include "system.h"
#include "colors.h"

void replace_substring(char *string, const char *substring, const char *replacement) {
  char *pos = strstr(string, substring);
  if (pos != NULL) {
    size_t subLen = strlen(substring);
    size_t replaceLen = strlen(replacement);
    memmove(pos + replaceLen, pos + subLen, strlen(pos + subLen) + 1);
    memcpy(pos, replacement, replaceLen);
  }
}

int main() {
  char username[256];
  char path[256];
  char host[256];
  char divider[256];
  char os[256];
  char kernel[256];
  char uptime[256];
  char shell[256];
  char cpu[256];
  char memory[256];
  char gpu[256];

  char line[256];

  getlogin_r(username, sizeof(username));

  snprintf(path, sizeof(path), "/home/%s/.config/ascii.conf", username);
  FILE *config = fopen(path, "ab+");
  if (config == NULL) {
    printf("error opening %s\n", path);
    return 1;
  }

  print_host_info(&host, &divider);
  print_OS(&os);
  print_kernel(&kernel);
  print_uptime(&uptime);
  print_shell(&shell);
  print_cpu_info(&cpu);
  print_memory_info(&memory);
  print_gpu_info(&gpu);

  while (fgets(line, sizeof(line), config)) {
    replace_substring(line, "!!host!!", host);
    replace_substring(line, "!!divider!!", divider);
    replace_substring(line, "!!os!!", os);
    replace_substring(line, "!!kernel!!", kernel);
    replace_substring(line, "!!uptime!!", uptime);
    replace_substring(line, "!!shell!!", shell);
    replace_substring(line, "!!cpu!!", cpu);
    replace_substring(line, "!!memory!!", memory);
    replace_substring(line, "!!gpu!!", gpu);
    printf("%s%s", BLU, line);
  }

  fclose(config);

  return 0;
}