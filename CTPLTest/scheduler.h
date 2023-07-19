/*
 * scheduler.h
 *
 *  Created on: 13 de jul de 2023
 *      Author: AdmGistLab2
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctpl.h>
#include <msp430.h>

#ifndef MAX_APP_TASKS
#define MAX_APP_TASKS 1
#endif

typedef enum {app=0,vtimer} taskId_t;
typedef void (*task_ptr_t)(void);

void setupTasks(unsigned char doSetup, ...);
char getTaskIdx(task_ptr_t fx);
char postTask(task_ptr_t fx);
void procTasks();

#endif /* SCHEDULER_H_ */
