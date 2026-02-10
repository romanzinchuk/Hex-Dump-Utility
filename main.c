#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h> // Standard integer types

#define BYTES_PER_LINE 16

int main(int argc, char *argv[]) {
    // 1. Check if user provided a filename
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    // 2. Open file in Binary Read mode
    FILE *file = fopen(argv[1], "rb");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open file '%s'.\n", argv[1]);
        return 1;
    }

    uint8_t buffer[BYTES_PER_LINE];
    size_t bytesRead;
    unsigned int offset = 0;

    printf("Offset    Hex Bytes                                       ASCII\n");
    printf("----------------------------------------------------------------------\n");

    // 3. Read file chunk by chunk
    while ((bytesRead = fread(buffer, 1, BYTES_PER_LINE, file)) > 0) {
        
        // Print Offset (e.g., 00000010)
        printf("%08X  ", offset);

        // Print Hexadecimal representation
        for (int i = 0; i < BYTES_PER_LINE; i++) {
            // Add extra space after 8th byte for readability (canonical hexdump style)
            if (i == 8) printf(" "); 

            if (i < bytesRead) {
                printf("%02X ", buffer[i]);
            } else {
                printf("   "); // Padding for incomplete lines
            }
        }

        printf(" |");

        // Print ASCII representation
        for (int i = 0; i < bytesRead; i++) {
            if (isprint(buffer[i])) {
                printf("%c", buffer[i]);
            } else {
                printf("."); // Replace non-printable chars with dot
            }
        }

        printf("|\n");
        offset += BYTES_PER_LINE;
    }

    fclose(file);
    return 0;
}