#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){
    //printf("1\n");
    int num_node,num_links,num_req;
    int mem_node,index_node;
    scanf("%d %d %d",&num_node,&num_links,&num_req);
    //set a adjmatrix of verteces.
    int adjmatrix[1024][1024]={0};
    //printf("save the quantum memory of each nodes.\n");
    int Nodes[num_node];
    for(int i =0 ;i<num_node ;i++){
        scanf("%d %d",&index_node,&mem_node);
        Nodes[index_node]=mem_node;
    }
    //printf("save the links and channel of the adjmatrix.");
    int linkID,End1,End2,channel;
    for(int i =0 ;i<num_links ;i++){
        scanf("%d %d %d %d",&linkID,&End1,&End2,&channel);
        adjmatrix[End1][End2]=channel;
        adjmatrix[End2][End1]=channel;
    }
    //printf("save the request information\n");
    int Request[num_req][3],RequestID, Reqsource,Reqdest;
    //printf("333\n");
    for(int i=0 ;i<num_req;i++){
        scanf("%d %d %d",&RequestID,&Reqsource,&Reqdest);
        Request[i][0]=RequestID;
        Request[i][1]=Reqsource;
        Request[i][2]=Reqdest;
        
    }
    //printf("request\n");
    //寻找所有的request所有可能的最短路径by BFS method !
    int req_cout=0;
    //printf("44\n");
    int path[num_req][num_node+2];
    memset(path, -1, num_req*(num_node+2)*sizeof(path[0][0]));
    //printf("55\n");

    for(int i=0;i<num_req;i++){
        //.printf("asdfghj\n");
        int found =0;
        int *visited=calloc(num_node,sizeof(int));//set a visited array
        int *queue=malloc(num_node*sizeof(int));//set a queue
        memset(queue, -1, num_node*sizeof(queue[0]));
        int *rear,*front;
        front=queue;rear=front;//设置queue的头和尾指标
        int source=Request[i][1];
        int destination=Request[i][2];
        *queue=Request[i][1];//define 初始点
        visited[source]=1;  
        int *predecessor=malloc(num_node*sizeof(int));
        memset(predecessor, -1, num_node*sizeof(predecessor[0]));//set a 回溯阵列
        int shortest_dist=1000;//最短距离
        //printf("BFS\n");
        while(*front!=-1){
            //printf("the source is :%d ,the destination is %d \n",source,destination);
            //printf("front is %d \n",*front);
            if(*front==destination){
                break;
            }
            for(int j=0;j<num_node;j++){
                //printf("11\n") ;
                if (adjmatrix[*front][j]!=0&&visited[j]!=1){
                     rear++;
                    *rear=j;//被拜访的node存进queue
                    //printf("rear is %d \n",*rear);
                    predecessor[j]=*front;
                    visited[j]=1;
                    if (j==destination){
                        int num=0,temp,temp_path[num_node];
                        temp=destination;
                        while(temp!=source){
                            
                            temp_path[num]=temp;//倒序存
                            temp=predecessor[temp];
                            num++;
                        }
                        temp_path[num]=temp;
                        shortest_dist=num;
                        path[i][0]=i;
                        path[i][1]=shortest_dist;
                        for(int k=2;k<=shortest_dist+2;k++){
                            path[i][k]=temp_path[shortest_dist+2-k];
                        }
                        //path计数器
                        break;
                    }
                    
                    
                }
                

            }
            if(found==1){
                break;
            }
            front++;
        }
        free(visited);
        free(queue);
        free(predecessor);
    }
    
    
    //检查所有的最短路径
    int real_count=0;
    int flag[num_req];
    int real_path[num_req][num_node+2];
    for(int i=0;i<num_req;i++){
        int find=1;
        if(path[i][0]==-1){
            //printf("%d failed\n",i);
            continue;
        }
            //printf("%d succsess1!\n",i);
        int dist =path[i][1];
        if(Nodes[path[i][2]]<1||Nodes[path[i][dist+2]]<1){
            continue;
            //printf("source and dest fill\n");
        }        
        for (int a =2;a<dist+2;a++){
            int G_i, G_j;
            G_i=path[i][a],G_j=path[i][a+1];
            if(adjmatrix[G_i][G_j]<1){
                //printf("chnnel failed \n");
                find=0;
                break;
                        
            }
        }
        if(find==0){
            continue;
        }
        for(int a=3;a<=dist+1;a++){
            if(Nodes[path[i][a]]<2){
                find=0 ;
                //printf("memory failed !\n");
                break;
            }

        }
        if(find==0){
            continue;
        }
        if(find==1){
            for(int num_real=0;num_real<=dist+2;num_real++){
                real_path[real_count][num_real]=path[i][num_real];
            }
            for( int k=2;k<dist+2;k++){
                Nodes[path[i][k]]--;
                Nodes[path[i][k+1]]--;
                adjmatrix[path[i][k]][path[i][k+1]]--;
                adjmatrix[path[i][k+1]][path[i][k]]--;
            }    
            real_count++;
            continue;
        }
    }




    printf("%d\n",real_count);
    for(int i =0;i<real_count;i++){
        printf("%d ",real_path[i][0]);
        for(int j =0;j<=real_path[i][1];j++){
            //printf("j=: %d \n",j);
            printf("%d ",real_path[i][j+2]);
        }
        printf("\n");
        
    }
/*
3 3 2
0 6
1 4
2 5
0 0 1 2
1 0 2 3
2 1 2 5
0 0 2
1 1 2
*/






    return 0;
}