#ifndef DIJKSTRAH_H
#define DIJKSTRA_H

#include<iostream>
#include<vector>
#include <tuple>
#include<fstream>
#include<sstream>
#include "rapidxml.hpp"
#include<set>
#include<string>
using namespace std;

#include"database.h"

#define MAX 700
#define Infinity 65535
#define POINTS_NUM 606
#define EDGE_NUM 617
//edge nodes
struct edgeNode
{
	int no; //尾接点序号
	int cost; //边权值
	edgeNode *next; //其下一条邻接边尾节点指针
};
//节点信息结构体
struct vexNode
{
	string info; //节点名称
	edgeNode *link; //与其相连的边的尾节点链表指针
};
struct Queue
{
	int no; //队列中节点序号
	int cost; //以此为尾节点的边的权值
};

class Dijkstra{
	public:
		int dijkstra(int, int);
		vector<tuple<double, double>> get_waypts();
		string get_capturetime();
	private:
		void createGraph(const int n,const int e);
		void keep_min_heap(Queue *priQue,int &num,const int k);
		void heap_insert(Queue *priQue,int &num,int no,int cost);
		Queue heap_extract_min(Queue *priQue,int &num);
		void print_it(int *parent,vexNode *adjlist,int v);

		//优先队列
		Queue priQue[MAX];
		//节点数组
	//	vexNode adjlist[POINTS_NUM];
		//指定源点到节点i的最短路径花费
		int lowcost[MAX];
		//指定源点到节点i路径中，节点i的前驱节点序号
		int parent[MAX];
		vector<tuple<double, double>> route;
		string capture_time;
};
#endif