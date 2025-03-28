// Contains a number of convenience macros, which should be used whenever
// relevant.
//
// Defining macros here allows easy one-place modification of code to change
// behavior.

#ifndef GRACE_CORE_MACRO_H_
#define GRACE_CORE_MACRO_H_

#include <assert.h>
#include <stdio.h>

#define GRACE_ASSERT(condition, message) assert(condition&& message)

#define GRACE_TODO(message) assert(false && message)

#define GRACE_UNREACHABLE \
  assert(false && "UNREACHABLE: Control flow is forbidden on this path.");

#endif
