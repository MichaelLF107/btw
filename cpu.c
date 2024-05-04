#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "cpu.h"
#include "colors.h"

void print_cpu_info(char *cpu) {
  FILE *cpuinfo = fopen("/proc/cpuinfo", "r");
  if (cpuinfo == NULL) {
    printf("error opening /proc/cpuinfo\n");
    return;
  }

  char *cpuModel;

  char line[256];
  while (fgets(line, sizeof(line), cpuinfo)) {
    if (strstr(line, "model name") != NULL) {
      if (line[strlen(line) - 1] == '\n') {
        line[strlen(line) - 1] = '\0';
      }

      cpuModel = line + 13;
      break;
    }
  }

  fclose(cpuinfo);

  cpu += sprintf(cpu, "%s%sCPU: %s%s%s%s", RESET, GRN, RESET, CYN, cpuModel, RESET);
}

void print_gpu_info(char *gpu) {
    FILE *fp;
    char path[1035];

    fp = popen("lspci -k | grep -A 2 -E \"(VGA|3D)\"", "r");
    if (fp == NULL) {
        printf("Failed to run command\n" );
        exit(1);
    }

    while (fgets(path, sizeof(path), fp) != NULL) {
      if (strstr(path, "VGA compatible controller") != NULL) {
        if (path[strlen(path) - 1] == '\n') {
          path[strlen(path) - 1] = '\0';
        }

        gpu += sprintf(gpu, "%s%sGPU:%s%s %s%s", RESET, GRN, RESET, CYN, path + 35, RESET);
      }
    }

    pclose(fp);
}

void print_memory_info(char *memory) {
  FILE *meminfo = fopen("/proc/meminfo", "r");
  if (meminfo == NULL) {
    printf("error opening /proc/meminfo\n");
    return;
  }

  long totalMemory = 0;
  char line[256];
  while (fgets(line, sizeof(line), meminfo)) {
    if (strstr(line, "MemTotal:") != NULL) {
      sscanf(line, "MemTotal: %ld", &totalMemory);
      break;
    }
  }

  fclose(meminfo);

  totalMemory /= 1024;

  totalMemory /= 1024;

  memory += sprintf(memory, "%s%sRAM: %s%s%ldGB%s", RESET, GRN, RESET, CYN, totalMemory + 1, RESET);
}