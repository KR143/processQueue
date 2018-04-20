#include<stdio.h>
#include<conio.h>
int n=4;
int Job[12][8];
int StartQueue[20],StartQueue1[20],Burst_Time[10],Arrival_Time[10];
int Start=0;
int End=-1,CPU_TIME=0,boole=0,onWards;  

int isExecuted(){
	// checking whether all the Job has completed their execution or not......
	
	int i;
	for(i=0;i<2;i++){
		if(Job[i][2]>0)
			break;
	}
	
	if(i<2){
    return 1;
  }
	return 0;
}


int sortStartQueue()
	{
		if(StartQueue[Start]<=0)
		return -1;
		else if(StartQueue[Start+1]<=0)
		return StartQueue[Start]-1;
		else{
			int a=StartQueue[Start]-1;
			int b=StartQueue[Start+1]-1;
			if(Job[a][2]<Job[b][2])
			return a;
			StartQueue[Start]=b+1;
			StartQueue[End]=a+1;
			return StartQueue[Start]-1;
		}
	}

  void Insert(int a){  // Enqueue
  	End=End+1;
  	StartQueue[End]=a;
  }
  int Delete(){  // Dequeue
  	int a=StartQueue[Start];
  	Job[a-1][3]=CPU_TIME+1;
  	Start=Start+1;
  	boole=1;
  	onWards=a;
  	return a;
  }

void RR(){ // Round Robin
	int count=0,check=0;
	int cpuIdle=1;
	int i,id;
	int r=-1,f=0;
			for(i=2;i<n;i++){
					r=r+1;
					StartQueue1[r]=i+1;
				}
				if(cpuIdle==1)
					id=StartQueue1[f]-1;
	while(check==0){
		
	//	if(CPU_TIME<=4){
			//}
				printf("%d",id);
			
		if(count==2){
			int a=StartQueue1[f];
			f=f+1;
			r=r+1;
			StartQueue1[r]=a;
			id=StartQueue1[f]-1;
			if(id!=-1){
				cpuIdle=0;
			}
			else
				check=1;
			count=0;
			
		}
		CPU_TIME++;
		Job[id][2]=Job[id][2]-1;
		count++;
		if(Job[id][2]<=0){
			f=f+1;
			Job[id][3]=CPU_TIME+1;
			id=StartQueue1[f]-1;
			count=0;
			if(id==-1)
			check=1;
		}
	}
}



void scheduler(){
	int id,i,count=0;
	while(isExecuted()){
		if(CPU_TIME<2)
		for(i=0;i<n;i++)
			if(CPU_TIME==Arrival_Time[i])
				Insert(i+1);
		id=sortStartQueue();
		if(id!=-1){
			Job[id][2]=Job[id][2]-1;
			count++;
			if(Job[id][2]<=0){
				Delete();
			}
		}
		else{
			break;	
		}
		CPU_TIME++;
	}
	
	RR();
}

void ComputeWaitingTime(){
	int i,avg=0;
	printf("\n=======================================================================================================================\n\n");
	printf("Process		WaitingTime\n");
	printf("--------------------------------\n");
	for(i=0;i<n;i++){
		Job[i][5]=Job[i][4]-Burst_Time[i];
		avg+=Job[i][5];
		printf("  P%d			%d\n",i+1,Job[i][5]);
	}
	avg/=n;
	printf("\nThe Average Waiting Time is %d\n",avg);
}


void ComputeTurnAroundTime(){
	int i,avg=0;
	printf("\n=======================================================================================================================\n\n");
	printf("Process		TurnAroundTime\n");
	printf("------------****------****---------\n");
	for(i=0;i<n;i++){
		Job[i][4]=Job[i][3]-Job[i][1];
		avg+=Job[i][4];
		printf("  P%d			%d\n",i+1,Job[i][4]);
	}
	avg/=n;
	printf("\nThe Average TurnAround Time is %d\n",avg);
	
}

int main(){
	int i;
	for(i=0;i<n;i++){
		printf("Enter ArrivalTime of P%d :: ",i+1);
		scanf("%d",&Arrival_Time[i]);
		printf("Enter Burst_Time of P%d :: ",i+1);
		scanf("%d",&Burst_Time[i]);
		Job[i][1]=Arrival_Time[i];
		Job[i][2]=Burst_Time[i];
	}
	printf("\n\n");
	scheduler();
	printf("\n");
	ComputeTurnAroundTime();
	ComputeWaitingTime();
	return 0;
}

