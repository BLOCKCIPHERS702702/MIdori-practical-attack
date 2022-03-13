#include"Midori.h"
byte8 Sb0[16] = { 0xc, 0xa,  0xd,  0x3,  0xe,  0xb, 0xf,  0x7,  0x8,  0x9,  0x1, 0x5, 0x0, 0x2, 0x4, 0x6}; 
int Block_size=64;
int Nr = (Block_size>>4)+12;// Midori迭代轮数
int Nk = 4;// 密钥32位字大小
byte8 state[16];// 4×4状态矩阵
byte8 RoundKey[320];
byte8 SeedKey[16]={0x68,0x7d,0xed,0xeb,0xec,0x85,0xba,0xfc,0xfb,0xef,0x98,0x86,0xbe,0x5a,0x8c,0xbf};
byte8  Rcon[20][16] = { 
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,1, 0,1,0,1, 1,0,1,1, 0,0,1,1 },{0,1,1,1 ,1,0,0,0 ,1,1,0,0, 0,0,0,0},{1,0,1,0, 0,1,0,0, 0,0,1,1 ,0,1,0,1}
,{0,1,1,0, 0,0,1,0, 0,0,0,1, 0,0,1,1},{0,0,0,1, 0,0,0,0, 0,1,0,0, 1,1,1,1},{1,1,0,1, 0,0,0,1, 0,1,1,1, 0,0,0,0}
,{0,0,0,0, 0,0,1,0, 0,1,1,0, 0,1,1,0},{0,0,0,0, 1,0,1,1, 1,1,0,0, 1,1,0,0},{1,0,0,1, 0,1,0,0, 1,0,0,0, 0,0,0,1}
,{0,1,0,0, 0,0,0,0, 1,0,1,1, 1,0,0,0},{0,1,1,1, 0,0,0,1, 1,0,0,1, 0,1,1,1},{0,0,1,0, 0,0,1,0, 1,0,0,0, 1,1,1,0}
,{0,1,0,1, 0,0,0,1, 0,0,1,1, 0,0,0,0},{1,1,1,1, 1,0,0,0, 1,1,0,0, 1,0,1,0},{1,1,0,1, 1,1,1,1, 1,0,0,1, 0,0,0,0}
,{0,1,1,1, 1,1,0,0, 1,0,0,0, 0,0,0,1},{0,0,0,1, 1,1,0,0, 0,0,1,0, 0,1,0,0},{0,0,1,0, 0,0,1,1, 1,0,1,1, 0,1,0,0}
,{0,1,1,0, 0,0,1,0, 1,0,0,0, 1,0,1,0}
}; 

void InvShulleCell()
 {
	 int p[16]={0,7,14,9,5,2,11,12,15,8,1,6,10,13,4,3},i;
	 byte8 s[16];
	 for(i=0;i<16;i++)
		s[i] =state[i];
	 for(i=0;i<16;i++)
		state[i] =s[p[i]];
 }
 void MixColumn()
 {
	 int i,j,k;
	 byte8 s[16],sum;
	 for(i=0;i<16;i++)
		 s[i]=state[i];
	 for(i=0;i<4;i++)
	{
		sum=s[4*i]^s[4*i+1]^s[4*i+2]^s[4*i+3];
		for(j=0;j<4;j++)
			 state[4*i+j]=sum^s[4*i+j];
	 }
 }
void Key_Schedule( byte8 Direction)//Direction 0加密，Direction1解密
{
	int i,j;
	byte8 K[2][16];
	for(i=0;i<8;i++)
	{
		K[0][2*i]=SeedKey[i]>>4;
		K[0][2*i+1]=SeedKey[i]&0xf;
		K[1][2*i]=SeedKey[i+8]>>4;
		K[1][2*i+1]=SeedKey[i+8]&0xf;
	}
	if(!Direction)
	{
		for(j=0;j<16;j++)
				RoundKey[j]=K[0][j]^K[1][j];
		for(i=1;i<Nr;i++)
			for(j=0;j<16;j++)
				RoundKey[j+16*i]=Rcon[i][j]^K[(i+1)&0x1][j];
	}
	if(Direction)
	{
		for(j=0;j<16;j++)
				RoundKey[j]=K[0][j]^K[1][j];
		for(i=1;i<Nr;i++)
		{
			for(j=0;j<16;j++)
				state[j]=Rcon[i][j]^K[(i+1)&0x1][j];
			MixColumn();
			InvShulleCell();
			for(j=0;j<16;j++)
				RoundKey[j+16*i]=state[j];
		}
	}
}
void SubCell_64()
{
	int i,j,k;
	for(i=0;i<16;i++)
			state[i]=Sb0[state[i]];
}
 void ShulleCell()
 {
	 int p[16]={0,10,5,15,14,4,11,1,9,3,12,6,7,13,2,8},i;
	 byte8 s[16];
	 for(i=0;i<16;i++)
		s[i] =state[i];
	 for(i=0;i<16;i++)
		state[i] =s[p[i]];
 }
 void KeyAdd(int round)
 {
	 int i;
	 for(i=0;i<16;i++)
		 state[i]=state[i]^RoundKey[i+16*round];
 }
 void Midori64(byte8 input[],int in_len, byte8 output[],int out_len, byte8 key[], int keylen)
 {
	 int i,j,round = 0;
	Key_Schedule(0);
	for(i=0;i<16;i++)
	{	state[i]=input[i];
	}

	KeyAdd(0);
	for(i=1;i<Nr;i++)
	{
		SubCell_64();
		ShulleCell();
		MixColumn();
		KeyAdd(i);
	}
	SubCell_64();
	KeyAdd(0);
	for(i=0;i<16;i++)
		output[i]=state[i];
 }
 void InvMidori(byte8 input[],int in_len, byte8 output[],int out_len, byte8 key[], int keylen)
 {
	 int i,j,round = 0;
	Key_Schedule( 1);
	for(i=0;i<16;i++)
	{	state[i]=input[i];
	}
	KeyAdd(0);
	for(i=1;i<Nr;i++)
	{
		SubCell_64();
		MixColumn();
		InvShulleCell();
		KeyAdd(Nr-i);
	}
	SubCell_64();
	KeyAdd(0);
	for(i=0;i<16;i++)
		output[i]=state[i];
 }
 void Reduce_Round_Midori(int round,byte8 input[],int in_len, byte8 output[],int out_len, byte8 key[], int keylen)
 {
	 int i,j;
	Key_Schedule(0);
	for(i=0;i<16;i++)
	{	state[i]=input[i];
	}
	KeyAdd(0);
	for(i=1;i<round;i++)
	{
		SubCell_64();
		ShulleCell();
		MixColumn();
		KeyAdd(i);
	}
	SubCell_64();
	KeyAdd(0);
	for(i=0;i<16;i++)
		output[i]=state[i];
 }
 void Reduce_Round_Midori_withoutKeyschedule(int round,byte8 input[],int in_len, byte8 output[],int out_len,  int keylen)
 {
	 int i,j;
	//Key_Schedule( key,0,RoundKey);
	for(i=0;i<16;i++)
	{	state[i]=input[i];
	}
	KeyAdd(0);
	for(i=1;i<round;i++)
	{
		SubCell_64();
		ShulleCell();
		MixColumn();
		KeyAdd(i);
	}
	SubCell_64();
	KeyAdd(0);
	for(i=0;i<16;i++)
		output[i]=state[i];
 }
 void Midori(int round,byte8 input[],int in_len, byte8 output[],int out_len, byte8 key[], int keylen)
 {
	 int i,j;
	Key_Schedule( 0);
	for(i=0;i<16;i++)
	{	state[i]=input[i];
	}
	KeyAdd(0);
	for(i=1;i<round+1;i++)
	{
		SubCell_64();
		ShulleCell();
		MixColumn();
		KeyAdd(i);
	}
		for(i=0;i<16;i++)
		output[i]=state[i];
 }
 //上面这个是没有最后一轮的减轮midori，下面的是包含最后一轮的
 void Reduce_Round_InvMidori(int round,byte8 input[],int in_len, byte8 output[],int out_len, byte8 key[], int keylen)
 {
	 int i,j;
	Key_Schedule(1);
	for(i=0;i<16;i++)
	{	state[i]=input[i];
	}
	KeyAdd(0);
	for(i=1;i<round;i++)
	{
		SubCell_64();
		MixColumn();
		InvShulleCell();
		KeyAdd(round-i);
	}
	SubCell_64();
	KeyAdd(0);
	for(i=0;i<16;i++)
		output[i]=state[i];
 }
 void Reduce_Round_InvMidori_withoutKeyschedule(int round,byte8 input[],int in_len, byte8 output[],int out_len, int keylen)
 {
	 int i,j;
	for(i=0;i<16;i++)
	{	state[i]=input[i];
	}
	KeyAdd(0);
	for(i=1;i<round;i++)
	{
		SubCell_64();
		MixColumn();
		InvShulleCell();
		KeyAdd(round-i);
	}
	SubCell_64();
	KeyAdd(0);
	for(i=0;i<16;i++)
		output[i]=state[i];
 }
 int Roundfunction(int round)
 {
	 int i;
	 for(i=0;i<round;i++)
	{ 
		SubCell_64();
		ShulleCell();
		MixColumn();
		KeyAdd(i);
	 }
	 return round;
 }
 void exchange_P(byte8 a1[],byte8 b1[],int index[],byte8 a2[],byte8 b2[])
 {
	 byte8 temp;
	 int super_sbox[4][4]={{0,5,10,15},{1,4,11,14},{3,6,9,12},{2,8,7,13}},i,j;
	 for(i=0;i<4;i++)
		 if(index[i])
			 for(j=0;j<4;j++)	  
			{a2[super_sbox[i][j]]=b1[super_sbox[i][j]];
			 b2[super_sbox[i][j]]=a1[super_sbox[i][j]];}
		 else
			 for(j=0;j<4;j++)	 
			 {a2[super_sbox[i][j]]=a1[super_sbox[i][j]];
			 b2[super_sbox[i][j]]=b1[super_sbox[i][j]];}
 }
  void exchange_C(byte8 a1[],byte8 b1[],int index[],byte8 a2[],byte8 b2[])
 {
	 byte8 temp;
	 int super_sbox[4][4]={{0,1,2,3},{4,5,6,7},{8,9,10,11},{12,13,14,15}},i,j;
	 for(i=0;i<4;i++)
		 if(index[i])
			 for(j=0;j<4;j++)	  
			{a2[super_sbox[i][j]]=b1[super_sbox[i][j]];
			 b2[super_sbox[i][j]]=a1[super_sbox[i][j]];}
		 else
			 for(j=0;j<4;j++)	 
			 {a2[super_sbox[i][j]]=a1[super_sbox[i][j]];
			 b2[super_sbox[i][j]]=b1[super_sbox[i][j]];}
 }
 void exchange_v(byte8 a1[],byte8 b1[],int index[],byte8 a2[],byte8 b2[])
 {
	 byte8 temp;
	 int independent_v[4][4]={{0,4,12,8},{2,14,6,10},{3,15,7,11},{1,13,5,9}},i,j;
	 for(i=0;i<16;i++)
	 { a2[i]=a1[i];b2[i]=b1[i]; }
	 for(i=0;i<4;i++)	 
		if(index[i]) 
		for(j=0;j<4;j++) 		 
			{a2[independent_v[i][j]]=b1[independent_v[i][j]];
			 b2[independent_v[i][j]]=a1[independent_v[i][j]];}
 }
 void copy_P(byte8 a1[],byte8 b1[],int index[])
 {
	  int super_sbox[4][4]={{0,5,10,15},{1,4,11,14},{3,6,9,12},{2,8,7,13}},i,j;
	  for(i=0;i<4;i++)
		  if(index[i])
			for(j=0;j<4;j++)
				b1[super_sbox[i][j]]=a1[super_sbox[i][j]];
 }
 void copyv_P(byte8 a1[],byte8 b1[],int index[])
 {
	  int super_sbox[4][4]={{0,4,12,8},{2,14,6,10},{3,15,7,11},{1,13,5,9}},i,j;
	  for(i=0;i<4;i++)
		  if(index[i])
			for(j=0;j<4;j++)
				b1[super_sbox[i][j]]=a1[super_sbox[i][j]];
 }
 void copyC_P(byte8 a1[],byte8 b1[],int index[])
 {
	  int super_sbox[4][4]={{0,1,2,3},{4,5,6,7},{8,9,10,11},{12,13,14,15}},i,j;
	  for(i=0;i<4;i++)
		  if(index[i])
			for(j=0;j<4;j++)
				b1[super_sbox[i][j]]=a1[super_sbox[i][j]];
 }
 void unchange(byte8 p1[],byte8 p2[],int index[])
 {
	  int independent_v[4][4]={{0,4,12,8},{2,14,6,10},{3,15,7,14},{1,13,5,9}},i,j,k;
	  
 }
 void PrintWhiteningKey( )
 {
	 int i;
	 Key_Schedule(0);
	 for (i=0;i<16;i++)
		 printf(" Round Key[%d]=%x\n",i,RoundKey[i]);
 }

