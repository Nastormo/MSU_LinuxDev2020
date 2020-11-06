#define _GNU_SOURCE
#include <dlfcn.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
 
typedef int (*orig_unlinkat_f_type)(int dirfd, const char *pathname, int flags);
extern int errno;

int unlinkat(int dirfd, const char *pathname, int flags)
{
    if(strstr(pathname, "FIX") != NULL)
    {
        errno = EPERM;
        return errno;
    }

    orig_unlinkat_f_type orig_unlinkat;
    orig_unlinkat = dlsym(RTLD_NEXT, "unlinkat");
    return orig_unlinkat(dirfd, pathname, flags);
}