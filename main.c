#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main() {

    FILE *file = fopen("test.txt", "rb");
    if(file == NULL) {
        printf("Error: Could not open file. \n");
        return 1;
    }
        
    unsigned char buffer[16];
    size_t bytesRead;
    unsigned int offset = 0;

    printf("Offset    Hex Bytes                                       ASCII\n");
    printf("-----------------------------------------------------------------------\n");

    while((bytesRead = fread(buffer, 1, 16, file)) > 0) {
        printf("%08x  ", offset);

        for (int i = 0; i < 16; i++) {
            if (i < bytesRead) {
                printf(" %02X", buffer[i]);
            }
            else {
                printf("   ");
            }
        }

        printf(" | ");
        
        for (int i = 0; i < bytesRead; i++) {
            unsigned char c = buffer[i];

            if(isprint(c)) {
                printf("%c", c);
            } else {
                printf(".");
            }
        }

        printf("\n");
        offset += 16;
    }   

    fclose(file);
    return 0;
}