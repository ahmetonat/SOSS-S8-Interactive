
#ifndef __CMD_PARSE_H__
#define __CMD_PARSE_H__

#include "stm8s.h"

// Parser states:
#define ST_INIT 10      //Wating for command.
#define ST_DELIM1 20    //Waiting for delimiter1
#define ST_ARG 30       //Waiting for argument
#define ST_EXP 40       //Waiting for exponent
#define ST_DELIM_END 50 //Waiting for end delimiter.

#define KWD_REF 'r'
#define KWD_KP  'p'
#define KWD_KD  'd'
#define KWD_KI  'i'
#define KWD_TS  't'  //Ref change time. //TODO: Set a minimum.
#define KWD_MOD 'm'  //Change ref mode: 1: Step, 2:Analog, 3: Serial.

#define KWD_CMD_DELIM '='
#define KWD_SEPARATOR ','
#define KWD_CMD_END   '.'

//Arbitrary command values:
#define CMD_REF 1
#define CMD_KP  2
#define CMD_KD  3
#define CMD_KI  4
#define CMD_TS  5
#define CMD_MOD 6

//References can be received from the following sources:
#define REFMODE_CMD 0  // From serial command r=...
#define REFMODE_PER 1  // Periodic (amplitude still from command r=...
#define REFMODE_POT 2  // From pot value.


#define VALUE_MAX 20000 //Max allowed value in a command.

// struct parserparams

typedef struct { //The parameters for the parser.
  uint8_t rcv_chr; //The last received character.
  uint8_t chr_received; // Flag that character has been received.
  uint8_t state; //State of the parser.
  uint8_t command; //
  int16_t value; // The argument value of the received command.
  uint8_t isnegative; //Argument value sign.
  uint8_t exp;  //Argument exponent for PID parameters.
  int16_t cmd_arg;  // After successful parse, the value will be set.
  uint8_t cmd_div;
  uint8_t cmd_parsed; //Flag that successful parse has been conducted.

}ParserParams_t;

void init_parser(ParserParams_t * user);

void parser(ParserParams_t * user);

//uint8_t error (uint8_t state);    //Error in input.
void error (ParserParams_t * user);    //Error in input.
uint8_t success (uint8_t state);  //Input successfully parsed.

int16_t intfromchar(int16_t value, uint8_t chr);



#endif
