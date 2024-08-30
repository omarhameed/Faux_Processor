/**
 *  ECED3403 - Computer Architecture Assignment 1
 * @file emulator.h
 * @brief CPU emulator program definitions and declarations
 *
 * This header file contains macro definitions and declarations of external variables
 * and functions for the X-Makina emulator program, including register and memory definitions,
 * bit masking definitions, and functions for branching, arithmetic operations, and
 * various addressing modes.
 *
 * @author Omar Hameed
 * @date July 17, 2023
 */

#ifndef EMULATOR_H
#define EMULATOR_H

#include <stdio.h>

// Color definitions for console output
#define RED     "\033[1m\033[31m"    
#define YELLOW  "\033[1m\033[33m"      
#define RESET   "\033[0m"

// Memory and buffer sizes
#define MAXBufSize 256
#define MEM_SIZE 0x10000
#define WORD_MEM_SIZE 1<<15
#define BYTE_MEM_SIZE 1<<16
#define MAX_FILE_NAME 20
#define DataStart 8

// Register and memory operation definitions
#define WORD 0
#define BYTE 1
#define ByteLength 7 // 0 to 7 is 8 bits

#define REG_CONS 2
#define REG 0
#define GP_REG 4
#define BP RegFile[0][4]
#define LR RegFile[0][5]
#define SP RegFile[0][6]
#define PC RegFile[REG][7] 
#define number_reg 8
#define num_consts 8
#define NUM_REG 8
#define LastByte 1

// Memory Access Modes
#define R 0 // Read
#define WR 1 // Write

// Instructions and operations
enum BR { BEQ, BNE, BC, BNC, BN, BGE, BLT, BRA };
enum Arithmetics { ADD, ADDC, SUB, SUBC, DADD, CMP, XOR, AND, OR, BIT, BIC, BIS };
enum Mov { MOVL, MOVLZ, MOVLS, MOVH };
enum IndexedAddressings { LD = 0b10, ST = 0b11 };
enum OneOprands { SRA, RRC, COMP, SWAPB, SXT };
enum PrePos { Normal, POS_INC, POS_DEC, PRE_INC = 0b101, PRE_DEC = 0b110 };

// Program Status Word structure
typedef struct {
    unsigned short c : 1;
    unsigned short z : 1;
    unsigned short n : 1;
    unsigned short slp : 1;
    unsigned short v : 1;
    unsigned short current : 3; /* Current priority */
    unsigned short faulting : 1; /* 0 - No fault; 1 - Active fault */
    unsigned short reserved : 4;
    unsigned short previous : 3; /* Previous priority */
} psw_bits;
extern psw_bits psw;

// Memory union for handling different data types
extern union Memory {
    unsigned short WordMem[WORD_MEM_SIZE];
    unsigned char ByteMem[BYTE_MEM_SIZE];
} memory_u;

// Function declarations for emulator operations
extern void Controller();
extern void Fetch();
extern void Decode();
extern void Execute();
extern void UpdatePSW(unsigned short src, unsigned short dst, unsigned short res, unsigned short wb);
extern void Bus(unsigned short mar, unsigned short* mdr_ptr, int read_write, int word_byte);

#endif // EMULATOR_H
