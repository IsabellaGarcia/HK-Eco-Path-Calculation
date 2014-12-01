
#include"parseXML.h"

#include <iostream>
#include <UrlMon.h>
#pragma comment(lib,"urlmon.lib")
using namespace std;

int  parseXML::parse(){
	download();
	file<> fdoc("speedmap.xml");
	xml_document<> doc;
	doc.parse<0>(fdoc.data());

	ofstream outfile;
	outfile.open("current_weight.txt");

	//root node
	xml_node<> *root = doc.first_node();
	//std::cout << root->name() << std::endl;

	xml_node<>* node1 = root->first_node();
	xml_node<>* node2;
	string start;
	string end;
	string saturation;
	int cost;
	int length;
	int position;
	double speed;
	string time;
	bool capture = false;
	//parsing in each speedmap
	do{
		node2 = node1->first_node();  
		std::string line = node2->value();
		/* for each edge;
		* Start point      --- string start 
		* End point        --- string end
		* Road saturation  --- cost
		* Speed            --- speed
		*/
		/* ---------------- LINK_ID -------------------- */
		stringstream iss(line);
		position = line.find('-');
		
		start = line.substr(0,position);
		outfile << start << " ";
		position ++;
		end = line.substr(position,line.length()-position);
		outfile << end << " ";
		/* ------------- RIGION ------------------------- */
		node2 = node2->next_sibling();
		/* ------------- ROAD TYPE ---------------------- */
		node2 = node2->next_sibling();
		/* ------------- ROAD SATURATION LEVEL ---------- */
		node2 = node2->next_sibling();
		saturation = node2->value();
		cost = shift(saturation);
		outfile << cost << " ";
		/* ------------- TRAFFIC_SPEED ------------------ */
		node2 = node2->next_sibling();
		speed = stod(node2->value());
		outfile << speed << endl;
		/* ------------- TIME ------------------ */
		if(!capture){
			node2 = node2->next_sibling();
			time = node2->value();
		}
		
	}while(node1 = node1->next_sibling());
	outfile << time << endl;
	outfile.close();
	return 0;
}
int  parseXML::shift(string saturation){
	if(saturation == "TRAFFIC BAD")
		return 5;
	else if(saturation == "TRAFFIC AVERAGE")
		return 3;
	else if(saturation == "TRAFFIC GOOD")
		return 1;
}

void  parseXML::download(){
	HRESULT hr = URLDownloadToFile(0,"http://data.one.gov.hk/others/td/speedmap.xml",
		"speedmap.xml",0,NULL);
    
	if (hr == S_OK){
	//char *cmd = "mspaint mypic.jpg";
	//WinExec(cmd,SW_SHOWNORMAL);
		//cout <<"OK" << endl;
	}
}