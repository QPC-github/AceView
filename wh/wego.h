#ifndef WEGO_H
#define WEGO_H

/*
************************************************************************
*** wego - an easy library for simple SMP/multithreading in C
*** header restricted to the few functions needed to run
*** a multi htreaded code synchronized by channels
*** see wh/channel.h and wh/remote_channel.h for details
************************************************************************
* $Header: /home/mieg/aa/CVS_ACEVIEW/ace/wh/wego.h,v 1.15 2017/02/20 01:27:43 mieg Exp $
*/
#include <errno.h>

void wego_init (void) ;
/*
* You must call wego_init() (or wego_max_threads which calls wego_init)
* before you use any of the other functions.
* Nothing bad happens if you call it more than once.  For example, if
* your program uses two libraries that depend on wego, each library
* can call wego_init().
*/
void wego_max_threads (int max_threads) ;

/*
 * calls wego_init()
* max_threads() tells the library how many concurrently running
* threads it may use. This limit is on RUNNING threads; the library 
* WILL create more threads, but they will not all run concurrently.
*
* The limit will be observed if you call this function before any
* tasks are started.  If you call again wego_init with a new limit,
* the library may not observe the new limit for some time.
*/

/* logging messages in a serialized way
 * printing to stderr in parallelized threads does not work, the
 * messages may be mixed up
 * The following method uses channeles to garantee a reasonable output
 */
void wego_log (const char *text) ;  /* export text to a serialized channel */
void wego_flush (void) ;      /* flushes the wego_log channel on stderr */

/* launching parallel threads
 * synchronized by channels
 * vp is a pointer to a structure of type TYPE
 * the content of vp is passed by value
 * so it must be initialsed before the call to wego_go
 */
void wego_go_ (void(*f)(void *vp), void *vp, int size) ;
#define  wego_go(_f,_vp,_TYPE) wego_go_(_f,_vp,sizeof(_TYPE))

/* example, launching a parallel thread executing the function f
 * look at wchannel/ in *.h to learn how to synchronize f using channels
 *
   typedef struct tStruct { int x, y, z ;} T ;
   void f (void *)
    {
      T *t = (T*) vp ;

      ...
   
      wego_log ("hello world") ; // serialized access to stderr
      return ;
    }

   int main () 
    {
      T t ;
      wego_init () ;      
      t.x = 1  ; t.y = 2 ; t.z = 3 ;  // initialize t before calling wego_go
      wego_go (f, &t, T) ; // arguments are passed by value inside the T structure

      ....

      wego_flush () ;  // will flush the wego-log
      return 0 ;
    }
*/

/*
************************************************************************
*** end of file
************************************************************************
*/

#endif

