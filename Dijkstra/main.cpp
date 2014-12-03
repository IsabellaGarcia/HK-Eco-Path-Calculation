#include"Dijkstra.h"
#include"parseXML.h"
#include"database.h"
#include<tuple>
#include<stdio.h>
#include<stdlib.h>
#include<iomanip>
#include<vector>
#include<iostream>
#include<string>

void draw_canvas(vector<tuple<double, double>>,string);
void draw_layout(vector<tuple<double, double>>,string);
void draw_structure();

vector<tuple<double, double>> way;

int main(){
	/*database db;
	ifstream infile;
	ofstream outfile;
	infile.open("roadlink.txt");
	outfile.open("location.txt");


	for(int i=1;i<618;i++){
		string line;
		getline(infile,line);
		int a,b;
		istringstream iss;
		iss.str(line);
		iss >> a >> b;
		cout <<line;
		outfile <<  setprecision(8) << db.search_north_index(db.search_name_index(a)) <<endl;
		outfile <<  setprecision(8) << db.search_east_index(db.search_name_index(a)) << endl;
		outfile <<  setprecision(8) << db.search_north_index(db.search_name_index(b)) << endl;
		outfile <<  setprecision(8) << db.search_east_index(db.search_name_index(b)) << endl;
	}
	infile.close();
	outfile.close();
	
	while(1);*/

	//while(1);
	parseXML px;
	px.parse();
	char *data;
	long double m,n,o,p;
	printf("%s%c%c\n","Content-Type:text/html;charset=iso-8859-1",13,10);
	data = getenv("QUERY_STRING");

	if(data == NULL)
	 printf("<P>Error! Error in passing data from form to script.");
	else if(sscanf(data,"m=%lf&n=%lf&o=%lf&p=%lf",&m,&n,&o,&p)!=4)
	 printf("<P>Error! Invalid data. Data must be numeric.");
	else{
		database db;
		int start, end;
		start = db.search_location_index(m,0,n,0);
		end = db.search_location_index(o,0,p,0);
		Dijkstra d;
		if(start*end != 0){		
			d.dijkstra(start,end);
			way = d.get_waypts();
			if(way.size() == 1){
				tuple<double, double> temp = way.at(0);
				way.push_back(temp);
				database db1;
				get<0>(way.at(0)) = db1.search_north_index(start);
				get<1>(way.at(0)) = db1.search_east_index(start);
			}
				draw_layout(way,d.get_capturetime());
		}
		else{
			tuple<double, double> temp = make_tuple(m,n);			
			way.insert(way.begin(),temp);
			tuple<double, double> temp_1 = make_tuple(o,p);
			way.push_back(temp_1);
			draw_layout(way,d.get_capturetime());
		}
	}
	
	return 0;
}

void draw_canvas(vector<tuple<double, double>> waypts,string capture_time){
	printf("<html> ");
	printf("<head> ");
	printf("<title>Hong Kong Maps</title> ");
	printf("<meta name= \"%s\" content=\"%s\"> ","viewport","initial-scale=1.0, user-scalable=no");
	printf("<meta charset=\"%s\"> ","utf-8");
	printf("<style> ");
	printf("html, body, #map-canvas { height: 800px; width: 900px;  margin: 0px; padding: 0px; float: left }");
	printf("div #input form{ height: 800px; width: 50px; margin: 0px; padding: 0px; float:right  }");
	printf("</style> ");
	printf("<script src=\"%s\">","https://maps.googleapis.com/maps/api/js?v=3.exp&language=en");
	printf("</script> ");
	printf("<script> ");

	



	cout << "var start_lat = " << get<0>(waypts.at(0)) <<";";
	cout << "var start_lng = " << get<1>(waypts.at(0)) <<";";
	cout << "var end_lat = " << get<0>(waypts.at(waypts.size()-1)) <<";";
	cout << "var end_lng = " << get<1>(waypts.at(waypts.size()-1)) <<";";

	printf("var map; ");
	printf("var markers = []; ");
	printf("var waypts = []; ");
	printf("var directionsDisplay; ");
	printf("var directionsService = new google.maps.DirectionsService();");
	printf("var geocoder; ");
		printf("var check1 = 0;");
	printf("var check2 = 0;");

	//----------------  Initialize function  -----------------------------
	printf("function initialize() { ");
	printf("directionsDisplay = new google.maps.DirectionsRenderer();");
	printf("geocoder = new google.maps.Geocoder();");
	printf("var mapOptions = {  ");
	printf("zoom: 13, center: new google.maps.LatLng(22.335269, 114.265802)};");
	printf("map = new google.maps.Map(document.getElementById('map-canvas'), mapOptions);");
	printf("directionsDisplay.setMap(map); ");	
	printf("calcRoute();");
	//----------------  end of initialize function  ----------------------
	printf("} ");

	//----------------  Initialize calcRoute  -----------------------------
	printf("function calcRoute() {");
	//set start and end point
	printf(" var start = new google.maps.LatLng(start_lat, start_lng);");
	printf("var end = new google.maps.LatLng(end_lat, end_lng);");
  
  // set way points along the way
	printf("var waypts = [];");
  //for (var i = 0; i < checkboxArray.length; i++){

	for( int i = 1; i < way.size()-1; i++){
		cout << "var way1 = new google.maps.LatLng(" << get<0>(waypts.at(i))
			<<"," << get<1>(waypts.at(i))<<");";
		printf("waypts.push({");
		printf("location: way1,");
		printf("stopover:true});");
	}
			  
	printf(" var request = {");
	printf("origin:start,");
	printf("destination:end,");
	printf("waypoints: waypts,");
	printf("optimizeWaypoints: true,");
	printf("travelMode: google.maps.TravelMode.DRIVING");
	printf("};");
	printf("directionsService.route(request, function(response, status) {");
	printf(" if (status == google.maps.DirectionsStatus.OK) {");
	printf("directionsDisplay.setDirections(response);");
	printf(" }");
	printf(" });");
	printf("}");
	//----------------  end of initialize calcRoute  ----------------------

		printf("function codeAddress() {");
		printf("var address = document.getElementById('address').value;");
		printf("geocoder.geocode( { 'address': address}, function(results, status) {");
		printf("if (status == google.maps.GeocoderStatus.OK) {");
       printf(" map.setCenter(results[0].geometry.location);");
			printf("var marker = new google.maps.Marker({");
			printf("map: map,");
			printf("position: results[0].geometry.location");
		printf("});");
		
		printf("document.getElementById(\"m\").value = results[0].geometry.location.lat();");
		printf("document.getElementById(\"n\").value = results[0].geometry.location.lng();");
		printf("check1 = 1;");
		printf("doublecheck();");
		printf("} else {");
			printf("alert('Geocode was not successful for the following reason: ' + status);");
			printf("}");
		printf("});");
	printf("}");
	
	printf("function codeAddress1() {");
		printf("var address1 = document.getElementById('address1').value;");
		printf("geocoder.geocode( { 'address': address1}, function(results, status) {");
		printf("if (status == google.maps.GeocoderStatus.OK) {");
        printf("map.setCenter(results[0].geometry.location);");
			printf("var marker = new google.maps.Marker({");
			printf("map: map,");
			printf("position: results[0].geometry.location");
		printf("});");
		
		printf("document.getElementById(\"o\").value = results[0].geometry.location.lat();");
		printf("document.getElementById(\"p\").value = results[0].geometry.location.lng();");
		printf("check2 = 1;");
		printf("doublecheck();");
		printf("} else {");
			printf("alert('Geocode was not successful for the following reason: ' + status);");
			printf("}");
		printf("});");
	printf("}");

	printf("function doublecheck(){");
		printf("if(check1*check2 != 0){");
		printf("alert(\"Now you can click on the Submit button to get the result\");");
			printf("document.getElementById(\"mySubmit\").disabled = false;");
			printf("}");
	printf("}");

	printf("function getStart(val){");
		printf("codeAddress();");
	printf("}");
	
	printf("function getEnd(val){");
		printf("codeAddress1();");
	printf("}");

	printf("google.maps.event.addDomListener(window, 'load', initialize);  ");

	//end of body
	printf("</script> ");
	printf("</head> ");


	printf("<body> <table> <tr> <td>  ");
	printf("<div id=\"map-canvas\"></div> ");
	printf("<td/><td> ");

	cout <<"<p>Traffic data is collected at </p>" << capture_time << endl;
		printf("<div><label> Start point name: <input name= \"address\" id = \"address\" type=\"textbox\" ");
		printf("onchange = \"getStart(this.value)\"/></label></div>");
		printf("<div><label> End point name: <input name= \"address1\" id = \"address1\" type=\"textbox\" ");
		printf("onchange = \"getEnd(this.value)\"/></label></div>	");









	printf("<div id=\"input form\"> ");
	printf("<form action=\"cgi-bin/Dijkstra/Dijkstra.exe\" > ");
	printf("<p>The latitude and longitude of points: </p> ");
		printf("<div><label> Start_lat: <input name= \"m\" maxlength=\"18\" /></label></div>");
		printf("<div><label> Start_lng: <input name= \"n\" maxlength=\"18\" /></label></div>");
		printf("<div><label> End_lat:<input  name= \"o\" maxlength=\"18\" /><label></div>");
		printf("<div><label> End_lng:<input  name= \"p\" maxlength=\"18\" /><label></div>");
		printf("<div><input type=\"submit\" id = \"mySubmit\" value=\"Submit\" disabled = true /></div>");
	printf("</form></div></td></tr></table></body></html>");
}

void draw_layout(vector<tuple<double, double>> waypts,string capture_time){
	ifstream infile;
	infile.open("layout.txt");
	
	while(!infile.eof()){
		string line;
		getline(infile,line);
		cout << line;
	}
	infile.close();

	cout << "var start_lat = " << get<0>(waypts.at(0)) <<";";
	cout << "var start_lng = " << get<1>(waypts.at(0)) <<";";
	cout << "var end_lat = " << get<0>(waypts.at(waypts.size()-1)) <<";";
	cout << "var end_lng = " << get<1>(waypts.at(waypts.size()-1)) <<";";


	printf("var map; ");
	printf("var markers = []; ");
	printf("var waypts = []; ");
	printf("var directionsDisplay; ");
	printf("var directionsService = new google.maps.DirectionsService();");
	printf("var geocoder; ");
	printf("var check1 = 0;");
	printf("var check2 = 0;");

	//----------------  Initialize function  -----------------------------
	printf("function initialize() { ");
	printf("directionsDisplay = new google.maps.DirectionsRenderer();");
	printf("geocoder = new google.maps.Geocoder();");
	printf("var mapOptions = {  ");
	printf("zoom: 13, center: new google.maps.LatLng(22.335269, 114.265802)};");
	printf("map = new google.maps.Map(document.getElementById('map-canvas'), mapOptions);");
	printf("directionsDisplay.setMap(map); ");
	printf("directionsDisplay.setPanel(document.getElementById('directions-panel'));");
	printf("calcRoute();");
	//----------------  end of initialize function  ----------------------
	printf("} ");

  
		//----------------  Initialize calcRoute  -----------------------------
	printf("function calcRoute() {");
	//set start and end point
	printf(" var start = new google.maps.LatLng(start_lat, start_lng);");
	printf("var end = new google.maps.LatLng(end_lat, end_lng);");
  
  // set way points along the way
	printf("var waypts = [];");
  //for (var i = 0; i < checkboxArray.length; i++){

	for( int i = 1; i < way.size()-1; i++){
		cout << "var way1 = new google.maps.LatLng(" << get<0>(waypts.at(i))
			<<"," << get<1>(waypts.at(i))<<");";
		printf("waypts.push({");
		printf("location: way1,");
		printf("stopover:true});");
	}
			  
	printf(" var request = {");
	printf("origin:start,");
	printf("destination:end,");
	printf("waypoints: waypts,");
	printf("optimizeWaypoints: true,");
	//Added
	printf("avoidTolls: true,");
	printf("travelMode: google.maps.TravelMode.DRIVING");
	printf("};");
	printf("directionsService.route(request, function(response, status) {");
	printf(" if (status == google.maps.DirectionsStatus.OK) {");
	printf("directionsDisplay.setDirections(response);");
	printf(" }");
	printf(" });");
	printf("}");	


	ifstream infile_2;
	infile_2.open("end_1.txt");
	
	while(!infile_2.eof()){
		string line_2;
		getline(infile_2,line_2);
		cout << line_2;
	}
	infile_2.close();


	ifstream infile_1;
	infile_1.open("layout2.txt");
	
	while(!infile_1.eof()){
		string line_1;
		getline(infile_1,line_1);
		cout << line_1;
	}
	infile_1.close();
	cout <<"<p>Traffic data is collected at </p>" << capture_time << endl;
}
