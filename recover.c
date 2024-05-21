#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./file_name");
        return 1;
    }
    // Open the forensic card image file in read-binary mode
    FILE *forensic_card_image = fopen(argv[1], "rb");
    if (forensic_card_image == NULL)
    {
        printf("Can't open file. try again!");
        return 1;
    }
    // Read card data to a buffer, in 512 chunks
    uint8_t buffer[512];
    int jpeg_count = 0;
    FILE *new_jpeg = NULL;
    // Read the card data in 512-byte chunks
    while (fread(buffer, sizeof(uint8_t), 512, forensic_card_image) == 512)
    {
        // Check for the start of a new JPEG file
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && ((buffer[3] & 0xf0) == 0xe0))
        {
            // If this is the first JPEG file
            if (jpeg_count == 0)
            {
                // Create a new JPEG file
                char jpeg_file_name[20];
                sprintf(jpeg_file_name, "%03i.jpg", jpeg_count);
                // open new file in "wb" mode and set new_jpeg to this file
                new_jpeg = fopen(jpeg_file_name, "wb");
                // make sure the new file opened successfully
                if (new_jpeg == NULL)
                {
                    printf("Error opening output file: %s \n", jpeg_file_name);
                    fclose(forensic_card_image);
                    return 1;
                }
            }
            // If it's not the first JPEG file
            else
            {
                // Close the previous JPEG file
                fclose(new_jpeg);
                // Create a new JPEG file
                char jpeg_file_name[20];
                sprintf(jpeg_file_name, "%03i.jpg", jpeg_count);
                // Open new one in 'wb' mode and set new jpeg to this file
                new_jpeg = fopen(jpeg_file_name, "wb");
                // make sure the new file opened successfully
                if (new_jpeg == NULL)
                {
                    printf("Error opening output file: %s \n", jpeg_file_name);
                    fclose(forensic_card_image);
                    return 1;
                }
            }
            // Write the current block of data to the new JPEG file
            fwrite(buffer, sizeof(uint8_t), 512, new_jpeg);
            jpeg_count++;
        }
        // If not start of jpeg, write non-jpeg data to the already open file
        else if (new_jpeg != NULL)
        {
            fwrite(buffer, sizeof(uint8_t), 512, new_jpeg);
        }
    }
    // close all files
    if (new_jpeg != NULL)
    {
        fclose(new_jpeg);
    }
    fclose(forensic_card_image);
    printf("Extracted %i JPEG files \n", jpeg_count);
    return 0;
}
