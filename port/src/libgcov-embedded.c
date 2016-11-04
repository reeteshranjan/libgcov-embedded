/*
 * coverage-support.c
 *
 *  We need only few basic things from the article http://tinyurl.com/jkegjzh
 *  These are - static_init and the get_stackpointer
 */

#ifdef ENABLE_LIBGCOV_PORT

#include <stdio.h>
#include <stddef.h>
#include "libgcov-embedded.h"
#include "libgcov.h"

/* call the coverage initializers if not done by startup code */
void static_init(void) {
  void (**p)(void);
  extern uint32_t __init_array_start, __init_array_end; /* linker defined symbols, array of function pointers */
  uint32_t beg = (uint32_t)&__init_array_start;
  uint32_t end = (uint32_t)&__init_array_end;

  while(beg<end) {
    p = (void(**)(void))beg; /* get function pointer */
    (*p)(); /* call constructor */
    beg += sizeof(p); /* next pointer */
  }
}

/* Our stub for _exit that calls the gcov_exit */
void
_exit (int status)
{
  gcov_exit();
  for(;;){ }
}

#endif /* ENABLE_LIBGCOV_PORT */
