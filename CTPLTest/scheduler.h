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

#ifndef MAX_APP_TASKS
#define MAX_APP_TASKS 10
#endif

typedef enum {app=0,vtimer} taskId_t;
typedef void (*task_ptr_t)(unsigned char);

void setupTasks(unsigned char doSetup, ...);
char getTaskIdx(task_ptr_t fx);
void postVTTaskById(unsigned char taskId);
char postTask(task_ptr_t fx, unsigned char arg1);
void procTasks();

#endif /* SCHEDULER_H_ */
