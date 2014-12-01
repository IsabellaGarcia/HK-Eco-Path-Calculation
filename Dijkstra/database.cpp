#include"database.h"
#include"boost\tuple\tuple.hpp"
database::database(){
	driver = get_driver_instance(); 
	con = driver->connect("isabella", "isabella", "hellohi1217");
	 //choose a database
	con->setSchema("points");  
}

database::~database(){
	 delete con;
	// delete driver;
}

void database::connect(){
	/*try {   
        sql::Statement *stmt;  
		sql::ResultSet *res;    
        //�½�һ��ִ�����  
        stmt = con->createStatement();  

		//res = search_location_index(stmt,(long double)834148.783, (long double)816250.647);
		res = search_index_name(stmt,596);
        //���������  
        while (res->next())   
        {  
        //�����ID��user���е��ֶ���    
		cout << res->getString("RoadName") << endl;  
        }  
        //��ȡһ���ַ���Ŀ������CMD����ͣ�����鿴�����Ϣ��  
        getchar();  
        delete res;  
        delete stmt;  
      } catch (sql::SQLException &e) {  
        //���쳣������£�����쳣  
        cout << "# ERR: SQLException in " << __FILE__;  
        cout << "(" << __FUNCTION__ << ") on line "   
           << __LINE__ << endl;  
        cout << "# ERR: " << e.what();  
        cout << " (MySQL error code: " << e.getErrorCode();  
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;  
      }  
	while(1);
      //return EXIT_SUCCESS;  */
}

string database::search_index_name(int index){
	sql::Statement *stmt; 
	sql::ResultSet * res;
	stmt = con->createStatement();
	string index_s = to_string((long long) index);
	string c="select * from points where RoadId = \'";
	c = c + index_s;
	c = c + "\';";

	res = stmt->executeQuery(c.c_str()); 
	string result;
	while (res->next()){  
        //�����ID��user���е��ֶ���    
		result =  res->getString("RoadName");  
     } 

	delete res;  
    delete stmt;  
	return result;
}

int database::search_name_index(int name){
	sql::Statement *stmt; 
	sql::ResultSet * res;
	stmt = con->createStatement();
	string a = to_string((long long) name);
	string c ="select * from points where RoadName = \'";	
	c = c + a;
	c = c + "\'";
	res = stmt->executeQuery(c.c_str()); 
	string result;
	while (res->next()){  
        //�����ID��user���е��ֶ���    
		result =  res->getString("RoadId");  
     } 
	int index = stoi(result);
	delete res;  
    delete stmt; 
	return index;
}

int database::search_location_index(long double E, int f_E, long double N, int f_N){
		sql::Statement *stmt; 
		sql::ResultSet * res;
		stmt = con->createStatement();
		//Build up search sentence
		
		string point_1 = to_string(E-0.001);
		string point_2 = to_string(N);
		string point_3 = to_string(N+0.001);
		string c ="select * from points where north >= \'";	
		c = c + point_1;
		c = c + "\' and east >= \'";
		c = c + point_2;
		c = c + "\' and east <= \'";
		c = c + point_3;
		c = c +  "\' order by north asc";

		//cout << c << endl;
        res = stmt->executeQuery(c.c_str());  
		string result;
		int final_result = 0;
		if(res!=NULL){
			while (res->next()){  
			//�����ID��user���е��ֶ���    
			result =  res->getString("RoadId");  
			final_result = stoi(result);
			//cout << final_result << endl;
			break;
			} 
		}
		
		delete res;  
        delete stmt; 
		//while(1);
		return final_result;
}

double database::search_north_index(int index){
	sql::Statement *stmt; 
	sql::ResultSet * res;
	stmt = con->createStatement();
	string index_s = to_string((long double) index);
	string c="select * from points where RoadId = \'";
	c = c + index_s;
	c = c + "\';";

	res = stmt->executeQuery(c.c_str()); 
	string result;
	while (res->next()){  
        //�����ID��user���е��ֶ���    
		result =  res->getString("north");  
     } 
	//cout << result <<endl;
	delete res;  
    delete stmt;  
	return stod(result);
}

double database::search_east_index(int index){
	sql::Statement *stmt; 
	sql::ResultSet * res;
	stmt = con->createStatement();
	string index_s = to_string((long double) index);
	string c="select * from points where RoadId = \'";
	c = c + index_s;
	c = c + "\';";

	res = stmt->executeQuery(c.c_str()); 
	string result;
	while (res->next()){  
        //�����ID��user���е��ֶ���    
		result =  res->getString("east");  
     } 

	delete res;  
    delete stmt;  
	return stod(result);
}

