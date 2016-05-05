/* stdbool.h: ISO/IEC 9899:1999 (C99), section 7.16 */

/* Copyright (C) ARM Ltd., 2002
* All rights reserved
* RCS $Revision: 152541 $
* Checkin $Date: 2010-02-23 12:26:12 +0000 (Tue, 23 Feb 2010) $
* Revising $Author: drodgman $
*/

#ifndef __bool_true_false_are_defined
#define __bool_true_false_are_defined 1

  #ifndef __cplusplus /* In C++, 'bool', 'true' and 'false' and keywords */
    #define bool _Bool
    #define true 1
   #define TRUE true
    #define false 0
   #define FALSE false
  #else
    #ifdef __GNUC__
      /* GNU C++ supports direct inclusion of stdbool.h to provide C99
         compatibility by defining _Bool */
      #define _Bool bool
    #endif
  #endif

#endif /* __bool_true_false_are_defined */