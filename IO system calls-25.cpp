#include<sys/stat.h>
#include<fcntl.h>
#include<sys/types.h>
#include<stdio.h>
int main()
{
int n, i=0;
int f1, f2;
char c, strin[100];
f1=open("data",O_RDWR|O_CREAT|O_TRUNC);
c=getchar();
while(c!='\n') {
strin[i++]=c;
}
strin[i]='\0';
write(f1, strin, i);
close(f1);
f2=open("data",O_RDONLY);
read(f2, strin, 0);
printf("\n%s\n",strin[i]);
close(f2);
return 0;
}
