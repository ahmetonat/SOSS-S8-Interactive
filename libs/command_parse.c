

//TODO: error must also re-initialize the user.

#include "command_parse.h"

const uint8_t err_str[]=" ERROR!\n\r";
const uint8_t err_str_len=9;

void parser(ParserParams_t * user){  
  // This function is called when a character is received.
  // Get the next char in the stream:
  
  if (user->state==ST_INIT){ //In init. state, first char is the command:
    if (user->rcv_chr==KWD_REF){  //Received set ref command
      user->command=CMD_REF;
      //user->state=20;    //TODO: FIXME! Replace with ST_DELIM1
      user->state=ST_DELIM1;
    }else if (user->rcv_chr==KWD_MOD){ //Received ref mode command
      user->command=CMD_MOD;
      //      user->state=20;
      user->state=ST_DELIM1;
    }else if (user->rcv_chr==KWD_TS){ //Received rep period command
      user->command=CMD_TS;
      //      user->state=20;
      user->state=ST_DELIM1;
    }else if (user->rcv_chr==KWD_KP){ //Received KP command
      user->command=CMD_KP;
      //      user->state=20;
      user->state=ST_DELIM1;
    }else if (user->rcv_chr==KWD_KD){ //Received KD command
      user->command=CMD_KD;
      //      user->state=20;
      user->state=ST_DELIM1;
    }else if (user->rcv_chr==KWD_KI){ //Received KI command
      user->command=CMD_KI;
      //      user->state=20;
      user->state=ST_DELIM1;
    }else {   //Received irrelevant character.
      error(user);
    }
  } //END: if ST_INIT
  else if (user->state==ST_DELIM1){ //Waiting for equals.
    if (user->rcv_chr==KWD_CMD_DELIM){ //Received equals.
      //      printf ("Received delimiter '=' as expected.\n");
      user->value=0;
      user->state=ST_ARG;
    }else{//Received unexpected character.
      error(user);
    }
  }//END: if ST_DELIM1
  else if (user->state==ST_ARG){
    if (user->rcv_chr>='0' && user->rcv_chr <='9'){//Received numeral
      user->value=intfromchar(user->value, user->rcv_chr);
      if (user->value>VALUE_MAX){
	//printf("Input value out of bounds: %d, Must be max:%d\n",
	//value, VALUE_MAX);
	error(user);
      }
    }else if(user->rcv_chr=='-' && user->value==0){
      user->isnegative=TRUE;  //The value sign is negative.
    }else if(user->rcv_chr == KWD_CMD_END && (user->command==CMD_REF||
					      user->command==CMD_MOD||
					      user->command==CMD_TS)){
      //Received end delimiter and command requires 1 argument.
      //      printf("Completed receiving the reference.\n");
      //      printf("The value is: %d\n", value);
      if (user->isnegative==TRUE){
	user->cmd_arg=-user->value;
      }else{
	user->cmd_arg=user->value;
      }
      user->isnegative=FALSE; //TODO: Think of how to end parser!
      user->cmd_parsed=TRUE;
      user->state=ST_INIT;
    }else if (user->rcv_chr==KWD_SEPARATOR && (user->command==CMD_KP||
					       user->command==CMD_KD||
					       user->command==CMD_KI)){
      //Received DELIMITER2 and is processing a parameter set command:
      if (user->isnegative==TRUE){
	user->cmd_arg= -user->value;
      }else{
	user->cmd_arg=  user->value;
      }
      user->isnegative=FALSE;
      user->state=ST_EXP;    //Go to state to read exponent.
      
    }else{ //Received illegal character, or ',' not applicable to this state.
      //      printf("Received illegal character!\n");
      error(user);
    }
    
  }//END: if STATE==ST_ARG
  else if (user->state==ST_EXP){
    if (user->rcv_chr>='0' && user->rcv_chr <='9'){//Received numeral
      user->exp=((int16_t)user->rcv_chr-'0'); //Set parameter exponent.
      user->state=ST_DELIM_END;
    }else{ //received irrelevant character.
      error(user);
    }
  }//END: if STATE==ST_EXP
  else if (user->state==ST_DELIM_END){
    if (user->rcv_chr==KWD_CMD_END){//Received DELIM2
      user->isnegative=FALSE; //TODO: Think of how to end parser!
      user->cmd_parsed=TRUE;
      user->state=ST_INIT;
      //TODO: Write an end-of-parse function to handle these!
    }else{ //received irrelevant character.
      error(user);
    }
  }//END: if STATE==ST_DELIM_END
  
  
  else{
    //    printf("Unexpected state value!\n");
    error(user);
  }//END STATE CHECKS.
  
}//END parser



//Initialize parser parameters:
void init_parser(ParserParams_t * user){
  user->chr_received = FALSE;
  user->state=ST_INIT;
  user->value=0;
  user->exp=0;
  user->cmd_parsed=FALSE; //Parse successful flag
  user->cmd_arg=0;        //Command argument
  user->cmd_div=0;        //Command divisor
  user->isnegative=FALSE;
}



//uint8_t error (uint8_t state){
void error (ParserParams_t * user){

  uint8_t i;

  for (i=0;i<err_str_len; ++i){
    //UART1_SendData8(err_str[i]);
    UART1->DR=err_str[i];
  while ((UART1->SR & (uint8_t)UART1_FLAG_TXE) == (uint8_t)0x00);
  }
 
  //printf ("Error in state: %d!\n", state);
  //TODO: LED_ON(); or similar...
  //  return (ST_INIT);
  init_parser(user);
}


int16_t intfromchar(int16_t value, uint8_t chr){
  value=(value<<3)+(value<<1)+((int)chr-'0');//Simple *10
  //printf("Value is:%d\n", value);
  return (value);
}//TODO: Replace typecast with int16_t

uint8_t success (uint8_t state){
  uint8_t i;
  i=state;
  return 0;
}
