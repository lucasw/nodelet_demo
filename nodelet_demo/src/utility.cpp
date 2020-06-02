/**
 * Copyright 2018 Lucas Walter
 * This code is adapted from an example at:
 * http://brokestream.com/procstat.html
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int get_cpu_id()
{
  /* Get the the current process' stat file from the proc filesystem */
  FILE* procfile = fopen("/proc/self/stat", "r");
  const u_int64_t kToRead = 8192;
  char buffer[kToRead];
  int read = fread(buffer, sizeof(char), kToRead, procfile);
  fclose(procfile);

  // TODO(lucasw) change to strtok_r
  // Field with index 38 (zero-based counting) is the one we want
  char* line = strtok(buffer, " ");
  for (int i = 1; i < 38; i++)
  {
    line = strtok(NULL, " ");
  }

  line = strtok(NULL, " ");
  int cpu_id = atoi(line);
  return cpu_id;
}
