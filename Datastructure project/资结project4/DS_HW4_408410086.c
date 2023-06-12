#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
unsigned long MurmurOAAT32(char *key){

    unsigned long h = 3323198485ul ;
    for(;*key ; ++key){
        h ^= *key ;
        h *= 0x5bd1e995 ;
        h ^= h >> 15 ;
    }

    return h ;
}
int num=0;
void DFS(int level,unsigned long **Hash,int strings,int current,int Index,int *judge){
    
    if(current<=level-1&&Hash[Index][current]!=0){
        printf("1 %d %d\n",current,Index);//show 当前位置
        fflush(NULL);
        unsigned long check;
        scanf("%lu",&check);//获取Hashvalue
        if(Hash[Index][current]!=check){//如果该值不一样，说明child hash有错
            if(current==level-1){//如果当前是最底层，记录错误string并num++
                
                judge[Index]=1;
                num++;
            }
            else{
            
                DFS(level,Hash,strings,current+1,2*Index,judge);//检查左child
                DFS(level,Hash,strings,current+1,2*Index+1,judge);//检查右child
            }
        }
    }
}

int main(){

    int strings=0,StrMaxLen=0;
    int count=1;
    int level=1;
    scanf("%d %d",&strings,&StrMaxLen);
    //获取层数
    if(strings==0){
        level=0;
    }
    else{
        while(strings>count){
            level++;
            count=count*2;

        }
    }
    //Input
    char **A= ( char  **)  malloc ( sizeof ( char  *) *strings); 
    for (int i = 0; i < strings; i ++){
         A[i] = ( char  *) malloc ( sizeof ( char ) * StrMaxLen);
    }
    for(int i=0;i<strings;i++){
        scanf("%s",A[i]);
    }
    //建merkel tree
    unsigned long **Hashtree=( unsigned long  **)  malloc ( sizeof ( unsigned long  *) *(strings+1));
    for (int i = 0; i < strings+1; i ++){
         Hashtree[i] = ( unsigned long  *) malloc ( sizeof ( unsigned long ) * level);//避免出现奇数个nodes
    }
    //初始化
    for(int i=0;i<strings+1;i++){
        for(int j=0;j<level;j++){
            Hashtree[i][j]=0;
        }
    }
    for(int i=0;i<strings;i++){
        Hashtree[i][level-1]=MurmurOAAT32(A[i]);//最底层先hash
    }
    
    for(int i=level-1;i>0;i--){

        int pos1=0,pos2=0;//pos1记录下层位置，pos2记录上层位置；
        while(Hashtree[pos1][i]!=0){
            
            if(Hashtree[pos1+1][i]==0){
                
                char *temp = ( char  *) malloc ( sizeof ( char ) * (StrMaxLen));
                sprintf(temp , "%lu" , Hashtree[pos1][i] + Hashtree[pos1][i]) ;
                Hashtree[pos2][i-1]=MurmurOAAT32(temp);
                free(temp);
                pos1+=2;
                break;
                
                
            }
            else{
                char *temp = ( char  *) malloc ( sizeof ( char ) * (StrMaxLen));
                sprintf(temp , "%lu" , Hashtree[pos1][i] + Hashtree[pos1+1][i]) ;
                Hashtree[pos2][i-1]=MurmurOAAT32(temp);
                pos1+=2;
                pos2++;
                free(temp);
                
            }
        }
    }
    int judge[strings];
    for(int i=0;i<strings;i++){
        judge[strings]=0;
    }
    DFS(level,Hashtree,strings,0,0,judge);

    printf("2 %d\n",num);
    for(int i=0;i<strings;i++){
        if(judge[i]==1){
            printf("%s\n",A[i]);
        }
    }
free(A);
free(Hashtree);
return 0;
}
