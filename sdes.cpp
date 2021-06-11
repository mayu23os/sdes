#include<iostream>
#include<cstdlib>
#define N 10
using namespace std;
int p4[4]={2,4,3,1},p10[]={3,5,2,7,4,10,1,9,8,6},p8[]={6,3,7,4,8,5,10,9};
int exp[8]={4,1,2,3,2,3,4,1};
int ip[]={2,6,3,1,4,8,5,7},invip[]={4,1,3,5,7,2,8,6};
int key[N];//={1,0,1,0,0,0,0,0,1,0};
int key1[8],key2[8];
int s0[][4]={
    1,	0,	11,	10,
	11,	10,	1,	0,
	0,	10,	1,	11,
	11,	1,	11,	10,
            };
int s1[][4]={
    0,	1,	10,	11,
	10,	0,	1,	11,
	11,	0,	1,	0,
	10,	1,	0,	11
            };
int pt[N];//={0,1,0,0,0,0,0,1};
int en[N],de[N];
void swap(int *a,int *b,int len=4)
{
    int temp;
    for(int i=0;i<len;i++)
    {
        temp=a[i];
        a[i]=b[i];
        b[i]=temp;
    }
} 
void exor(int *a,int *b,int *res,int len=8)
{
    for(int i=0;i<len;i++)
    {
        res[i]=a[i]^b[i];
    }
}
void ep(int *a,int *res)
{
    for (int i = 0; i < 8; i++)
    {
        res[i]=a[exp[i]-1];
    } 
}
void left_2(int *a,int *res)
{
    for(int i=0;i<5;i++)
    {
        res[(3+i)%5]=a[i];
    }
}
void half(int org[],int* wo,int* w1,int len)//len -- length to be divided in
{ 
    for(int i=0;i<len;i++)
    {
        wo[i]=org[i];
        w1[i]=org[i+len];
    }
}
void merge(int *a1,int *a2,int *b,int len=4)
{
    for(int i=0;i<len;i++)
    {
        b[i]=a1[i];
        b[i+len]=a2[i];
    }    
}
void left_1(int *a,int *res)
{
    for(int i=0;i<5;i++)
    {
        res[ (4+i) % 5 ] = a[i];
    }
}
void per_ip(int *a,int *res,int flag)
{
    if(flag==1)
    {
        for (int i = 0; i < 8; i++)
        {
            res[i]=a[ip[i]-1];
        }   
    }
    else if(flag==-1)
    {
        for (int i = 0; i < 8; i++)
        {
            res[i]=a[invip[i]-1];
        }   
    }
}
int getcol(int a[])
{
    int i=a[1];
    int j=a[2];
    if(i*10+j==0)
        return 0;
    else if(i*10+j==1)
        return 1;
    else if(i*10+j==10)
        return 2;
    else
        return 3;
}
int getrow(int a[])
{
    int i=a[0];
    int j=a[3];
    if(i*10+j==0)
        return 0;
    else if(i*10+j==1)
        return 1;
    else if(i*10+j==10)
        return 2;
    else
        return 3; 
}
void permute(int *a,int *res,int len)
{
    if(len==10)
    {
        for (int i = 0; i < len; i++)
        {
            res[i]=a[p10[i]-1];
        }    
    }
    else if(len==8)
    {
        for (int i = 0; i < len; i++)
        {
            res[i]=a[p8[i]-1];
        }    
    }
    else if(len==4)
    {
        for (int i = 0; i < len; i++)
        {
            res[i]=a[p4[i]-1];
        }    
    }
}
void printarr(int *a,int len)
{
    for(int i=0;i<len;i++)
    {
       cout<<a[i]<<" ";
    }
}
void genkey()
{
    cout<<"\n========================/ KEY GENERATION /=======================\n";
    int ip[N],lh[5],rh[5];
    int ex1[N],ex2[N],ext[N],ex1a[N],ex2a[N];
    permute(key,ip,10);
    half(ip,lh,rh,5);
    //-----------------------ls fn
    left_1(lh,ex1);
    left_1(rh,ex2);
    merge(ex1,ex2,ext,5);
    permute(ext,key1,8);
    cout<<"\nK1\t";
    printarr(key1,8);
    left_2(ex1,ex1a);
    left_2(ex2,ex2a);
    merge(ex1a,ex2a,ext,5);
    permute(ext,key2,8);
    cout<<"\nK2\t";
    printarr(key2,8);
}
void fk(int *key,int *ip,int *res)
{   int lh[N],rh[N];
    int lh1[N],rh1[N];
    int ex1[N],ex2[N],ext[N],ext1[N];
    int lefts0[2],rights1[2];
    int lc,lr,rr,rc;
    half(ip,lh,rh,4);   //step 1
    ep(rh,ex1);     //step 3
    cout<<"\n\nEP\t";
    printarr(ex1,8);
    exor(ex1,key,ex2);
    cout<<"\nExOR\t";
    printarr(ex2,8);
    half(ex2,lh1,rh1,4);
    lr=getrow(lh1);
    rr=getrow(rh1);
    lc=getcol(lh1);
    rc=getcol(rh1);
    lefts0[0]=s0[lr][lc]/10;
    lefts0[1]=s0[lr][lc]%10;
    rights1[0]=s1[rr][rc]/10;
    rights1[1]=s1[rr][rc]%10;
    merge(lefts0,rights1,ex2,2);    //step 8
    cout<<"\nS0S1 Box\t";
    printarr(ex2,4);
    permute(ex2,ext,4);     // step 9
    exor(lh,ext,ext1,4);    //step 10
    merge(ext1,rh,res);
    cout<<"\nfk Result\t";
    printarr(res,8);
}
void switch_(int *res)
{
    int lh[4],rh[4];
    half(res,lh,rh,4);
    swap(lh,rh);
    merge(lh,rh,res);
}
void encrypt(int en[])
{
    cout<<"\n\n=========================/ ENCRYPTION /==========================\n";
    int res1[N],res2[N],ext[N];
    per_ip(pt,ext,1);
    cout<<"\nIP\t";
    printarr(ext,8);
    fk(key1,ext,res1);      //for the leftmost 4 bits
    switch_(res1);
    fk(key2,res1,res2);     //for rightmost 4 bits
    per_ip(res2,en,-1);
    cout<<"\n\nCIPHER TEXT\t";
    printarr(en,8);
}
void decrypt(int en[])
{   
    int res1[N],res2[N],ext[N],ext1[N];
    int elh[N],erh[N],lh[N],rh[N],dlh[N],drh[N];
    cout<<"\n\n=========================/ DECRYPTION /==========================\n";
    per_ip(en,ext,1);
    cout<<"\nIP\t";
    printarr(ext,8);
    fk(key2,ext,res2);
    switch_(res2);
    fk(key1,res2,res1);
    per_ip(res1,de,-1);
    cout<<"\n\nDECRIPHERED TEXT\t";
    printarr(de,8);
    cout<<"\nPLAIN TEXT\t";
    printarr(pt,8);
    cout<<"\n";
}
int main()
{
    cout<<"Enter the 8 bit Plain text ";
    for(int i=0;i<8;i++)
        cin>>pt[i];
    cout<<"Enter the 10 bit Key ";
    for(int i=0;i<N;i++)
    cin>>key[i];
    genkey();
    encrypt(en);
    decrypt(en);
}

//PT 1 0 1 1 1 1 0 1
//ciphertext 0 0 0 1 0 1 0 1
//key  1 0 1 0 0 0 0 0 1 0 

//key - 1 0 1 0 0 0 0 0 1 0
//cipher - 0 0 0 1 0 1 0 1
//pt -0 1 0 0 0 0 0 1

//k 0 0 0 1 0 0 1 0 1 1 1
//p 1 0 1 0 0 1 0 1

//ppt
//k 0 0 1 0 0 1 0 1 1 1
//p 1 0 1 0 0 1 0 1