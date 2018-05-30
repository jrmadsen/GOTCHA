/*
This file is part of GOTCHA.  For copyright information see the COPYRIGHT
file in the top level directory, or at
https://github.com/LLNL/gotcha/blob/master/COPYRIGHT
This program is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License (as published by the Free
Software Foundation) version 2.1 dated February 1999.  This program is
distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
without even the IMPLIED WARRANTY OF MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE. See the terms and conditions of the GNU Lesser General Public License
for more details.  You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

#include "gotcha/gotcha_types.h"
#include "gotcha/gotcha.h"
#include "tool1.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

static char* retX_wrapper(char* x);

static gotcha_wrappee_handle_t origRetX_handle = 0x0;

#define NUM_IOFUNCS 1
struct gotcha_binding_t iofuncs[] = {
   { "retX",retX_wrapper,&origRetX_handle}
};

char* retX_wrapper(char* x){
  typeof(&retX_wrapper) origRetX = gotcha_get_wrappee(origRetX_handle);
  strcat(x,"t1=>");
 
  return origRetX ? (origRetX(x) ) : 0;
}

int init_tool1()
{
   enum gotcha_error_t result;

   result = gotcha_wrap(iofuncs, NUM_IOFUNCS, "tool1");
   if (result != GOTCHA_SUCCESS) {
      fprintf(stderr, "gotcha_wrap returned %d\n", (int) result);
      return -1;
   }
   return 0;
}
