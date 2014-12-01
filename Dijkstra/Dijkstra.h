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
	int no; //β�ӵ����
	int cost; //��Ȩֵ
	edgeNode *next; //����һ���ڽӱ�β�ڵ�ָ��
};
//�ڵ���Ϣ�ṹ��
struct vexNode
{
	string info; //�ڵ�����
	edgeNode *link; //���������ıߵ�β�ڵ�����ָ��
};
struct Queue
{
	int no; //�����нڵ����
	int cost; //�Դ�Ϊβ�ڵ�ıߵ�Ȩֵ
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

		//���ȶ���
		Queue priQue[MAX];
		//�ڵ�����
	//	vexNode adjlist[POINTS_NUM];
		//ָ��Դ�㵽�ڵ�i�����·������
		int lowcost[MAX];
		//ָ��Դ�㵽�ڵ�i·���У��ڵ�i��ǰ���ڵ����
		int parent[MAX];
		vector<tuple<double, double>> route;
		string capture_time;
};
#endif