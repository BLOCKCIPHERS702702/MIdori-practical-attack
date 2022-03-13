#include"Midori.h"

// unsigned char rsbox[256];

 int Choose_Chiprtext_Pair(unsigned char *good_pair1,unsigned char *good_pair2)
 {
		unsigned char 
		P[4][16]= {{ 0x5,0x1,0x0,0x8,0x4,0xf,0x4,0x5,0x1,0x2,0x3,0x1,0x5,0xc,0xa,0x2},
								{0x4,0x2,0xc,0x2,0x0,0xf,0xd,0x3,0xb,0x5,0x8,0x6,0x8,0x7,0x9,0xe},
								{0xe,0xc,0x8,0x7,0xd,0x7,0xb,0xa,0xb,0xc,0x2,0x9,0x7,0x5,0x4,0x3}};
		unsigned char C[16][16];
	int index0[4]={0,1,1,1},i,j,k,l,count=0,index123[3];
	int independent_v[4][4]={{0,4,12,8},{2,14,6,10},{3,15,7,14},{1,13,5,9}};
	unsigned char *pair_count=(unsigned char *)calloc(16777216,sizeof(char));
	unsigned char *realc_set=(unsigned char *)calloc(70000*16,sizeof(char));
	unsigned int *save_num=(unsigned int *)calloc(33554500,sizeof(int));
	double c=2;
	//printf("%x,%x,%x,%x,%x,\n",RoundKey[1],RoundKey[2],RoundKey[3],RoundKey[6],RoundKey[9]);
	FILE *fp1=fopen("Pair1 text.txt","wb");
	FILE *fp2=fopen("Pair2 text.txt","wb");
	FILE *fp0=fopen("Pair Num.txt","wb");
	unsigned long ss,sss;
	unsigned long index[65536];
	int num1=pow(c,16),num2=pow(c,11),flag,sum=0,count1=0;
		for(i=0;i<16777216;i++)
			*(pair_count+i)=0;
	Key_Schedule(0);
	for(sss=0;sss<num2;sss++)
	{
		P[0][2]=(sss>>8)&0xf;P[0][6]=(sss>>4)&0xf;P[0][10]=(sss)&0xf;
	//	printf("%d,count1=%d,  ",sss,count1);
		for(ss=0;ss<num1;ss++)
		{
			for(j=0;j<4;j++)
				P[0][independent_v[0][j]]=(ss>>4*j)&0xf;
			Reduce_Round_Midori_withoutKeyschedule(6,P[0],64,C[0],64,128);
			for(i=0;i<16;i++)
				*(realc_set+i+(16*ss))=C[0][i];  //第i个存储第i个完整的密文
		}
		for(i=0;i<num1;i++)
		{
			ss=*(realc_set+(16*i)+4)|(*(realc_set+(16*i)+5)<<4)|(*(realc_set+(16*i)+6)<<8)|(*(realc_set+(16*i)+8)<<12)|(*(realc_set+(16*i)+10)<<16)|(*(realc_set+(16*i)+11)<<20);
			index[i]=ss;
			*(save_num+(ss<<1)+*(pair_count+ss))=i;
			*(pair_count+ss)=*(pair_count+ss)+1;  //值为ss的输入有几个
			if(*(pair_count+ss)>1) 
			{
				for(j=0;j<16;j++)
				{
					*(good_pair1+count1*16+j)=*(realc_set+*(save_num+(ss<<1))*16+j);  //printf("%x,",	*(good_pair1+count1*16+j));
					*(good_pair2+count1*16+j)=*(realc_set+*(save_num+(ss<<1)+1)*16+j);  //printf("%x,",	*(good_pair2+count1*16+j));
				}
				count1++; //printf("\n");
			}
		}
		for(i=0;i<num1;i++)
			*(pair_count+index[i])=0;	
	}
	count=0;
	//   前四字节不能相等
	for(j=0;j<count1;j++)
	{
		if((*(good_pair1+j*16)!=*(good_pair2+j*16))||
			((*(good_pair1+j*16+1)==*(good_pair2+j*16+1))&&
			(*(good_pair1+j*16+2)==*(good_pair2+j*16+2))&&
			(*(good_pair1+j*16+3)==*(good_pair2+j*16+3)))
			)	
			continue;
		for(i=0;i<16;i++)
		{	*(good_pair1+count*16+i)=*(good_pair1+j*16+i);
			*(good_pair2+count*16+i)=*(good_pair2+j*16+i);
		}
		count++;
	}
	fwrite(good_pair1,1,count1*16,fp1);fclose(fp1);
	fwrite(good_pair2,1,count1*16,fp2);fclose(fp2);
	fprintf(fp0,"%d",count);
	fclose(fp0);
	printf("Choose_Chiprtext_Pair finished count=%d\n",count);
	return count;
 }

int Choose_Chiprtext_PairII(unsigned char *good_pair1,unsigned char *good_pair2)
 {
		unsigned char 
		P[4][16]= {{ 0x5,0x1,0x0,0x8,0x4,0xf,0x4,0x5,0x1,0x2,0x3,0x1,0x5,0xc,0xa,0x2},
								{0x4,0x2,0xc,0x2,0x0,0xf,0xd,0x3,0xb,0x5,0x8,0x6,0x8,0x7,0x9,0xe},
								{0xe,0xc,0x8,0x7,0xd,0x7,0xb,0xa,0xb,0xc,0x2,0x9,0x7,0x5,0x4,0x3}};
		unsigned char C[16][16];
	int index0[4]={0,1,1,1},i,j,k,l,count=0,index123[3];
	int independent_v[4][4]={{0,4,12,8},{2,14,6,10},{3,15,7,14},{1,13,5,9}};
	unsigned char *pair_count=(unsigned char *)calloc(16777216,sizeof(char));
	unsigned char *realc_set=(unsigned char *)calloc(70000*16,sizeof(char));
	unsigned int *save_num=(unsigned int *)calloc(33554500,sizeof(int));
	double c=2;
	//printf("%x,%x,%x,%x,%x,\n",RoundKey[1],RoundKey[2],RoundKey[3],RoundKey[6],RoundKey[9]);
	FILE *fp1=fopen("Pair1II text.txt","wb");
	FILE *fp2=fopen("Pair2II text.txt","wb");
	FILE *fp0=fopen("PairII Num.txt","wb");
	unsigned long ss,sss;
	unsigned long index[65536];
	int num1=pow(c,16),num2=pow(c,11),flag,sum=0,count1=0;
		for(i=0;i<16777216;i++)
			*(pair_count+i)=0;
	Key_Schedule(0);
	for(sss=0;sss<num2;sss++)
	{
		P[0][0]=(sss>>8)&0xf;P[0][4]=(sss>>4)&0xf;P[0][8]=(sss)&0xf;
	//	printf("%d,count1=%d,  ",sss,count1);
		for(ss=0;ss<num1;ss++)
		{
			for(j=0;j<4;j++)
				P[0][independent_v[1][j]]=(ss>>4*j)&0xf;
			Reduce_Round_Midori_withoutKeyschedule(6,P[0],64,C[0],64,128);
			for(i=0;i<16;i++)
				*(realc_set+i+(16*ss))=C[0][i];  //第i个存储第i个完整的密文
		}
		for(i=0;i<num1;i++)
		{
			ss=*(realc_set+(16*i)+4)|(*(realc_set+(16*i)+5)<<4)|(*(realc_set+(16*i)+6)<<8)|(*(realc_set+(16*i)+8)<<12)|(*(realc_set+(16*i)+10)<<16)|(*(realc_set+(16*i)+11)<<20);
			index[i]=ss;
			*(save_num+(ss<<1)+*(pair_count+ss))=i;
			*(pair_count+ss)=*(pair_count+ss)+1;  //值为ss的输入有几个
			if(*(pair_count+ss)>1) 
			{
				for(j=0;j<16;j++)
				{
					*(good_pair1+count1*16+j)=*(realc_set+*(save_num+(ss<<1))*16+j);  //printf("%x,",	*(good_pair1+count1*16+j));
					*(good_pair2+count1*16+j)=*(realc_set+*(save_num+(ss<<1)+1)*16+j);  //printf("%x,",	*(good_pair2+count1*16+j));
				}
				count1++; //printf("\n");
			}
		}
		for(i=0;i<num1;i++)
			*(pair_count+index[i])=0;	
	}
	count=0;
	//   前四字节不能相等
	for(j=0;j<count1;j++)
	{
		if((*(good_pair1+j*16)!=*(good_pair2+j*16))||
			((*(good_pair1+j*16+1)==*(good_pair2+j*16+1))&&
			(*(good_pair1+j*16+2)==*(good_pair2+j*16+2))&&
			(*(good_pair1+j*16+3)==*(good_pair2+j*16+3)))
			)	
			continue;
		for(i=0;i<16;i++)
		{	*(good_pair1+count*16+i)=*(good_pair1+j*16+i);
			*(good_pair2+count*16+i)=*(good_pair2+j*16+i);
		}
		count++;
	}
	fwrite(good_pair1,1,count1*16,fp1);fclose(fp1);
	fwrite(good_pair2,1,count1*16,fp2);fclose(fp2);
	fprintf(fp0,"%d",count);
	fclose(fp0);
	printf("Choose_Chiprtext_Pair finished count=%d\n",count);
	return count;
 }
int Guess_key10(unsigned int guess_k[ ])
{
	byte8 Sb0[16] = { 0xc, 0xa,  0xd,  0x3,  0xe,  0xb, 0xf,  0x7,  0x8,  0x9,  0x1, 0x5, 0x0, 0x2, 0x4, 0x6}; 
		unsigned char 
		P[4][16]= {{ 0x5,0x1,0x0,0x8,0x4,0xf,0x4,0x5,0x1,0x2,0x3,0x1,0x5,0xc,0xa,0x2},
								{0x4,0x2,0xc,0x2,0x0,0xf,0xd,0x3,0xb,0x5,0x8,0x6,0x8,0x7,0x9,0xe},
								{0xe,0xc,0x8,0x7,0xd,0x7,0xb,0xa,0xb,0xc,0x2,0x9,0x7,0x5,0x4,0x3}};
		unsigned char C[16][16];
	int index0[4]={0,1,1,1},i,j,k,l,count=0,index123[3],count1=0;
	int independent_v[4][4]={{0,4,12,8},{2,14,6,10},{3,15,7,14},{1,13,5,9}};
	unsigned char *pair_count=(unsigned char *)calloc(16777216,sizeof(char));
	unsigned char *realc_set=(unsigned char *)calloc(70000*16,sizeof(char));
	unsigned int *save_num=(unsigned int *)calloc(33554500,sizeof(int));
	unsigned char *good_pair1=(unsigned char *)calloc(8389000,sizeof(char));
	unsigned char *good_pair2=(unsigned char *)calloc(8389000,sizeof(char));
	double c=2;
	unsigned long ss,sss;
	unsigned long index[65536];
	int num1=pow(c,16),num2=pow(c,11),flag,sum=0;
		
	Key_Schedule(0);
	for(ss=0;ss<num1;ss++)
	{
		for(j=0;j<4;j++)
			P[0][independent_v[1][j]]=(ss>>4*j)&0xf;
		Reduce_Round_Midori_withoutKeyschedule(6,P[0],64,C[0],64,128);
		for(i=0;i<16;i++)
			*(realc_set+i+(16*ss))=C[0][i];  //第i个存储第i个完整的密文
	}
	unsigned char State[6],SUM;
	Key_Schedule(1);
	for(guess_k[10]=0;guess_k[10]<16;guess_k[10]++)
	{	
		for(i=0;i<16777216;i++)
			*(pair_count+i)=0;
	//	guess_k[10]=RoundKey[10];
		count1=0;
		for(i=0;i<num1;i++)
		{
			State[0]=Sb0[*(realc_set+(16*i)+4)^guess_k[4]]^Sb0[*(realc_set+(16*i)+5)^guess_k[5]]^Sb0[*(realc_set+(16*i)+6)^guess_k[6]];
			State[1]=Sb0[*(realc_set+(16*i)+8)^guess_k[8]]^Sb0[*(realc_set+(16*i)+10)^guess_k[10]]^Sb0[*(realc_set+(16*i)+11)^guess_k[11]];
			State[2]=Sb0[*(realc_set+(16*i)+12)^guess_k[12]]^Sb0[*(realc_set+(16*i)+13)^guess_k[13]]^Sb0[*(realc_set+(16*i)+15)^guess_k[15]];
			SUM=Sb0[*(realc_set+(16*i))^guess_k[0]]^Sb0[*(realc_set+(16*i)+1)^guess_k[1]]^Sb0[*(realc_set+(16*i)+2)^guess_k[2]]^Sb0[*(realc_set+(16*i)+3)^guess_k[3]];
			State[3]=SUM^Sb0[*(realc_set+(16*i)+1)^guess_k[1]];
			State[4]=SUM^Sb0[*(realc_set+(16*i)+2)^guess_k[2]];
			State[5]=SUM^Sb0[*(realc_set+(16*i)+3)^guess_k[3]];
			ss=State[0]|(State[1]<<4)|(State[2]<<8)|(State[3]<<12)|(State[4]<<16)|(State[5]<<20);
			*(save_num+(ss<<1)+*(pair_count+ss))=i;
			*(pair_count+ss)=*(pair_count+ss)+1;  //值为ss的输入有几个
			if(*(pair_count+ss)>1) 
			{
				for(j=0;j<16;j++)
				{
					*(good_pair1+count1*16+j)=*(realc_set+*(save_num+(ss<<1))*16+j);  //printf("%x,",	*(good_pair1+count1*16+j));
					*(good_pair2+count1*16+j)=*(realc_set+*(save_num+(ss<<1)+1)*16+j);  //printf("%x,",	*(good_pair2+count1*16+j));
				}
				count1++; //printf("\n");
			}
		}
		count=0;
		//   前四字节不能相等
		for(j=0;j<count1;j++)
		{
			if((*(good_pair1+j*16)==*(good_pair2+j*16))&&
				((*(good_pair1+j*16+1)==*(good_pair2+j*16+1))&&
				(*(good_pair1+j*16+2)==*(good_pair2+j*16+2))&&
				(*(good_pair1+j*16+3)==*(good_pair2+j*16+3)))
				)	
				continue;
			for(i=0;i<16;i++)
			{	*(good_pair1+count*16+i)=*(good_pair1+j*16+i);
				*(good_pair2+count*16+i)=*(good_pair2+j*16+i);
			}
			count++;
		}
		count1=0;
		for(i=0;i<count;i++)
		{
			for(j=4;j<16;j++) {C[0][j]=*(good_pair1+i*16+j);C[1][j]=*(good_pair2+i*16+j);}
			for(j=0;j<4;j++) {C[0][j]=*(good_pair2+i*16+j);C[1][j]=*(good_pair1+i*16+j);}
			Reduce_Round_InvMidori_withoutKeyschedule(6,C[0],64, P[0],64, 128);
			Reduce_Round_InvMidori_withoutKeyschedule(6,C[1],64, P[1],64, 128);
			if(((Sb0[guess_k[1]^P[0][1]]^Sb0[guess_k[4]^P[0][4]]^Sb0[guess_k[11]^P[0][11]]^Sb0[guess_k[1]^P[1][1]]^Sb0[guess_k[4]^P[1][4]]^Sb0[guess_k[11]^P[1][11]])==0)
			&&((Sb0[guess_k[7]^P[0][7]]^Sb0[guess_k[8]^P[0][8]]^Sb0[guess_k[13]^P[0][13]]^Sb0[guess_k[7]^P[1][7]]^Sb0[guess_k[8]^P[1][8]]^Sb0[guess_k[13]^P[1][13]])==0)
			&&((Sb0[guess_k[12]^P[0][12]]^Sb0[guess_k[9]^P[0][9]]^Sb0[guess_k[3]^P[0][3]]^Sb0[guess_k[12]^P[1][12]]^Sb0[guess_k[9]^P[1][9]]^Sb0[guess_k[3]^P[1][3]])==0)
			&&((Sb0[guess_k[0]^P[0][0]]^Sb0[guess_k[5]^P[0][5]]^Sb0[guess_k[15]^P[0][15]]^Sb0[guess_k[0]^P[1][0]]^Sb0[guess_k[5]^P[1][5]]^Sb0[guess_k[15]^P[1][15]])==0)
	)
				count1++;
		}
 		if(count1==count) 
		{	
			printf("guess key[10]=%x\n ",guess_k[10],count1);
			return 1;
		}
	}
	return 0;
}
 void SixRdistinguisher()
 {
	 byte8 Sb0[16] = { 0xc, 0xa,  0xd,  0x3,  0xe,  0xb, 0xf,  0x7,  0x8,  0x9,  0x1, 0x5, 0x0, 0x2, 0x4, 0x6}; 
	 printf("\n6Round distinguisher\n");
	 byte8 K[16]={0x68,0x7d,0xed,0xeb,0xec,0x85,0xba,0xfc,0xfb,0xef,0x98,0x86,0xbe,0x5a,0x8c,0xbf};
		unsigned char 
		P[4][16]= {{ 0x5,0x1,0x0,0x8,0x4,0xf,0x4,0x5,0x1,0x2,0x3,0x1,0x5,0xc,0xa,0x2},
								{0x4,0x2,0xc,0x2,0x0,0xf,0xd,0x3,0xb,0x5,0x8,0x6,0x8,0x7,0x9,0xe},
								{0xe,0xc,0x8,0x7,0xd,0x7,0xb,0xa,0xb,0xc,0x2,0x9,0x7,0x5,0x4,0x3},
								{},
		},
		deta[2][16];
	unsigned char C[16][16];
	int index0[4]={0,1,1,1},i,j,k,l,count=0,index123[3];
	int independent_v[4][4]={{0,4,12,8},{2,14,6,10},{3,15,7,14},{1,13,5,9}};
	int ROUND=2;
	unsigned long u1,u2,u3,u4;
	double c=2;
	unsigned char *pair_count=(unsigned char *)calloc(16777216,sizeof(char));
	unsigned char *good_pair1=(unsigned char *)calloc(8389000,sizeof(char));
	unsigned char *good_pair2=(unsigned char *)calloc(8389000,sizeof(char));
	unsigned int *perfect_pair_index0=(unsigned int *)calloc(83890,sizeof(int));
	unsigned int *perfect_pair_index1=(unsigned int *)calloc(83890,sizeof(int));
	unsigned int *perfect_pair_index2=(unsigned int *)calloc(8389,sizeof(int));
	unsigned int *perfect_pair_index3=(unsigned int *)calloc(8389,sizeof(int));

	count=Choose_Chiprtext_Pair(good_pair1,good_pair2); 
	FILE *fp1=fopen("Pair1 text.txt","rb");
	FILE *fp2=fopen("Pair2 text.txt","rb");
	FILE *fp0=fopen("Pair Num.txt","rb");
	fscanf(fp0,"%d",&count);  printf("%d\n",count);
	fread(good_pair1,1,count*16,fp1);
	fread(good_pair2,1,count*16,fp2);
	printf("Choose_Chiprtext_Pair Finished, the number of chipher pair is  %d\n",count);
	Key_Schedule(1);
	//GUESS KEY//GUESS KEY//GUESS KEY//GUESS KEY//GUESS KEY//GUESS KEY
	unsigned long ss;
	unsigned int guess_k[16],guess_key0,guess_key1,guess_key2,guess_key3,GN=0,Sbox[16][16];
	int num=pow(c,16),flag=0,sum=0;
	int count1=0,count2,count3,count4=0,count5=0,count6=0,count7=0;
	for(i=0;i<16;i++)
		for(j=0;j<16;j++)
			Sbox[i][j]=Sb0[j^i];
	for(guess_key0=0;guess_key0<pow(c,8);guess_key0++)
	{	
	//	printf("%d,",guess_key0);
		guess_k[1]=guess_key0&0xf;guess_k[2]=(guess_key0>>4)&0xf;
		count6=0;
		for(i=0;i<count;i++)
		{
			if( (Sbox[guess_k[1]][*(good_pair1+16*i+1)]^Sbox[guess_k[1]][*(good_pair2+16*i+1)])==(Sbox[guess_k[2]][*(good_pair1+16*i+2)]^Sbox[guess_k[2]][*(good_pair2+16*i+2)])) 
			{ *(perfect_pair_index0+count6)=i;count6++;  			}
		}
		for(guess_k[3]=0;guess_k[3]<16;guess_k[3]++)
		{
			count1=0;
			for(i=0;i<count6;i++)
			if((Sbox[guess_k[2]][*(good_pair1+*(perfect_pair_index0+i)*16+2)]^Sbox[guess_k[2]][*(good_pair2+*(perfect_pair_index0+i)*16+2)])==(Sbox[guess_k[3]][*(good_pair1+*(perfect_pair_index0+i)*16+3)]^Sbox[guess_k[3]][*(good_pair2+*(perfect_pair_index0+i)*16+3)]))
			{	*(perfect_pair_index1+count1)=*(perfect_pair_index0+i);count1++;			}
			//GUESS KEY 6,9
				for(guess_key1=0;guess_key1<pow(c,8);guess_key1++)
				{
					guess_k[6]=guess_key1>>4;guess_k[9]=guess_key1&0xf;
					count2=0;
					for(i=0;i<count1;i++)
					{
						for(j=0;j<16;j++) {C[0][j]=*(good_pair1+*(perfect_pair_index1+i)*16+j);C[1][j]=*(good_pair2+*(perfect_pair_index1+i)*16+j);}
						for(j=0;j<4;j++) {C[0][j]=*(good_pair2+*(perfect_pair_index1+i)*16+j);C[1][j]=*(good_pair1+*(perfect_pair_index1+i)*16+j);}
						Reduce_Round_InvMidori_withoutKeyschedule(6,C[0],64, P[0],64, 128);
						Reduce_Round_InvMidori_withoutKeyschedule(6,C[1],64, P[1],64, 128);
						if((Sbox[guess_k[6]][P[0][6]]^Sbox[guess_k[9]][P[0][9]]^Sbox[guess_k[3]][P[0][3]]^Sbox[guess_k[6]][P[1][6]]^Sbox[guess_k[9]][P[1][9]]^Sbox[guess_k[3]][P[1][3]])==0)
						{
							*(perfect_pair_index2+count2)=*(perfect_pair_index1+i);
							count2++;
						}				
		//GUESS KEY 7，13
					}if(count2<10) continue;
					for(guess_key2=0;guess_key2<pow(c,8);guess_key2++)
					{
							guess_k[7]=guess_key2>>4;guess_k[13]=guess_key2&0xf;
							count3=0;
							for(i=0;i<count2;i++)
							{
								for(j=4;j<16;j++) {C[0][j]=*(good_pair1+*(perfect_pair_index2+i)*16+j);C[1][j]=*(good_pair2+*(perfect_pair_index2+i)*16+j);}
								for(j=0;j<4;j++) {C[0][j]=*(good_pair2+*(perfect_pair_index2+i)*16+j);C[1][j]=*(good_pair1+*(perfect_pair_index2+i)*16+j);}
								Reduce_Round_InvMidori_withoutKeyschedule(6,C[0],64, P[0],64, 128);
								Reduce_Round_InvMidori_withoutKeyschedule(6,C[1],64, P[1],64, 128);
								if((Sbox[guess_k[7]][P[0][7]]^Sbox[guess_k[13]][P[0][13]]^Sbox[guess_k[2]][P[0][2]]^Sbox[guess_k[7]][P[1][7]]^Sbox[guess_k[13]][P[1][13]]^Sbox[guess_k[2]][P[1][2]])==0)
								{
									*(perfect_pair_index3+count3)=*(perfect_pair_index2+i);
										count3++;
								}
							}
							if(count3<6) continue;
							for(guess_key3=0;guess_key3<pow(c,8);guess_key3++)
							{
								guess_k[14]=guess_key3>>4;guess_k[11]=guess_key3&0xf;
								count4=0;
								for(i=0;i<count3;i++)
								{
									for(j=4;j<16;j++) {C[0][j]=*(good_pair1+*(perfect_pair_index3+i)*16+j);C[1][j]=*(good_pair2+*(perfect_pair_index3+i)*16+j);}
									for(j=0;j<4;j++) {C[0][j]=*(good_pair2+*(perfect_pair_index3+i)*16+j);C[1][j]=*(good_pair1+*(perfect_pair_index3+i)*16+j);}
									Reduce_Round_InvMidori_withoutKeyschedule(6,C[0],64, P[0],64, 128);
									Reduce_Round_InvMidori_withoutKeyschedule(6,C[1],64, P[1],64, 128);
									if((Sbox[guess_k[14]][P[0][14]]^Sbox[guess_k[11]][P[0][11]]^Sbox[guess_k[1]][P[0][1]]^Sbox[guess_k[14]][P[1][14]]^Sbox[guess_k[11]][P[1][11]]^Sbox[guess_k[1]][P[1][1]])==0)
									{
											count4++;
									}
								}
								if(count4>6)
								{ 
//									printf("\n%d,%d,%d,%d\n",count1,count2,count3,count4);
									goto STEP; }
							}
						}
			}
		}
	}
	STEP:
	printf("\n		guess_k[1]=%x,guess_k[2]=%x,guess_k[3]=%x,guess_k[6]=%x,guess_k[9]=%x,guess_k[7]=%x,guess_k[13]=%x,guess_k[14]=%x,guess_k[11]=%x",guess_k[1],guess_k[2],guess_k[3] ,guess_k[6],guess_k[9] ,guess_k[7],guess_k[13],guess_k[14],guess_k[11]);
//	printf("perfect_pair=%d\n",count4);
	count5++;
	//for(i=0;i<count3;i++)
	//{
	//for(j=0;j<16;j++){ printf("%x,%x  ",*(good_pair1+*(perfect_pair_index3+i)*16+j),*(good_pair2+*(perfect_pair_index3+i)*16+j));}
	//printf("\n");
	//}
	count=Choose_Chiprtext_PairII(good_pair1,good_pair2); 
	fp1=fopen("Pair1II text.txt","rb");
	fp2=fopen("Pair2II text.txt","rb");
	fp0=fopen("PairII Num.txt","rb");
	fscanf(fp0,"%d",&count);  
//	printf("%d\n",count);
	fread(good_pair1,1,count*16,fp1);
	fread(good_pair2,1,count*16,fp2);
	printf("Choose_Chiprtext_Pair II Finished, the number of chipher pair is  %d\n",count);
	count1=0;
	Key_Schedule(1);
	for(i=0;i<count;i++)
	{
		if( (Sbox[guess_k[1]][*(good_pair1+16*i+1)]^Sbox[guess_k[1]][*(good_pair2+16*i+1)])==(Sbox[guess_k[2]][*(good_pair1+16*i+2)]^Sbox[guess_k[2]][*(good_pair2+16*i+2)])&&
			(Sbox[guess_k[2]][*(good_pair1+16*i+2)]^Sbox[guess_k[2]][*(good_pair2+16*i+2)])==(Sbox[guess_k[3]][*(good_pair1+16*i+3)]^Sbox[guess_k[3]][*(good_pair2+16*i+3)])) 		
			{ *(perfect_pair_index1+count1)=i;count1++;  			}
	}
	//		printf("perfect_pair=%d\n",count1);
				for(guess_k[4]=0;guess_k[4]<16;guess_k[4]++)
				{
	//				printf("%d  ",guess_k[4]);
					count2=0;
					for(i=0;i<count1;i++)
					{
						for(j=0;j<16;j++) {C[0][j]=*(good_pair1+*(perfect_pair_index1+i)*16+j);C[1][j]=*(good_pair2+*(perfect_pair_index1+i)*16+j);}
						for(j=0;j<4;j++) {C[0][j]=*(good_pair2+*(perfect_pair_index1+i)*16+j);C[1][j]=*(good_pair1+*(perfect_pair_index1+i)*16+j);}
						Reduce_Round_InvMidori_withoutKeyschedule(6,C[0],64, P[0],64, 128);
						Reduce_Round_InvMidori_withoutKeyschedule(6,C[1],64, P[1],64, 128);
						if((Sbox[guess_k[1]][P[0][1]]^Sbox[guess_k[4]][P[0][4]]^Sbox[guess_k[11]][P[0][11]]^Sbox[guess_k[1]][P[1][1]]^Sbox[guess_k[4]][P[1][4]]^Sbox[guess_k[11]][P[1][11]])==0)
						{
							*(perfect_pair_index2+count2)=*(perfect_pair_index1+i);
							count2++;
						}					
		//GUESS KEY 7，13
					}if(count2<6) continue;
					for(guess_k[12]=0;guess_k[12]<16;guess_k[12]++)
					{
							count3=0;
							for(i=0;i<count2;i++)
							{
								for(j=4;j<16;j++) {C[0][j]=*(good_pair1+*(perfect_pair_index2+i)*16+j);C[1][j]=*(good_pair2+*(perfect_pair_index2+i)*16+j);}
								for(j=0;j<4;j++) {C[0][j]=*(good_pair2+*(perfect_pair_index2+i)*16+j);C[1][j]=*(good_pair1+*(perfect_pair_index2+i)*16+j);}
								Reduce_Round_InvMidori_withoutKeyschedule(6,C[0],64, P[0],64, 128);
								Reduce_Round_InvMidori_withoutKeyschedule(6,C[1],64, P[1],64, 128);
								if((Sbox[guess_k[12]][P[0][12]]^Sbox[guess_k[9]][P[0][9]]^Sbox[guess_k[3]][P[0][3]]^Sbox[guess_k[12]][P[1][12]]^Sbox[guess_k[9]][P[1][9]]^Sbox[guess_k[3]][P[1][3]])==0)
								{
									*(perfect_pair_index3+count3)=*(perfect_pair_index2+i);
										count3++;
								}
							}
							if(count3<3) continue;
							for(guess_k[8]=0;guess_k[8]<16;guess_k[8]++)
							{
								count4=0;
								for(i=0;i<count3;i++)
								{
									for(j=4;j<16;j++) {C[0][j]=*(good_pair1+*(perfect_pair_index3+i)*16+j);C[1][j]=*(good_pair2+*(perfect_pair_index3+i)*16+j);}
									for(j=0;j<4;j++) {C[0][j]=*(good_pair2+*(perfect_pair_index3+i)*16+j);C[1][j]=*(good_pair1+*(perfect_pair_index3+i)*16+j);}
									Reduce_Round_InvMidori_withoutKeyschedule(6,C[0],64, P[0],64, 128);
									Reduce_Round_InvMidori_withoutKeyschedule(6,C[1],64, P[1],64, 128);
									if((Sbox[guess_k[7]][P[0][7]]^Sbox[guess_k[8]][P[0][8]]^Sbox[guess_k[13]][P[0][13]]^Sbox[guess_k[7]][P[1][7]]^Sbox[guess_k[8]][P[1][8]]^Sbox[guess_k[13]][P[1][13]])==0)
									{
										*(perfect_pair_index0+count4)=*(perfect_pair_index3+i);
										count4++;
									}
										if(count4>5)
										{ 
											//printf("%d,%d,%d,%d\n",count1,count2,count3,count4);
											goto STEP2; }
								}
							}
						}
			}
STEP2:
	printf("		guess_k[8]=%x,guess_k[4]=%x,guess_k[12]=%x\n",guess_k[8],guess_k[4],guess_k[12] );
//	printf("perfect_pair=%d\n",count4);
	count5++;
	//for(i=0;i<count3;i++)
	//{
	//for(j=0;j<16;j++){ printf("%x,%x  ",*(good_pair1+*(perfect_pair_index3+i)*16+j),*(good_pair2+*(perfect_pair_index3+i)*16+j));}
	//printf("\n");
	//}
	for(guess_key1=0;guess_key1<pow(c,12);guess_key1++)
	{
		flag=0;
		guess_k[0]=guess_key1>>8;guess_k[5]=(guess_key1>>4)&0xf;guess_k[15]=guess_key1&0xf;
		for(i=0;i<count4;i++)
		{
			for(j=4;j<16;j++) {C[0][j]=*(good_pair1+*(perfect_pair_index0+i)*16+j);C[1][j]=*(good_pair2+*(perfect_pair_index0+i)*16+j);}
			for(j=0;j<4;j++) {C[0][j]=*(good_pair2+*(perfect_pair_index0+i)*16+j);C[1][j]=*(good_pair1+*(perfect_pair_index0+i)*16+j);}
			Reduce_Round_InvMidori_withoutKeyschedule(6,C[0],64, P[0],64, 128);
			Reduce_Round_InvMidori_withoutKeyschedule(6,C[1],64, P[1],64, 128);
			if((Sbox[guess_k[0]][P[0][0]]^Sbox[guess_k[5]][P[0][5]]^Sbox[guess_k[15]][P[0][15]]^Sbox[guess_k[0]][P[1][0]]^Sbox[guess_k[5]][P[1][5]]^Sbox[guess_k[15]][P[1][15]]))
			{
				flag=1;break;
			}
		}
		if(flag==0) break;
	}
	printf("guess_k[0]=%x,guess_k[5]=%x,guess_k[15]=%x\n",guess_k[0],guess_k[5],guess_k[15] );
	Guess_key10(guess_k);
	 printf("6Round distinguisher finished\n");
 }

  int Probability()
 {
	 byte8 Sb0[16] = { 0xc, 0xa,  0xd,  0x3,  0xe,  0xb, 0xf,  0x7,  0x8,  0x9,  0x1, 0x5, 0x0, 0x2, 0x4, 0x6}; 
	 unsigned long input;
	 double c=2;
	 int i,j,k;
	 unsigned int alpha,beta,gamma, a, b;
	 long long count=0;
	 for(input=0;input<pow(c,5*4);input++)
	 {
		 alpha=(input)&0xf;
		 beta=(input>>4)&0xf;
		 gamma=(input>>8)&0xf;
		 a=(input>>12)&0xf;
		 b=(input>>16)&0xf;
		 if(((Sb0[alpha^Sb0[a]]^ Sb0[beta^Sb0[a] ]^  Sb0[beta ^Sb0[ b ]]^ Sb0[ alpha^Sb0[b]])==0)
			 && 
			 ((Sb0[gamma^Sb0[a] ]^ Sb0[ alpha^beta^gamma^Sb0[b ]]^ Sb0[gamma^Sb0[ b ]]^ Sb0[alpha^beta^gamma^Sb0[a ]])==0)
		 ) 
		 count++;
	 }
	 printf("Probability =%f\n",count/pow(c,5*4));
	 return 0;
 }


int main()
{
	int i,j,k,l,e[4]={1,1,1,1};

	byte8 PP[16]= { 0x4,0x2,0xc,0x2,0x0,0xf,0xd,0x3,0xb,0x5,0x8,0x6,0x8,0x7,0x9,0xe },
	CC[16]={0};
	Probability();
	//for(i=0;i<16;i++)
	//printf("%x",PP[i]);
	//printf("\n");
	//Key_Schedule(0);
	//Reduce_Round_Midori(4,PP,64,CC,128,K,128);
	//for(i=0;i<16;i++)
	//	printf("%x",CC[i]);//c055cbb95996d14902b60574d5e728d6 for 0 key 0 plaintext
	//printf("\n");
	//Key_Schedule( 1);
	//Reduce_Round_InvMidori(4,CC,64,PP,128,K,128);
	//for(i=0;i<16;i++)
	//	printf("%x",PP[i]);
	//printf("\n");

	unsigned char 
	P[4][16]= {{ 0xe,0xc,0x8,0x7,0xd,0x7,0xb,0xa,0xb,0xc,0x2,0x9,0x7,0x5,0x4,0x3},
								{0x4,0xc,0x8,0x7,0x0,0xf,0xd,0x3,0xb,0x5,0x8,0x6,0x8,0x7,0x9,0xe},
								{0x4,0xc,0x8,0x7,0xd,0x7,0xb,0xa,0xb,0xc,0x2,0x9,0x7,0x5,0x4,0x3},
								{0xe,0xc,0x8,0x7,0x0,0xf,0xd,0x3,0xb,0x5,0x8,0x6,0x8,0x7,0x9,0xe},
	},
		C[4][16];
	/*byte8 K[16]={0x68,0x7d,0xed,0xeb,0xec,0x85,0xba,0xfc,0xfb,0xef,0x98,0x86,0xbe,0x5a,0x8c,0xbf};
	for(i=0;i<16;i++)
	printf("%x",PP[i]);
	printf("\n");
	Midori64(PP,64,CC,128,K,128);
	for(i=0;i<16;i++)
		printf("%x",CC[i]);
	printf("\n");
	InvMidori(CC,64,PP,128,K,128);
	for(i=0;i<16;i++)
	printf("%x",PP[i]);
	printf("\n");*/

	int index0[4]={1,1,1,1};
	int independent_v[4][4]={{0,4,12,8},{2,14,6,10},{3,15,7,14},{1,13,5,9}};
	int ROUND=2;
	int index[4]={1,0,0,0};
	PrintWhiteningKey();
	SixRdistinguisher();
	system("pause");
	return 0;
}

