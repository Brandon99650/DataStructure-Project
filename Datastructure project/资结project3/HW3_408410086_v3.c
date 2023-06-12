#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include<stdbool.h>
int count=0;

void DFS(int Base_num,double **MST,int path[]){
    int current = path[count];
    for(int i=0;i<Base_num;i++){
        
        if(MST[current][i]!=0){
            count++;
            path[count]=i;
            DFS(Base_num,MST,path);
        }
    }
}

int main(){
    int base_num;
    int base_ID ,gap;
    scanf("%d %d",&base_num,&gap);

    double **A= ( double  **)  malloc ( sizeof ( double  *) *base_num); 
    for (int i = 0; i < base_num; i ++){
         A[i] = ( double  *) malloc ( sizeof ( double ) * 3);
    }
    for (int i=0;i<base_num;i++){
        scanf("%d %lf %lf",&A[i][0],&A[i][1],&A[i][2]);
    }
    
    //set a adjmatrix ;
    double **adj = ( double  **)  malloc ( sizeof ( double  *) *base_num); 
    for (int i = 0; i < base_num; i ++){
         adj[i] = ( double  *) malloc ( sizeof ( double ) * base_num);
    }
    
    double **MST= ( double  **)  malloc ( sizeof ( double  *) *base_num); 
    for (int i = 0; i < base_num; i ++){
          MST[i] = ( double  *) malloc ( sizeof ( double ) * base_num);
    }
    for(int i=0;i<base_num;i++){
        for(int j=0;j<base_num;j++){
            MST[i][j]=0;
        }
    }
    //memset(MST, 0, base_num*(base_num)*sizeof(MST[0][0]));
    for(int i=0;i<base_num;i++){
        for(int j=0;j<base_num;j++){
            adj[i][j]=sqrt((A[i][1]-A[j][1])*(A[i][1]-A[j][1])+(A[i][2]-A[j][2])*(A[i][2]-A[j][2]));
           // printf("%8lf ",adj[i][j]);
        }
        //printf("\n");
    }
    int i, j, k;
    double min;
    int *adjvex=malloc(base_num*sizeof(int)); // 保存相关顶点下标
    double *lowcost=malloc(base_num*sizeof(double)); // 保存相关顶点间边的权值
    lowcost[0] = 0;   // V0作为最小生成树的根开始遍历
    adjvex[0] = 0;   // V0第一个加入
    // 初始化操作
    for( i=1; i < base_num; i++ )
    {
        lowcost[i] = adj[0][i]; // 将邻接矩阵第0列所有权值先加入数组
        adjvex[i] = 0;    // 初始化全部起点为V0
    }
    
    // 构造最小生成树的过程
    for( i=1; i < base_num; i++ )
    {
        min = 665665555;  
        j = 1;
        k = 0;
        
        // 遍历全部顶点
        while( j < base_num )
        {
        // 找出lowcost数组已存储的最小权值
            if( lowcost[j]!=0 && lowcost[j] < min )
            {
                min = lowcost[j];
                k = j;  // 将发现的最小权值的下标存入k，以待使用。
            }
                j++;
        }
        MST[adjvex[k]][k]=lowcost[k];
        lowcost[k] = 0;  // 将当前顶点的权值设置为0，表示此顶点已经完成任务，进行下一个顶点的遍历
    
        // 邻接矩阵k列逐个遍历全部顶点(k=1,)
        for( j=1; j < base_num; j++ )
        {
            if( lowcost[j]!=0 && adj[k][j] < lowcost[j] )
            {
                lowcost[j] = adj[k][j];//替换当前使j点权重最短的边以及该边的端点k
                adjvex[j] = k; 
            }
        }
    }
    
    int *path=malloc(base_num*sizeof(path[0]));
    path[0]=0;
    int source=0;
   // int count=0;
    DFS(base_num,MST,path);
    int total = 0;
    int output_id = 0;
    int flag = 0;//无人机数量不够
    double distance = 0;
    int num=0;
    int **Output= ( int  **)  malloc ( sizeof ( int  *) *base_num); 
    for (int i = 0; i < base_num; i ++){
          Output[i] = ( int  *) malloc ( sizeof ( int ) * base_num);
    }
    for(int i=0;i<base_num;i++){
        for(int j=0;j<base_num;j++){
            Output[i][j]=-1;
        }
    }
    for (int i = 0; i < base_num;i++){
        if(!flag){//如果数量不够，当前base没有无人机搜集资料
            Output[output_id][num]=output_id;
            total++;//无人机+1
            num++;
            flag = 1;//暂时够了
        }
        Output[output_id][num]=path[i];
        num++;
        if(i < base_num-1){
            distance += adj[path[i]][path[i+1]];//加上当前点与下一个点之间的距离
        }
        if(distance>(gap/2)){
            distance = 0;
            flag = 0;//飞不到下一个点
            output_id++;
            num=0;//当下无人机飞行任务结束，无人机数量不足
        }
        
        
    }
    printf("%d\n", total);
    for(int i=0;i<total;i++){
        for(int j=0;j<base_num;j++){
            if(Output[i][j]!=-1){
                printf("%d ",Output[i][j]);
            }
        }
        printf("\n");
    }
    free(A);
    free(adj);
    free(lowcost);
    free(adjvex);
    free(MST);
    free(path);
    free(Output);



    return 0;
}
/*
10 10
0 0.31943890 2.29615086
1 1.22727638 2.82131700
2 3.11475237 0.10137054
3 3.33213435 0.71334089
4 6.85464191 0.62696129
5 7.36465772 2.01343701
6 8.14020191 2.09479811
7 8.93059113 1.88562411
8 9.20708976 3.03945723
9 9.55529399 8.33022108
*/
