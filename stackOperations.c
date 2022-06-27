//
//  main.c
//
//
//  Created by Asude Ekiz on 2.04.2022.
//
#define MAXSIZE 32
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int isempty(void);
int isfull(void);
char stack[MAXSIZE];
int top = -1;
int peek(void) ;
int pop(void);
int push(char data);

int main(int argc, const char * argv[]) {
    int number;
    int value = 0;
    int flag = 0;
    int bitNumber;
    int digit;
    char bit;
    char *val_array;
    char *onesComplement;
    char *twosComplement;
    char *binaryNumber;
    int error=0;
    int carry=1;
    int i,j;
    //READ ME
    //number girilen sayi
    //value girilen sayinin mutlak degeri
    //val_array girilen sayiyi tutan string
    //sayi negatifse val_array twos complemente giricek
    //degilse ayni kalicak
    //binaryNumber da son durumdaki hali
    printf("Please enter the number:\n");
    scanf("%d",&number);
    if (number<0) {
        value=number*(-1);
        flag=1; //sayi negatif demek
    }
    else
        value=number;
    
    printf("value:%d\n",value);
    
    bitNumber=log2(value)+1;
    printf("bitNumber:%d\n",bitNumber);
    
    val_array=(char*)malloc(bitNumber*sizeof(char));
    onesComplement=(char*)malloc(bitNumber*sizeof(char));
    twosComplement=(char*)malloc(bitNumber*sizeof(char));
    

    
    
    while ((value/2)!=0) {
        digit=value%2;
        bit=digit+'0';
        push(bit);
        value/=2;
    }
    if (value/2==0) {
        digit=value;
        bit=digit+'0';
        push(bit);
    }
    
    printf("Instant bit state:\n");
    
    i=0;
    while(!isempty()) {
       val_array[i] = pop();
       printf("%c",val_array[i]);
        i++;
    }
    
    if (flag==1) { //sayi negatifse twos complement yapılacak
       
            
        for(i=0; i < bitNumber; i++) {
               if(val_array[i]=='1') {
                   onesComplement[i] = '0';
               } else if(val_array[i]=='0') {
                   onesComplement[i] = '1';
               } else {
                   printf("Error :( ");
                   return 1;
               }
           }
           onesComplement[bitNumber] = '\0';
            
          
           for(i = bitNumber-1; i >= 0; i--) {
               if(onesComplement[i]=='1' && carry==1){
                   twosComplement[i] = '0';
               } else if(onesComplement[i]=='0' && carry==1) {
                   twosComplement[i] = '1';
                   carry = 0;
               } else {
                   twosComplement[i] = onesComplement[i];
               }
           }
           twosComplement[bitNumber] = '\0';
              
           printf("\nTwo's Complement : %s\n", twosComplement);
    }
    //verilen sayiyi 8 in katlari olacak sekilde ifade etme
    
    int tmp=bitNumber;
    while (tmp%8!=0) {
        tmp=tmp+1;
    }
    printf("\nExpanded digit count:%d\n",tmp);
    binaryNumber=(char*)malloc(tmp*sizeof(char));
    
    if (flag==1) {//sayi negatifse genisletilen kisim 1lerle doldurulacak
        for (i=0; i<tmp-bitNumber; i++) {
            binaryNumber[i]='1';
        }
        //kalan kismina da val_arraydeki aynen gecirilecek
        j=0;
        for (i=tmp-bitNumber; i<tmp; i++) {
            binaryNumber[i]=twosComplement[j];
            j++;
        }
        binaryNumber[tmp] = '\0';
    }
    
    else if (flag==0){//sayi pozitifse genisletilen kisim 0lerle doldurulacak
        for (i=0; i<tmp-bitNumber; i++) {
            binaryNumber[i]='0';
        }
        //kalan kismina da val_arrayin twoscomplement hali aynen gecirilecek
        j=0;
        for (i=tmp-bitNumber; i<tmp; i++) {
            binaryNumber[i]=val_array[j];
            j++;
        }
        binaryNumber[tmp] = '\0';
    }
    printf("\nBinary Number is: %s\n\n", binaryNumber);
    //printf("STACK BEFORE PUSHING\n");
    
   // printf("%s\n",stack);
   //stack bosaltma kismi
    char garbage;
    while (!isempty()) {
        garbage=pop();
    }
    
    int control=0;
    for (i=0; i<tmp; i++) {
        if (binaryNumber[i]=='1') {
            push('*');
        }
        else if (binaryNumber[i]=='0'){
            if (!isempty()) {
                pop();
            }
            else{
                control-=1;
            }
        }
    }
    
    int result=top+1+control;
    if (result==0) {
        //printf("result:%d\n",result);
        printf("0 ve 1 adedi esittir.\n");
    }
    else if(result>0){
        //printf("result:%d\n",result);
        printf("1 adedi 0 adedinden %d fazladir.\n",result);
    }
    else if (result<0){
        int posresutlt=abs(result);
        //printf("result:%d\n",result);
        printf("0 adedi 1 adedinden %d fazladir.\n",posresutlt);
    }
    

    return 0;
}

int isempty() {

   if(top == -1)
      return 1;
   else
      return 0;
}
   
int isfull() {

   if(top == MAXSIZE)
      return 1;
   else
      return 0;
}

int peek() {
   return stack[top];
}

int pop() {
   char data;
    
   if(!isempty()) {
      data = stack[top];
      top = top - 1;
      return data;
   } else {
      printf("Could not retrieve data, Stack is empty.\n");
      return 0;
   }
}

int push(char data) {

   if(!isfull()) {
      top = top + 1;
      stack[top] = data;
       return 1;
   } else {
      printf("Could not insert data, Stack is full.\n");
       return 0;
   }
}
