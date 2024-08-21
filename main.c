#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>




void ReadFile(FILE* in_file){
    char testing_input[256];
    int successfull_assignments;
    while(fgets(testing_input, 256,in_file ) != NULL){
        if (testing_input[0] != 'S'){
            printf("ERROR: %s IS Not a valid S-recored \n", testing_input);
        }
        else if (testing_input[1] != '0' && testing_input[1] !='1'&& testing_input[1] !='9'){
            printf("ERROR: %s IS Not a supported S-recored only S0, S1, S9\n", testing_input);
        }



        // s-record valid 
        printf("%s", testing_input);

        // s1| 2 byte length | 4byte adress | data  | checksum 
        int length; 
        int address_low;
        int address_high;
        sscanf(&testing_input[2], "%2x", &length);

        //char program_name[length -4-2];
        int data_length = (length*2) -6;
        unsigned int sum =0;
        unsigned int value1 ;
        int values_assigned;
        for (int i = 2; i<(length*2)+4; i =i+2){
            values_assigned = sscanf(&testing_input[i], "%2x", &value1);
            sum += value1;
           // value1 = 0;
        }

            if (sum == 255){
                printf("Check Sum Valid\n");
            }else if (sum != 255 ){
                printf("Error: Check Sum Error detected file corrupted\n");
                printf("  ========================CHECKSUM %02x\n ", sum);
                //exit(0);
            }



      /*for(int i=0; i<length; i++){
            unsigned int data[1];
            sscanf(&testing_input[i], "%2x", &data);
        }*/  
        if (testing_input[1] == '0'){
            // Display File Nom
            printf("S0 RECORED DETECTED: \n");
            //int data_length = (length*2) -6;
            char filename[data_length];
            unsigned int hex_filename_length;
            char *ascii_char = (char*)malloc(data_length + 1); // Allocate memory for ascii_char
            printf("FILE NAME: ");
            for (int i = 0; i<data_length; i=i+2){
                sscanf(&testing_input[8+i]  , "%2x", &ascii_char[i]);
                printf("%c", ascii_char[i]);
            }
            
            printf("\n");
            free(ascii_char);

        }

        else if (testing_input[1] == '1'){
            /*The program must extract the address of the first byte in the record. Subsequent
            data bytes are stored in contiguous locations. If there is already a value in a memory location, it must
            be overwritten.
            */
            printf("S1 RECORED DETECTED: \n");
            char data[data_length];
            unsigned int address_lo;
            unsigned int address_hi;
            sscanf(&testing_input[5], "%2x", &address_lo);
            sscanf(&testing_input[7], "%2x", &address_hi);
            unsigned int address = address_hi << 8 | address_lo;
            printf("Address: %04x\n", address);
            //printf("\n");

        }
        else if (testing_input[1] == '9'){
            /*The program must extract the address of the first byte in the record. Subsequent
            data bytes are stored in contiguous locations. If there is already a value in a memory location, it must
            be overwritten.
            */

            printf("S9 RECORED DETECTED: \n");

         
            unsigned int address_lo;
            unsigned int address_hi;
            sscanf(&testing_input[5], "%2x", &address_lo);
            sscanf(&testing_input[7], "%2x", &address_hi);
            unsigned int address = address_hi << 8 | address_lo;
            printf("Address: %04x\n", address);


        }
        
        int number_of_digits = (length*2) + 4 ; // SumOfDigits = (length*2) + header (2) + Count (2)
        // CheckSum 
        char checksum[2];
        //printf("checksum size %i", sizeof(checksum));
        sscanf(&testing_input[number_of_digits-2], "%c", &checksum[0]);
        sscanf(&testing_input[number_of_digits-1], "%c", &checksum[1]);
        //printf("CHECKSUM: %c%c\n", checksum[0], checksum[1]);
        
    }

}
int main(int argc, char *argv[]){
    errno_t error_flag;
    const char *file_name = "file_name";
    FILE * in_file; 
    //error_flag = fopen_s(&in_file, argv[1], "rb");
    error_flag = fopen_s(&in_file, "srecord.xme", "r");
    ReadFile(in_file);

    fclose(in_file);
    return 0;

}