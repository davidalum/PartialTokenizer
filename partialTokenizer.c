/*                                                                                                                                                                                                                
 * tokenizer.c                                                                                                                                                                                                   
Partial Tokenizer written by: David Alummoottil                                                                                                                                                                   
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*                                                                                                                                                                                                                
 * Tokenizer type.  You need to fill in the type as part of your implementation.                                                                                                                                  
 */

struct TokenizerT_ {
                                                                                                                               
  char type[30]; //indicates decimal, float, octal, etc..                                                                                                                                                    
  char* token; //the string that represents the token                                                                                                                                                          
};

typedef struct TokenizerT_ TokenizerT;

char *helper(char *str, int k){
 
  int len;
  len  = strlen(str);
  char *newStr = (char*) malloc ( sizeof(char) *len); //CHECK proper length                                                                                                                                         
int j = k;
 if(!isdigit(str[0]) ){
   printf("Error, first char not number.\n");
   j=1;
 }
  int d = 0;
  while(j<len){
    if(isxdigit(str[j]) || str[j] =='+'|| str[j] == '-' || str[j] =='.' || str[j] == 'x' || str[j] == 'X'|| str[j] == 'e' || str[j] == 'E'){
      newStr[d++] = str[j]; // Overwriting the null-character with another one 
    }
    else{

      printf("[0x%02X]\n",str[j]);	
      char *tok = newStr;
      return tok;
    }
    if(j == len-1){
      return (char *) newStr;
    }
j++;
    
  }
  return NULL;
}


int octalCheck(char *newStr){ //Returning 0 means not an octal, 1 means it is an octal
  int len;
  len = strlen(newStr);
  int i;
  int boolean = 8; 
                                                                                                                                                      
  for(i=2;i<len;i++){
   if( isdigit(newStr[i])){
    if(newStr[i] == '8' || newStr[i] == '9') 
     {
      boolean = 0;
      return boolean;
     }
    }
    else{
      boolean =0;
return boolean;
}
  }
  boolean = 1;
  return boolean;
}

int hexCheck(char *newStr){ //0 means not hex, 1 mean hex
  int len;
  len = strlen(newStr);
  int i;
  int boolean = 8;
  if(len ==2){
    boolean = 0;
    return boolean;
  }

  for(i=2;i<len;i++){
    if(isxdigit(newStr[i])==0){
      boolean=0;
      return boolean; 
    }
  }
  boolean=1; 
  return boolean;
}

int floatCheck(char* newStr, int charIndex){ //0 is not float, 1 means is a float. newStr starts with ., e, or E.                                                                                                                                   
  int len;                                                                                                                                                                                                       
  int i;
  i = charIndex+1;
  int boolean=8;                                                                                                                                                                                                    len = strlen(newStr);
  if( newStr[len-1]=='.' || newStr[len-1]=='e' || newStr[len-1]=='E'|| newStr[len-1]=='+'|| newStr[len-1]=='-')
    return 0; //if the last char is one of these, will be a mal token
  if( isdigit(newStr[i])==0 && newStr[i] != '+' &&newStr[i] != '-'){ //it is not a # excluding +, or -  
	    return 0;
  }
  int j;
  for(j=(charIndex+1);j<len;j++){
    if(isdigit(newStr[j]))
      boolean = 1; 
if(newStr[charIndex]=='e' || newStr[charIndex]== 'E')
	if(newStr[j] == '.')
	return 0;
  }
  return boolean;
}


int intCheck(char *newStr){ //0=not int, 1=int, 2=float, 3=not float 
  //printf("Entered int\n");
  int len;
  len = strlen(newStr);
  int i;
  int boolean = 8;
  int floatBoolean;
  if (len == 1){
    boolean = 1;
    return boolean;
  }
  for(i=1;i<len;i++){
    if(isdigit(newStr[i]) == 0){ //char is not 0-9 check
      if(newStr[i] == '.' || newStr[i] == 'e' || newStr[i] == 'E'){ //string could be a float
	floatBoolean = floatCheck(newStr, i);
	if(floatBoolean == 1) 
	  return 2; //indicates it is a float
	else if( floatBoolean== 0)
	  return 3; //indicates it is not a float
	else{
	  return 3;
	}
      }
      boolean = 0;
      return boolean;
      }
    }
  boolean = 1;  
  return boolean;
}


/*                                                                                                                                                                                                                
 TKCreate creates a new TokenizerT object for a given token stream                                                                                                                                              
 * (given as a string).                                                                                                                                                                                           
 *                                                                                                                                                                                                                
 * TKCreate should copy the arguments so that it is not dependent on                                                                                                                                              
 * them staying immutable after returning.  (In the future, this may change                                                                                                                                       
 * to increase efficiency.)                                                                                                                                                                                       
 *                                                                                                                                                                                                                
 * If the function succeeds, it returns a non-NULL TokenizerT.                                                                                                                                                     * Else it returns NULL.                                                                                                                                                                                           *                                                                                                                                                                                                               
 * You need to fill in this function as part of your implementation.                                                                                                                                              
 */


TokenizerT *TKCreate( char * ts ) {
  int len;
  int boolean;
  TokenizerT *newToken;
  newToken = (TokenizerT*) malloc(sizeof(TokenizerT));
  newToken->token= (char*) malloc( sizeof(char) * strlen(ts));
  strcpy(newToken->token, ts);
  len = strlen(ts);
  char firstChar = ts[0];
  char secondChar = ts[1];
  
  if(firstChar == '0'){  // Check if the 1st char = 0
    if(len == 1) //check if its just a zero
      strcpy(newToken->type, "Zero");
    if(isdigit(secondChar) && secondChar != '8' && secondChar != '9') //check if it can be OCTAL
      boolean = octalCheck(ts);     
    if(secondChar == '8' || secondChar == '9') 
	boolean = 0;
      if(boolean == 1)
	strcpy(newToken->type, "octal");
      else if(boolean == 0)
	strcpy(newToken->type, "mal");
    if(secondChar == 'x' || secondChar == 'X'){  //check if it can be HEX
      boolean = hexCheck(ts);
      if(boolean == 1)
        strcpy(newToken->type, "hexadecimal");
      else if(boolean == 0)
        strcpy(newToken->type, "mal");
        
    } //end of check if it can be HEX
    if(secondChar == '.'){  //check if it can be FLOAT starting with 0
      boolean = floatCheck(ts, 1);
      if(boolean == 0)
	strcpy(newToken->type, "mal");
      else if(boolean==1)
	strcpy(newToken->type, "float");
    }
   } //end of if firstchar = 0
 
 else if( isdigit(firstChar)){ //check if 1st char is 1-9
   boolean = intCheck(ts); //check if its a decimal or float starting with 1-9
   if(boolean == 1) 
     strcpy(newToken->type, "decimal"); 
   else if(boolean == 0)
     strcpy(newToken->type, "mal");
   else if( boolean == 2) 
     strcpy(newToken->type, "float");
     else if(boolean == 3)
       strcpy(newToken->type, "mal");   
     }//end of 1st char 1-9

return newToken;

 
} //end of TKCreate

/*                                                                                                                                                                                                                
 * TKDestroy destroys a TokenizerT object.  It should free all dynamically                                                                                                                                         * allocated memory that is part of the object being destroyed.                                                                                                                                                   
 *                                                                                                                                                                                                                
 * You need to fill in this function as part of your implementation.  */

void TKDestroy( TokenizerT * tk ) {

	free (tk->type);
	free (tk->token);
}

char *TKGetNextToken( TokenizerT * tk ) {
  return NULL;
}

/*                                                                                                                                                                                                                
 * main will have a string argument (in argv[1]).                                                                                                                                                                 
 * The string argument contains the tokens.                                                                                                                                                                       
 * Print out the tokens in the second string in left-to-right order.                                                                                                                                              
 * Each token should be printed on a separate line.                                                                                                                                                               
 */

int main(int argc, char **argv) {
  int i;
  char * test;
  int len;
  TokenizerT* newTok;
  if(argc<2){ //check to see if anything is entered in command line
    printf("No tokens in the command line argument\n");
    return 0;
  }

  for(i=1; i<argc;i++){
    len = strlen(argv[i]);
    
    char str[len];
    strcpy(str, argv[i]);
    int j=0;
    int adjLen=0;

    while(j<len){		                                                                                                                                                                                     /*           if(!isdigit(str[0]) ){
        printf("Error, first char not number.\n");
        return 0;
	}*/                     		  	 
  test = helper(str, j);	//call to helper function
  adjLen=strlen(test);  //used to make sure the whole string is iterated through
  newTok = TKCreate(test);  //sends string to be put into a token struct
  printf("%s %s\n", newTok->type, newTok->token); 
  j= j+adjLen+1; //incremement j so doesnt run forever
  TKDestroy(newTok);
} //end of while j<len
/*if(!isdigit(str[0]) ){
	printf("Error, first char not number.\n");
	return 0;
	}*/
//TKDestroy(newTok);          
	                                                                                                                                                                
  }
  return 0;
}
