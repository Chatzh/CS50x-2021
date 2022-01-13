#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    char filename[10];
    int file_count = 0;
    int first_file = 0;

    BYTE buffer[512];
    while (fread(buffer, sizeof(BYTE), 512, input))
    {
        // If it's first block of jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (first_file == 0)
            {
                sprintf(filename, "%03i.jpg", file_count);
                FILE *output = fopen(filename, "w");
                fwrite(buffer, sizeof(BYTE), 512, output);
                fclose(output);

                first_file++;
            }
            else
            {
                file_count++;

                sprintf(filename, "%03i.jpg", file_count);
                FILE *output = fopen(filename, "w");
                fwrite(buffer, sizeof(BYTE), 512, output);
                fclose(output);
            }
        }
        else
        {
            FILE *output_append = fopen(filename, "a");
            if (output_append != NULL)
            {
                fwrite(buffer, sizeof(BYTE), 512, output_append);
                fclose(output_append);
            }
        }
    }

    fclose(input);
}