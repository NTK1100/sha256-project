#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sha256.h"   // sẽ tìm trong ../include nhờ flag -I

int main() {
    const char *msgs[] = {"", "abc", "hello world"};
    for (int i = 0; i < 3; i++) {
        const char *msg = msgs[i];
        BYTE out[SHA256_DIGEST_SIZE];
        sha256((BYTE*)msg, strlen(msg), out);
        printf("SHA256('%s') = ", msg);
        for (int j = 0; j < SHA256_DIGEST_SIZE; j++)
            printf("%02x", out[j]);
        printf("\n");
    }
    system("pause");
    return 0;
}