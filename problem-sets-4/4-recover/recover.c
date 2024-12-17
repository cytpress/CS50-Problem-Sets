#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("one pic only\n");
        return 1;
    }
    // create a pointer call memory_card, point to the argv[1]
    FILE *memory_card = fopen(argv[1], "r");

    // allocate 512 blocks for the fread usage
    uint8_t buffer[512];

    // used for sprintf
    int counter = 0;

    // jpgname = 00i.jpg + NULL == 8 bytes
    char jpg[8];

    // initialize jpg found
    bool jpg_found = false;

    //initialize *img
    FILE *img = NULL;

    while (fread(buffer, 1, 512, memory_card) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] >= 0xe0 && buffer[3] <= 0xef)
        {
            jpg_found = true;
            if (counter == 0)
            {
                // https://www.runoob.com/cprogramming/c-function-sprintf.html
                // int sprintf(char *str, const char *format, ...)
                // print char *format to *str
                //%03i means print to at least three "0" but the replace last digit("i") to counter
                sprintf(jpg, "%03i.jpg", counter);
                img = fopen(jpg, "w");
                fwrite(buffer, 1, 512, img);
                counter++;
                jpg_found = false;
            }
            else
            {
                fclose(img);
                sprintf(jpg, "%03i.jpg", counter);
                img = fopen(jpg, "w");
                fwrite(buffer, 1, 512, img);
                counter++;
                jpg_found = false;
            }
        }
        else if (counter != 0)
        {
            fwrite(buffer, 1, 512, img);
        }
    }
    fclose(img);
    fclose(memory_card);
}
