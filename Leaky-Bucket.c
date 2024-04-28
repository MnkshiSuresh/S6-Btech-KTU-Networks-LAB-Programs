#include<stdio.h>
void main(){
int in,out,bsize,n,bucket=0;
printf("Enter the bucket size:");//bucket size
scanf("%d",&bsize);
printf("Enter the number of inputs:");//number of inputs
scanf("%d",&n);
printf("Enter the packet outgoing rate:");//packet outgoing rate
scanf("%d",&out);
while(n!=0)
{
printf("\nEnter the incoming packet size:");
scanf("%d",&in);
printf("Incoming packet size:%d\n",in) ;
if(in<=(bsize-bucket))
{
}
else
{
bucket+=in; //add to bucket
printf("Bucket status:%d out of %d\n",bucket,bsize);
printf("Packet size greater than remaining bucket size !!\nPacket
dropped\n");
}
bucket=bucket-out;
if (bucket<0)
bucket=0;
printf("After outgoing,bucket status:%d packets out of %d\n",bucket,bsize) ;
n--;
}
}
