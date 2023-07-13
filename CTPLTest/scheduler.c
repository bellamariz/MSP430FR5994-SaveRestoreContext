#include <stdlib.h>
#include <stdio.h>

typedef struct {
  uint32_t delay;
  uint32_t period;
  uint8_t run;
  void (*exec)(void *handle);
  void *handle;
} tTask;


