#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define BUFFER_SIZE 512

int main(int argc, char *argv[])
{
    //check usage
    if (argc != 2)
    {
        printf("Usage: ./recover image \n");
        return 1;
    }

    //Open file + make sure its a non-error'd openable file  (*file = file pointer)
    FILE *file = fopen(argv[1], "r");
    if (!file || file == NULL)
    {
        printf("TRY AGAIN-- Usage: ./recover image.file\n");
        return 1;
    }

    //create buffer
    unsigned char bufferBytes[BUFFER_SIZE];
    
    //create counter for images
    int fileCounter = 0;
    
    FILE* image = NULL;
    
    bool found_jpg = false;
    
//go through loop-ish but cancel if there are no more bytes to read
    while (fread(bufferBytes, BUFFER_SIZE, 1, file))
    {
        // check for Jpeg signature 4 digits
        if (bufferBytes[0] == 0xff &&   
            bufferBytes[1] == 0xd8 &&
            bufferBytes[2] == 0xff &&
        (bufferBytes[3] & 0xf0) == 0xe0)
        
        {
            if (found_jpg == true)
            {
                fclose(image);
            }
            
            else
            {
                found_jpg = true;
            }
            
            char filename[8];
            sprintf(filename, "%03d.jpg", fileCounter);
            image =fopen(filename, "a");
            fileCounter++;
        }

    if (found_jpg == true)
        {
            fwrite(&bufferBytes, BUFFER_SIZE, 1, image);
        }
    }
    fclose(file);
    fclose(image);
    return 0;
}

