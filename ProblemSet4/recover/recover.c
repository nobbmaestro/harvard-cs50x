#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* Constant(s) definitions */
#define BLOCK_SIZE 512
#define SIGNATURE_BYTE_0 0xFF
#define SIGNATURE_BYTE_1 0xD8
#define SIGNATURE_BYTE_2 0xFF

/* Type(s) definition */
typedef uint8_t BYTE;

/* Helper(s) function prototypes */
bool check_jpeg_signature(int size, BYTE buffer[size]);
void scan_memory_area(FILE *area);
int recover_memory(char *name);

/* Main function */
int main(int argc, char *argv[])
{
    int status_flag;

    if (argc == 2)
    {
        status_flag = recover_memory(argv[1]);
        if (status_flag)
        {
            printf("Invalid file name\n");
        }
        else
        {
            printf("Done.\n");
        }
    }
    else
    {
        printf("Usage: ./recover IMAGE\n");
        status_flag = 1;
    }

    return status_flag;
}

/* Helper(s) function */
bool check_jpeg_signature(int size, BYTE buffer[size])
{
    bool match;
    int num_bytes = 3;

    /* Check for buffer size */
    if (num_bytes <= size)
    {
        /* Check for jpeg signature */
        match = ((buffer[0] == SIGNATURE_BYTE_0) && (buffer[1] == SIGNATURE_BYTE_1) && (buffer[2] == SIGNATURE_BYTE_2));
    }
    else
    {
        match = false;
    }

    return match;
}

void scan_memory_area(FILE *area)
{
    BYTE buffer[BLOCK_SIZE];
    FILE *p_curr_file = NULL;

    char curr_file[8];
    int num_files = 0;

    while (fread(&buffer, sizeof(BYTE), BLOCK_SIZE, area) == BLOCK_SIZE)
    {
        /* Check for JPEG signature */
        if (check_jpeg_signature(BLOCK_SIZE, buffer))
        {
            /* Check if file is open, close if pointer is not NULL */
            if (p_curr_file != NULL)
            {
                fclose(p_curr_file);
                p_curr_file = NULL;
            }

            /* Check if file is open, create new JPEG file if pointer is NULL */
            if (p_curr_file == NULL)
            {
                sprintf(curr_file, "%03d.jpg", num_files);
                p_curr_file = fopen(curr_file, "w");
                num_files++;
            }
        }

        /* If file is initialized, write current block to file */
        if (p_curr_file != NULL)
        {
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, p_curr_file);
        }
    }

    /* Check pointer, close file if not NULL */
    if (p_curr_file != NULL)
    {
        fclose(p_curr_file);
        p_curr_file = NULL;
    }
}

int recover_memory(char *name)
{
    int status_flag;

    FILE *file;
    file = fopen(name, "r");

    if (file == NULL)
    {
        status_flag = 1;
    }
    else
    {
        scan_memory_area(file);
        fclose(file);
        status_flag = 0;
    }

    return status_flag;
}
