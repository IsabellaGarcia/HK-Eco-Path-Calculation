#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <string>
#include <mysql_connection.h>  
#include <cppconn/driver.h>  
#include <cppconn/exception.h>  
#include <cppconn/resultset.h>  
#include <cppconn/statement.h>  
using namespace std;  

class Dijkstra;
class database{
	public:
		database();
		~database();
		void connect(); 
		string search_index_name(int);
		int search_name_index(int);
		int search_location_index(long double, int, long double, int);
		double database::search_north_index(int);
		double database::search_east_index(int);
	private:
		sql::Driver *driver; 
		sql::Connection *con; 
};
#endif