#include"Dijkstra.h"
#include <tuple>
#include<vector>

//Initialize adjacency list structure
vexNode adjlist[POINTS_NUM];

void Dijkstra::createGraph(const int n,const int e)
{
	ifstream infile;
	//string line;
	infile.open("current_weight.txt");
	//getline(infile, line);
	database db;
	int i;
	for(i=1;i<=n;i++)
	{
		//cout <<db.search_index_name(i) << endl;
		adjlist[i].info = db.search_index_name(i);
		adjlist[i].link = NULL;
		lowcost[i] = Infinity;
		parent[i] = i;
	}
	//while(1);
	edgeNode *p1;
	int v1,v2;
	//cout << e << endl;
	for(i=1;i<=e+1;i++)
	{	
		if(i<=e){
			string line;
			getline(infile, line);
			istringstream iss;
			iss.str(line);

			iss>> v1 >> v2;
			//cout << v1 << "   " << v2 << endl;
			int v1_r = db.search_name_index(v1);
			int v2_r = db.search_name_index(v2);
			p1 = (edgeNode*)malloc(sizeof(edgeNode));
			p1->no = v2_r;
		   //weight 
			iss >> p1->cost;		
			//insert near the edge node
			p1->next = adjlist[v1_r].link;
			adjlist[v1_r].link = p1;
		}
		if(i==e+1){
			getline(infile,capture_time);
		}
	}

}

//当插入节点到优先队列时，保持队列优先性
void Dijkstra::keep_min_heap(Queue *priQue,int &num,const int k)
{
	int l = 2*k;
	int r = 2*k + 1;
	int smallest = k;
	if(l<=num&&priQue[l].cost<priQue[k].cost)
		smallest = l;
	if(r<=num&&priQue[r].cost<priQue[smallest].cost)
		smallest = r;
	if(smallest != k)
	{
		Queue temp = priQue[smallest];
		priQue[smallest] = priQue[k];
		priQue[k] = temp;
		keep_min_heap(priQue,num,smallest);
	}
}
//插入节点到优先队列时并且保持队列优先性
void Dijkstra::heap_insert(Queue *priQue,int &num,int no,int cost)
{
	//members in the Queue
	num +=1;
	priQue[num].no = no;
	priQue[num].cost = cost;
	int i = num;
	while(i>1&&priQue[i/2].cost>priQue[i].cost)
	{
		Queue temp = priQue[i];
		priQue[i] = priQue[i/2];
		priQue[i/2] = temp;
		i = i/2;
	}
}
//取出优先队列的队头元素
Queue Dijkstra::heap_extract_min(Queue *priQue,int &num)
{
	if(num<1)
		return priQue[0];
	Queue min = priQue[1];
	priQue[1] = priQue[num];
	num -=1;
	keep_min_heap(priQue,num,1);
	return min;
}
//打印指定源点带序号为i的点的最短路径
void Dijkstra::print_it(int *parent,vexNode *adjlist,int v)
{
	if(parent[v] == v){
		//cout<<"("<<v<<":"<<adjlist[v].info<<") ";
		database db;
	    tuple<double, double> temp = make_tuple(db.search_north_index(v), db.search_east_index(v));
		route.push_back(temp);
		
	}
	else
	{
		print_it(parent,adjlist,parent[v]);
		//cout<<"("<<v<<":"<<adjlist[v].info<<") ";
		database db;
	    tuple<double, double> temp = make_tuple(db.search_north_index(v), db.search_east_index(v));
		route.push_back(temp);
	}
}

int Dijkstra::dijkstra(int start_index, int end_index)
{
	for(int i = 0; i< MAX ;i++){
	 priQue[i].no = 0;
	 priQue[i].cost = 0;
	 lowcost[i] = 0;
	 parent[i] = 0;
	}	
		int n,e;
	//	cout<<"请输入节点数：";
		n = POINTS_NUM;		
	//	cout<<"请输入边数：";
		e = EDGE_NUM;
		//队列中的元素，初始为0
		int num = 0;
		int i;
		//创建邻接表
		createGraph(n,e);
	
		//cout << "Begin index of point：";
		int v0;
		v0 = start_index;
		int v = v0;
		//cout << "End index of point：";
		int v_end;
		v_end = end_index;

		lowcost[v0] = 0;
		//cout << endl;
		Queue queue;

		for(i=1;i<n;i++)
		{
			//cout << "V0 = " << v0 << endl;
			edgeNode *p = adjlist[v0].link;
			//cout << p->no << endl;
			while(p != NULL)
			{
				if(lowcost[v0] + p->cost<lowcost[p->no])
				{
					lowcost[p->no] = lowcost[v0] + p->cost;
					parent[p->no] = v0;
					heap_insert(priQue,num,p->no,lowcost[p->no]);
				}
				p = p->next;
			}
			//cout << endl;
			queue = heap_extract_min(priQue,num);
			v0 = queue.no;
		}
		
			//cout<<"From point "<<adjlist[v].info<<" to "<<adjlist[v_end].info<<", the shortest path is："<<endl;
			print_it(parent,adjlist,v_end);
		//	cout<<"The distance is ："<<lowcost[v_end]<<endl;
	//system("pause");
	
		return 0;
}

vector<tuple<double, double>> Dijkstra::get_waypts(){
	return route;
}

string Dijkstra::get_capturetime(){
	return capture_time;
}