#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<ctime>  
#include<iostream>   
  using   namespace   std;   

#define byte8 unsigned char
#define word32 unsigned int
  

void Midori_Inv(byte8 input[],int in_len, byte8 output[],int out_len, byte8 key[], int keylen);
void Midori(byte8 input[],int in_len, byte8 output[],int out_len, byte8 key[], int keylen);
void Reduced_Round_Midori(byte8 input[],int in_len, byte8 output[],int out_len, byte8 key[], int keylen,int roundnum);
void Key_Schedule(  byte8 Direction );
void Print_Key(int roundnum, byte8 key[]);
void Reduce_Round_Midori(int round,byte8 input[],int in_len, byte8 output[],int out_len, byte8 key[], int keylen);
void Reduce_Round_InvMidori(int round,byte8 input[],int in_len, byte8 output[],int out_len, byte8 key[], int keylen);
void Reduce_Round_InvMidori_withoutKeyschedule(int round,byte8 input[],int in_len, byte8 output[],int out_len, int keylen);
void Midori64(byte8 input[],int in_len, byte8 output[],int out_len, byte8 key[], int keylen);
void Reduce_Round_Midori_withoutKeyschedule(int round,byte8 input[],int in_len, byte8 output[],int out_len,  int keylen);
void PrintWhiteningKey();
void InvMidori(byte8 input[],int in_len, byte8 output[],int out_len, byte8 key[], int keylen);


