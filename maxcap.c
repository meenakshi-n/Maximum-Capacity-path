#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>

#define UNSEEN 0
#define INTREE 1
#define FRINGE 2

struct Adjacent
{	int v;
	int w;
	int weight;
	struct Adjacent*next;
}*new;
		
struct Vertex
{	int v;
	struct Adjacent* adjacent;
}vertex[5000];

struct Edges
{	int v;
	int w;
	int weight;
}*edges;

struct Spanning_tree
{	int v;
	int w;
	int weight;
	struct Spanning_tree*next;
}*tree=NULL;

//no.of edges
int e=0;

//dad array
int dad[5000];
int rank[5000];
int d[5000];
int H[5000];
int Q[5000];


void swap(int *a, int *b)
{	*a=(*a)+(*b);
	*b=(*a)-(*b);
	*a=(*a)-(*b);
}

int max_heap()
{	return H[0];
}

int parent(int i)
{	return floor((i-1)/2);
}

void insert_heap(int key,int heap_size)
{	int i;
	
	H[heap_size-1]=key;
	i=heap_size-1;
	while(i>0 && d[H[i]]>d[H[parent(i)]])
	{	//Do we need to pass the address of an idividual element of the array?
		swap(&H[i],&H[parent(i)]);
		i=i/2;
	}
	
	
}

void max_heapify(int i,int heap_size)
{	int l=2*(i+1)-1,r=2*(i+1),largest;
	if (l<heap_size && (d[H[l]])>(d[H[i]]))
		largest=l;
	else largest=i;
	
	if(r<heap_size && (d[H[r]])>(d[H[largest]]))
		largest=r;
	if (largest!=i)
	{	swap(&H[i],&H[largest]);				
		max_heapify(largest,heap_size);
	}
	
}

void delete_heap(int key,int heap_size)
{	int i;
	for(i=0;i<heap_size;i++)
		if(H[i]==key)
		{
			swap(&H[i],&H[heap_size-1]);
			max_heapify(i,heap_size-1);
			break;
		}
	

}



void dijkstra(int s, int destination)
{	int i,status[5000],heap_size=0,v;
	
	for(i=0;i<5000;i++)
	{	status[i]=UNSEEN;
		dad[i]=-1;
	}
	status[s]=INTREE;
	d[s]=0;
	new=vertex[s].adjacent;
	while(new!=NULL)
	{	status[new->w]=FRINGE;
		d[new->w]=new->weight;
		dad[new->w]=s;
		heap_size++;
		insert_heap(new->w,heap_size);
		new=new->next;
		
	}
	while(heap_size>0)
	{	v=max_heap();
		if(v==destination)
		{	break;
			
		}
		delete_heap(v,heap_size);
		heap_size--;
		status[v]=INTREE;
		new=vertex[v].adjacent;
		while(new!=NULL)
		{	if(status[new->w]==UNSEEN)
			{	status[new->w]=FRINGE;
				
				if((new->weight)>d[v])
					d[new->w]=d[v];
				else
					d[new->w]=new->weight;
				heap_size++;
				insert_heap(new->w,heap_size);
				dad[new->w]=v;
				
			}
			else if(status[new->w]==FRINGE)
			{	if(d[new->w]<d[v]&&d[new->w]<(new->weight))
				{	delete_heap(new->w,heap_size);
					heap_size--;
					if((new->weight)<d[v])
						d[new->w]=new->weight;
					else
						d[new->w]=d[v];
					heap_size++;
					insert_heap(new->w,heap_size);
					dad[new->w]=v;
					
	
				}
			}
			new=new->next;
		}
		
	}
	
	printf("\nMAXIMUM CAPACITY PATH FROM %d TO %d IS:\n************************************************\n",s,destination);
	printf("%d,\t", destination);
	while(dad[destination]!=-1)
	{	destination=dad[destination];
		printf("%d,\t",destination);
		
	}
	
}

int max_queue(int size)
{	int i,max;
	max=d[Q[0]];
	for(i=1;i<size;i++)
	{	if(d[Q[i]]>max)
			max=Q[i];
	}
	return max;
}

void delete_queue(int key,int size)
{	int i;
	for(i=0;i<size;i++)
		if(Q[i]==key)
			break;
	for(i;i<size-1;i++)
		Q[i]=Q[i+1];
}				
		
void dijkstra_without_heap(int s, int destination)
{	int i,status[5000],queue_size=0,v;
	for(i=0;i<5000;i++)
	{	status[i]=UNSEEN;
		dad[i]=-1;
	}
	status[s]=INTREE;
	d[s]=0;
	new=vertex[s].adjacent;
	while(new!=NULL)
	{	status[new->w]=FRINGE;
		d[new->w]=new->weight;
		dad[new->w]=s;
		queue_size++;
		Q[queue_size-1]=new->w;
		new=new->next;
		
	}
	while(queue_size>0)
	{	v=max_queue(queue_size);
		if(v==destination)
		{	
			break;
			
		}
		
		delete_queue(v,queue_size);
		queue_size--;
		status[v]=INTREE;
		new=vertex[v].adjacent;
		while(new!=NULL)
		{	if(status[new->w]==UNSEEN)
			{	status[new->w]=FRINGE;
				
				if((new->weight)>d[v])
					d[new->w]=d[v];
				else
					d[new->w]=new->weight;
				queue_size++;
				Q[queue_size-1]=new->w;
				dad[new->w]=v;
				
			}
			else if(status[new->w]==FRINGE)
			{	if(d[new->w]<d[v]&&d[new->w]<(new->weight))
				{	
					if((new->weight)<d[v])
						d[new->w]=new->weight;
					else
						d[new->w]=d[v];
					dad[new->w]=v;
					
	
				}
			}
			new=new->next;
		}
		
	}
	
	
}
	
	
	
	

void min_heapify(int i,int size)
{	int l=2*(i+1)-1,r=2*(i+1),smallest;
	if (l<size && (edges[l].weight)<(edges[i].weight))
		smallest=l;
	else smallest=i;
	
	if(r<size && (edges[r].weight)<(edges[smallest].weight))
		smallest=r;
	if (smallest!=i)
	{	swap(&edges[i].weight,&edges[smallest].weight);
		swap(&edges[i].v,&edges[smallest].v);
		swap(&edges[i].w,&edges[smallest].w);				
		min_heapify(smallest,size);
	}
	
}

Build_min_heap(int size)
{	
	int i;
	
	//print the array to check if it's passed right
                                                      
	i=floor(size/2);
	
	for (i=i-1;i>=0;i--)
	{	
		min_heapify(i,size);
	}
}

HeapSort(int size)
{	int i;
	Build_min_heap(size);
	for(i=size-1;i>=1;i--)
	{	
		swap(&edges[0].weight,&edges[i].weight);
		swap(&edges[0].v,&edges[i].v);
		swap(&edges[0].w,&edges[i].w);
		size=size-1;
		min_heapify(0,size);
	}
}	

int find(int k)
{	int i=k;
	while(dad[i]!=-1)
		i=dad[i];
	return i;
}

void Union(int r1,int r2)
{	if(rank[r1]>rank[r2])
		dad[r2]=r1;
	else if(rank[r1]<rank[r2])
		dad[r1]=r2;
	else if(rank[r1]==rank[r2])
	{	dad[r2]=r1;
		rank[r1]++;
		
	}
	
}

double Kruskal()
{	int size=e,i,r1,r2;
	clock_t end;
	struct Spanning_tree *new;
	
	HeapSort(size);
	
	for(i=0;i<size;i++)
	{
		r1=find(edges[i].v);
		r2=find(edges[i].w);
		if(r1!=r2)
		{	//how to represent T
			new=(struct Spanning_tree*)malloc(sizeof(struct Spanning_tree));
			new->weight=edges[i].weight;
			new->v=edges[i].v;
			new->w=edges[i].w;
			new->next=tree;
			tree=new;
			
			
			Union(r1,r2);
		}
	
	}
	end=clock();
	//displaying MST
	/*new=tree;
	printf("\nMST:\n");
	while(new!=NULL)
	{	printf("edge %d-%d of weight%d\n",new->v,new->w,new->weight);
		new=new->next;
	}*/
	return end;	
	
}

void graph_generate_dense()
{	int r,i,j,number[5000],k,t,adj,flag,flag1,num;		
	
	for(i=0;i<5000;i++)
	{	number[i]=i;
		vertex[i].adjacent=NULL;
		vertex[i].v=i;
	}
	adj=1000;

	//initialise structure that holds the edges
	edges=calloc(5000*adj,sizeof(struct Edges));

	for(i=0;i<5000;i++)
	{	
		j=0;

		//initialise dad and rank arrays for kruskals
		dad[i]=-1;
		rank[i]=0;
		flag=0;
		

		//check if edges have already been assigned
		if(vertex[i].adjacent!=NULL)
		{	flag=1;
			new=vertex[i].adjacent;
			while(new!=NULL)
			{	j++;
				new=new->next;
			}
		}
		
		for(k=5000;j<adj;j++,k--)
		{	
			flag1=0;
			r=rand()%k;
			if(number[r]==i)
			{	k++;
				j--;
				continue;
				
			}
				//check to see if the edge has already been added
			if(flag==1)
			{	new=vertex[i].adjacent;
				while(new!=NULL)
				{	if(new->w==number[r])
					{	j--;k++;
						flag1=1;
						break;
					}

					new=new->next;
				}
				
			}
			if(flag1==0)
			{	
					new=(struct Adjacent*)malloc(sizeof(struct Adjacent));
					new->w=number[r];
					new->v=vertex[i].v;
					new->weight=rand()%15+1;
					//new->weight=e;
					new->next=vertex[i].adjacent;
					vertex[i].adjacent=new;

					//edges
					edges[e].v=i;
					edges[e].w=new->w;
					edges[e].weight=new->weight;
			
				
					//to add edge v to the adjacency list of w
					
					new=(struct Adjacent*)malloc(sizeof(struct Adjacent));
					new->v=number[r];
					new->w=vertex[i].v;
					new->weight=e;
					new->next=vertex[number[r]].adjacent;
					vertex[number[r]].adjacent=new;
					
					//swap the randomly generated index with the last index of the array containing 5000 nos.

					t=number[r];
					number[r]=number[k-1];
					number[k-1]=t;	
					e++;
				
			}
		
		}
	}
	
	
}
			
void graph_generate(char* type)
{	int r,i,j,number[5000],k,t,adj,flag,flag1,num;		
	
	for(i=0;i<5000;i++)
	{	number[i]=i;
		vertex[i].adjacent=NULL;
		vertex[i].v=i;
	}
	if (strcmp(type, "sparse")==0)
		adj=3;
	else if(strcmp(type,"dense")==0)
		adj=1000;

	//initialise structure that holds the edges
	edges=calloc(5000*adj,sizeof(struct Edges));

	for(i=0;i<5000;i++)
	{	
		j=0;

		//initialise dad and rank arrays for kruskals
		dad[i]=-1;
		rank[i]=0;
		flag=0;
		

		//check if edges have already been assigned
		if(vertex[i].adjacent!=NULL)
		{	
			flag=1;
			new=vertex[i].adjacent;
			while(new!=NULL)
			{	j++;
				new=new->next;
			}
		}
		
		for(k=5000;j<adj;j++,k--)
		{	
			flag1=0;
			r=rand()%k;
			
			if(number[r]==i)
			{	k++;
				j--;
				continue;
				
			}
				//check to see if the edge has already been added
			if(flag==1)
			{	new=vertex[i].adjacent;
				while(new!=NULL)
				{	if(new->w==number[r])
					{	
						j--;k++;
						flag1=1;
						break;
					}

					new=new->next;
				}
				
			}
			if(flag1==0)
			{	
				//before adding edge, check to see if that vertex already has six vertices
				new=vertex[number[r]].adjacent;
				num=0;
				while(new!=NULL)
				{	
					num++;
					new=new->next;
				}
		
				if(num>=adj)
				{	j--;k++;
				}
				else
				{

					new=(struct Adjacent*)malloc(sizeof(struct Adjacent));
					new->w=number[r];
					new->v=vertex[i].v;
					new->weight=rand()%15+1;
					//new->weight=e;
					new->next=vertex[i].adjacent;
					vertex[i].adjacent=new;

					//edges
					edges[e].v=i;
					edges[e].w=new->w;
					edges[e].weight=new->weight;
			
				
					//to add edge v to the adjacency list of w
					new=(struct Adjacent*)malloc(sizeof(struct Adjacent));
					new->v=number[r];
					new->w=vertex[i].v;
					new->weight=e;
					new->next=vertex[number[r]].adjacent;
					vertex[number[r]].adjacent=new;
					
				
					//swap the randomly generated index with the last index of the array containing 5000 nos.

					t=number[r];
					number[r]=number[k-1];
					number[k-1]=t;	
					e++;
				}
			}
		
		}
	}
	
		
}
					
int main(int argc, char*argv[])
{	int i;
	double time_spent,t2,t1;
	clock_t begin , end;
	int v=2208,w=2013,a=11,b=2674,c=1092,d=2693,x=102,y=267;

	printf("SPARSE graph\n\n");
	graph_generate("sparse");

	begin=clock();
	dijkstra(v, w);
	end=clock();
	t2=(double)(end-begin)/CLOCKS_PER_SEC;
	printf("\n\ntime spent running dijkstra's is %f",t2);

	begin=clock();
	end=Kruskal();
	
	t1=(double)(end-begin)/CLOCKS_PER_SEC;
	printf("\ntime spent running kruskal's is %f",t1);
	
	
	begin=clock();
	dijkstra_without_heap(v, w);
	end=clock();
	time_spent=(double)(end-begin)/CLOCKS_PER_SEC;
	
	printf("\ntime spent running dijkstra's without heap is %f\n",time_spent);

	begin=clock();
	dijkstra(x, y);
	end=clock();
	t2=(double)(end-begin)/CLOCKS_PER_SEC;
	printf("\n\ntime spent running dijkstra's is %f",t2);

	begin=clock();
	end=Kruskal();
	
	t1=(double)(end-begin)/CLOCKS_PER_SEC;
	printf("\ntime spent running kruskal's is %f",t1);
	
	
	begin=clock();
	dijkstra_without_heap(x, y);
	end=clock();
	time_spent=(double)(end-begin)/CLOCKS_PER_SEC;
	
	printf("\ntime spent running dijkstra's without heap is %f\n",time_spent);

	begin=clock();
	dijkstra(a, b);
	end=clock();
	t2=(double)(end-begin)/CLOCKS_PER_SEC;
	printf("\n\ntime spent running dijkstra's is %f",t2);

	begin=clock();
	end=Kruskal();
	
	t1=(double)(end-begin)/CLOCKS_PER_SEC;
	printf("\ntime spent running kruskal's is %f",t1);
	
	
	begin=clock();
	dijkstra_without_heap(a,b);
	end=clock();
	time_spent=(double)(end-begin)/CLOCKS_PER_SEC;
	
	printf("\ntime spent running dijkstra's without heap is %f\n",time_spent);

	begin=clock();
	dijkstra(c, d);
	end=clock();
	t2=(double)(end-begin)/CLOCKS_PER_SEC;
	printf("\n\ntime spent running dijkstra's is %f",t2);

	begin=clock();
	end=Kruskal();
	
	t1=(double)(end-begin)/CLOCKS_PER_SEC;
	printf("\ntime spent running kruskal's is %f",t1);
	
	
	begin=clock();
	dijkstra_without_heap(c, d);
	end=clock();
	time_spent=(double)(end-begin)/CLOCKS_PER_SEC;
	
	printf("\ntime spent running dijkstra's without heap is %f\n",time_spent);

	printf("\n\nDENSE graph \n\n");
	graph_generate_dense();
	
	begin=clock();
	dijkstra(v, w);
	end=clock();
	t2=(double)(end-begin)/CLOCKS_PER_SEC;
	printf("\ntime spent running dijkstra's is %f",t2);

	begin=clock();
	end=Kruskal();
	
	t1=(double)(end-begin)/CLOCKS_PER_SEC;
	begin=clock();
	printf("\ntime spent running kruskal's is %f\n",t1);

	begin=clock();
	dijkstra(x, y);
	end=clock();
	t2=(double)(end-begin)/CLOCKS_PER_SEC;
	printf("\ntime spent running dijkstra's is %f",t2);

	begin=clock();
	end=Kruskal();
	
	t1=(double)(end-begin)/CLOCKS_PER_SEC;
	begin=clock();
	printf("\ntime spent running kruskal's is %f\n",t1);

	begin=clock();
	dijkstra(a, b);
	end=clock();
	t2=(double)(end-begin)/CLOCKS_PER_SEC;
	printf("\ntime spent running dijkstra's is %f",t2);

	begin=clock();
	end=Kruskal();
	
	t1=(double)(end-begin)/CLOCKS_PER_SEC;
	begin=clock();
	printf("\ntime spent running kruskal's is %f\n",t1);
	
	begin=clock();
	dijkstra(c, d);
	end=clock();
	t2=(double)(end-begin)/CLOCKS_PER_SEC;
	printf("\ntime spent running dijkstra's is %f",t2);

	begin=clock();
	end=Kruskal();
	
	t1=(double)(end-begin)/CLOCKS_PER_SEC;
	begin=clock();
	printf("\ntime spent running kruskal's is %f\n",t1);

	
	
	
	
	exit(0);	
	return 0;

	

}		
        	

