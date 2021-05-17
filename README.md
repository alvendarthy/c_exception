# C_exception
A C try-catch implementation.

## Supported exception Now.
- EXCEPT_DIV0: Div/0
- EXCEPT_SEG:  Segement Fault
- EXCEPT_USER: User Exception

# Example
```c
#include <stdio.h>
#include "c_try_catch.h"


int main(){
    printf("Let's go.\n");

    TRY
        char * a = NULL;
        *a = 'x';
    /*catch all exceptions: div 0 and segement falut*/
    CATCH_ALL
        /* segement fault catch */
        printf("exception!\n");
    ENDTRY


    TRY
        /* throw an exception manualy, with an int parameter. */
        THROW(1);
        /* this will not run*/
        int b = 1/ 0;

    /* Let's catch exception respectively */
    CATCH(EXCEPT_DIV0)
        printf("Div/0\n");
    CATCH( EXCEPT_SEG)
        printf("Segement Fault.\n");
    CATCH( EXCEPT_USER )
        /* EXCEPT_V() returns USER exception parameter. */
      	printf("User Exception %d\n", EXCEPT_V());
    ENDTRY
}

```
