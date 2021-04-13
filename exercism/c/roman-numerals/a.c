#include <stdio.h>

void main( void ){

int i,n,a[13]={1000,900,500,400,100,90,50,40,10,9,5,4,1};

char *r[13]={"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"};

printf("アラビア数字を入力してください：");

scanf("%d",&n);

if(n>0 && n<4000){

for(i=0;i<13;i++)

while(n>=a[i]){

printf("%s",r[i]);

n-=a[i];

}

printf("\n");

}else{

printf("変換できません\n");

}

}
