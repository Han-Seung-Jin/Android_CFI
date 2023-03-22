#include <jni.h>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include "libhello-test.h"

__attribute__((visibility("default"))) void *alloc_memory(size_t sz1) {
    void *p=(void *)malloc(sz1);
    return p;
}
