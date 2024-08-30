/**
 * @file Loader.c
 * @brief XME File Loader for ECED3403 Assignment 1 Emulator
 *
 * This module contains functionality to read S-Record formatted files,
 * extracting and decoding necessary information such as record type,
 * data length, address and data. This information is used to populate
 * memory and setup the initial program counter (PC) for the emulator.
 *
 * Note: Only S0, S1, and S9 records are supported.
 *
 * This is part of the coursework for ECED3403 - Computer Architecture, Assignment 1.
 *
 * @author Omar Hameed
 * @date Last updated on June 16, 2023
 *
 * 
 */

#include <stdio.h>
#include "emulator.h"

unsigned char testing_input[MAXBufSize]; // Define testing_input variable

/*
 *   Purpose:
 *          Opens a .XME file and loads it into memory. If no file is provided via command-line
 *          arguments, it prompts the user for a file name. If the file fails to open, it allows
 *          for retry up to three times. It calls ReadFile() function for reading the file content.
 *  Parameters:
 *          int argc: number of strings pointed to by argv.
 *          char* argv[]: command-line arguments.
 */
int OpenLoadF(int argc, char* argv[]) {
    char* file_name;
    char buffer[MAX_FILE_NAME];
    FILE* in_file = NULL;
    int max_trials = 3;
    int trials = 0;

    while (trials < max_trials) {
        if (argc >= 2) {
            file_name = argv[1];
        }
        else {
            printf("Enter the name of the .XME file to read: ");
            scanf("%s", buffer);
            file_name = buffer;
        }
        size_t name_length = strlen(file_name);

        // Check if the file has the correct extension
        if (name_length < 5 || strcmp(&file_name[name_length - 4], ".xme") != 0) {
            printf("Error: Invalid file extension. The file should have a .xme extension, try again \n");

            trials++;
            continue;  // Continue to the next iteration of the loop
        }
        in_file = fopen(file_name, "r");
        if (in_file != NULL) {
            printf("XME File read successfully\n");
            break;  // Exit the loop since the file was successfully opened
        }
        else {
            printf("Failed to open the file, try again\n");
            trials++;
        }
    }

    if (trials == max_trials) {
        printf("Maximum number of trials reached.\n Exiting the program.\n");
        return 1;  // Return an error code
    }
    ReadFile(in_file);


    return 0;  // Return success
}