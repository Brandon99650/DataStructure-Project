#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(){
    int resourceY;
    int resourceX;
    int user_id;
    scanf("%d%d%d",&resourceY,&resourceX,&user_id);
    //printf("%d %d %d",resourceY,resourceX,user_id);
    int A[500][500];
    int Output[user_id][6];
    char s;
    for(int num=0;num<user_id;num++){
        scanf("%d ",&A[num][0]);
        int i=1;
        do{
            scanf("%dx%d",&A[num][i],&A[num][i+1]);
            i=i+2;
        }
        while(getchar()!='\n');//直到吃到的字元為換行時停止
        /*for(int j=0;j<i;j++){
            printf("%d ",A[num][j]); 
        } */
        A[i][0]=i;
    }
    int count=0;
    int temp =0;
    int flag[user_id];
    //baseline
    for(int i=0;i<user_id;i++){
        flag[i]=0;
        if(A[i][1]<=resourceY&&(temp+A[i][2])<=resourceX){//每個request的第一個shape是否符合要求
            flag[i]=1;//標記第i個request已被加入
            Output[i][0]=i;//ID
            Output[i][1]=A[i][1];//height
            Output[i][2]=A[i][2];//length
            Output[i][3]=0;//y軸起始坐標
            Output[i][4]=temp;//x軸起始坐標
            temp=temp+A[i][2];//下一個被加入的request的x軸坐標
            Output[i][5]=A[i][1];//下一個疊在該點的y軸起始坐標
            count++;//目前有多少個被接受的request
        }
    }
    //進階做法
    for(int i=0;i<user_id;i++){//重複n次，逐個判斷之前失敗的點
        for(int j=0;j<user_id;j++){//尋找第一次成功的request，以下稱為基底
            int k=1;
            //檢查失敗的點i的多個shape是否和處於j位置的基底shape相同並進一步判斷
            while(k<A[i][0]){
                if(flag[i]==0&&flag[j]==1&&A[i][k]==A[j][1]&&A[i][k+1]==A[j][2]&&A[j][1]+Output[j][5]<=resourceY){
                    flag[i]=2;//如果flag[i]=0說明該點為失敗點，flag[j]=1說明該點為基底，判斷是否形狀相同且不超出y軸邊界
                //判斷成功令第二次判斷成功的點flag[i]標記為2並存值    
                    Output[i][0]=i;
                    Output[i][1]=A[i][k];
                    Output[i][2]=A[i][k+1];
                    Output[i][3]=Output[j][5];
                    Output[i][4]=Output[j][4];
                    Output[j][5]=Output[j][5]+A[i][1];
                    count++;
                    break;
                }
                k=k+2;
            }
        }
    }
    printf("%d\n",count);//count為兩輪總共成功接受的request個數
    for(int i=0;i<user_id;i++){
        if(flag[i]==1||flag[i]==2){
            printf("%d ",Output[i][0]);
            printf("%dx%d %d %d\n",Output[i][1],Output[i][2],Output[i][3],Output[i][4]);
        }
    }
    //3x4 4x5 2x6 6x2
    /*
16 32 5
0 4x4 2x8
1 1x16
2 8x2 4x4 2x8
3 2x8 1x16
4 16x1 8x2 4x4 2x8 1x16
    */




    return 0;
}