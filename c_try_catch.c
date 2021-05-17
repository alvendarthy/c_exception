#include <stdlib.h>
#include <stdarg.h>
#include <execinfo.h>
#include <stdio.h>
//#include <signal.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

#include "c_try_catch.h"

#define moduleonly static



// extern ExceptFrame* except_stack;
moduleonly void errorDump();

// extern global value
moduleonly ExceptFrame stack = {0};
ExceptFrame* except_stack = &stack;


void frameReset(ExceptFrame * frame)
{
	assert(frame != NULL);
    frame->value = 0;
    frame->sig = 0;
	frame->flag = 0;
	bzero(frame->env,sizeof(frame->env));
}

int frameIsDef(ExceptFrame * frame)
{
	assert(frame != NULL);
	return frame->flag;
}

ExceptFrame * frameNew()
{
	ExceptFrame * frame = malloc(sizeof(ExceptFrame));
	assert(frame != NULL);

	frameReset(frame);

	return frame;
}

void Frame_SIGSEGV_handler(int sig)
{
    except_stack->sig = sig;
    siglongjmp(except_stack->env,1);
}
