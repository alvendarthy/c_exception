#ifndef C_TRY_CATCH_H
#define C_TRY_CATCH_H

#include <setjmp.h>
#include <stdlib.h>
#include <signal.h>
#if 0
#include <stdarg.h>
#include <execinfo.h>
#include <stdio.h>
#include <signal.h>
#include <iostream>
#include <string.h>
#endif

#define EXCEPT_DIV0 SIGFPE
#define EXCEPT_SEG  SIGSEGV
#define EXCEPT_USER SIGUSR1

struct ExceptFrame_s
{
        int     value;
        int     sig;
        jmp_buf env;
        int     flag;
};
typedef struct ExceptFrame_s ExceptFrame;


void frameReset(ExceptFrame * frame);

int frameIsDef(ExceptFrame * frame);

ExceptFrame * frameNew();


extern ExceptFrame* except_stack;

extern void Frame_SIGSEGV_handler(int sig);

#define THROW(val) do { \
        except_stack->value = val; \
        raise(SIGUSR1); \
    }while(0)

#define EXCEPT_V()  (except_stack->value)

#define TRY \
    except_stack->flag = sigsetjmp(except_stack->env,1);\
    if(!frameIsDef(except_stack)) \
    { \
      signal(SIGUSR1,Frame_SIGSEGV_handler); \
      signal(SIGSEGV,Frame_SIGSEGV_handler); \
      signal(SIGFPE,Frame_SIGSEGV_handler);  

#define CATCH(type) \
    }\
    else if(except_stack->sig == type)\
    {\
      frameReset(except_stack);

#define CATCH_ALL \
    } else { \
      frameReset(except_stack);

#define ENDTRY }

#endif
