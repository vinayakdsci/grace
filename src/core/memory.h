#ifndef GRACE_CORE_MEMORY_H_
#define GRACE_CORE_MEMORY_H_

#include <stdio.h>
#include <stdlib.h>

static void *reallocate(void *ptr, size_t old_size, size_t new_size) {
  // Free the ptr if new size is 0. We assume that it was passed with this
  // intent in the first place.
  if (new_size == 0) {
    free(ptr);
    return NULL;
  }

  // If the pointer initially has size 0, realloc() will behave like malloc().
  void *result = realloc(ptr, new_size);
  if (!result) {
    // We have entered a bad state. realloc() returning NULL usually
    // indicates OOM.
    fprintf(stderr,
            "Could not resize pointer. System is possibly OUT OF MEMORY.");
    // Nothing much we can do except die here.
    exit(1);
  }

  return result;
}

#define ALLOCATE(type, length) \
  (type *)reallocate(NULL, 0, sizeof(type) * (length))

#define RESIZE_CAPACITY(old_capacity) ((capacity) < 8 ? 8 : (capacity) * 2)
#define RESIZE_ARRAY(type, ptr, old_size, new_size) \
  (type *)reallocate(ptr, sizeof(type) * (old_size), sizeof(type) * (new_size))

#define FREE(type, ptr) reallocate(ptr, sizeof(type), 0)
#define FREE_ARRAY(type, ptr, old_size) \
  reallocate(ptr, sizeof(type) * (old_size), 0)

#endif
