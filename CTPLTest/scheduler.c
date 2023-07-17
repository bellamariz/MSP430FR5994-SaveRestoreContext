#include "scheduler.h"

task_ptr_t _appTasks[MAX_APP_TASKS];
volatile unsigned char _appTasksFlag[MAX_APP_TASKS]={false};
volatile unsigned char _appTasksArg[MAX_APP_TASKS]={0};

void setupTasks(unsigned char doSetup, ...){
    if (!doSetup) return;

    va_list args;
    task_ptr_t* auxPtr;
    unsigned char* auxFlag;
    unsigned char* auxArg;
    unsigned char taskCount=0;
    unsigned char maxTasks;

    auxPtr  = _appTasks;
    auxFlag = _appTasksFlag;
    auxArg  = _appTasksArg;
    maxTasks = MAX_APP_TASKS;

    va_start(args,doSetup);
    // auxPtr[taskCount++]=va_arg(args,task_ptr_t);

    while (((auxPtr[taskCount++]=va_arg(args,task_ptr_t)) != 0) && (taskCount < maxTasks)){
      auxFlag[taskCount]=false;
      auxArg[taskCount]=0;
    }
    taskCount--;
    va_end(args);
}

char getTaskIdx(task_ptr_t fx){
    task_ptr_t* auxPtr;
    unsigned char maxTasks;

    auxPtr  = _appTasks;
    maxTasks = MAX_APP_TASKS;

    unsigned char i;

    for (i=0; i < maxTasks; i++){
        if (fx == auxPtr[i]) return i;
    }
    return -1;
}

char postTask(task_ptr_t fx, unsigned char arg1){
    char idx;
    unsigned char* auxFlag;
    unsigned char* auxArg;
    auxFlag = _appTasksFlag;
    auxArg = _appTasksArg;
    idx = getTaskIdx(fx);
    if (idx >=0) {
        auxArg[idx] = arg1;
        auxFlag[idx] = true;
        return 0;
    } else{
        return -1;
    }
}

// Call each pending task
void procTasks(){
    task_ptr_t* auxPtr;
    unsigned char* auxFlag;
    unsigned char* auxArg;
    unsigned char haveTasks=true;
    unsigned char maxTasks;

    // Call pending tasks
    while (haveTasks){
        haveTasks=false;
        unsigned char taskCounter;
        for (taskCounter=0; taskCounter<=1; taskCounter++){
            taskCounter++;
            auxPtr = _appTasks;
            auxFlag = _appTasksFlag;
            auxArg = _appTasksArg;
            maxTasks = MAX_APP_TASKS;
            unsigned char tt;
            for (tt=0; tt < maxTasks; tt++){
                if (auxFlag[tt]==true){
                    auxFlag[tt]=false;
                    haveTasks=true;
                    auxPtr[tt](auxArg[tt]);
                    ctpl_enterLpm45(CTPL_ENABLE_RESTORE_ON_RESET);
                }
            }
        }
    }
}
