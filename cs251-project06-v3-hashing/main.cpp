/*main.cpp*/

//
// Frank Kasper
// U. of Illinois, Chicago
// CS 251: Spring 2020
// 
// Project 6
// 
// Reads in data from DIVVY files regrading bike and user information
// and stores it into two hashtables to be searched from
// 

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <algorithm> 
#include <utility>

#include "hash.h"
#include "hashmap.h"
#include "util.h"

using namespace std;


//
// Stations
// 
struct Stations
{
	string StationId;
	string StationAbbrev;
	string Full;
	string Lat;
	string Long;
	string Cap;
	string Date;
	
	Stations()
	{
		StationId = "";
		StationAbbrev = "";
		Full = "";
		Lat = "";
		Long = "";
		Cap = "";
		Date = "";
	}
};

//
// Trips
// 
struct Trips
{
	string TripId;
	string Start;
	string Stop;
	string BikeId;
	string Duration;
	string From;
	string To;
	string Identifier;
	string Birthyear;
	int usage;
	
	Trips()
	{
		TripId = "";
		Start = "";
		Stop = "";
		BikeId = "";
		Duration = "";
		From = "";
		To = "";
		Identifier = "";
		Birthyear = "";
		usage = 0;
	}
};

//
// string2int
// 
// Converts a string to an integer, unless string is empty, in
// which case 0 is returned.
// 
int string2int(string s)
{
	if (s == "")
		return 0;
	else
		return stoi(s);
}

//
// inputStations
// 
// Given a filename denoting lottery winning numbers,
// inputs that data into the given hash table.
// 
bool inputStations(string filename,
				   hashmap<string, Stations>& stationsById,
				   hashmap<string, Stations>& stationsByAbbrev,
				   int &stationCount)
{
	ifstream  infile(filename);
	
	cout << "Reading " << filename << endl;
	if (!infile.good()) {
		cout << "**Error: unable to open '" << filename << "'..." << endl;
		return false;
	}
	
	// file is open, start processing:
	string line;
	getline(infile, line);  // input and discard first row --- header row
		
	while (getline(infile, line))
	{
		stringstream s(line);
		string id,abbrev,fullname,latitude,longitude,capacity,online_date;
		
		getline(s, id, ',');
		getline(s, abbrev, ',');
		getline(s, fullname, ',');
		getline(s, latitude, ',');
		getline(s, longitude, ',');
		getline(s, capacity, ',');
		getline(s, online_date, ',');
				
		// store into hash table
		Stations st;
		
		st.StationId = id;
		st.StationAbbrev = abbrev;
		st.Full = fullname;
		st.Lat = latitude;
		st.Long = longitude;
		st.Cap = capacity;
		st.Date = online_date;
		
		stationsById.insert(id, st, Hash);
		stationsByAbbrev.insert(abbrev, st, Hash);
		
		stationCount++;
	}	
	return true;  // we have data to be processed:
}

//
// inputTrips
// 
// Given a filename denoting lottery winning numbers,
// inputs that data into the given hash table.
// 
bool inputTrips(string filename,
				hashmap<string, Trips>& tripsById,
				hashmap<string, int>& bikesById,
				int &tripCount,
			    int &bikeCount)
{
	ifstream  infile(filename);
	
	cout << "Reading " << filename << endl;
	if (!infile.good()) {
		cout << "**Error: unable to open '" << filename << "'..." << endl;
		return false;
	}
	
	// file is open, start processing:
	string line;
	getline(infile, line);  // input and discard first row --- header row
	
	while (getline(infile, line))
	{
		stringstream s(line);
		string tripid,starttime,stoptime,bikeid,duration,from,to,identifies,birthyear;
		
		getline(s, tripid, ',');  
		getline(s, starttime, ',');   
		getline(s, stoptime, ',');
		getline(s, bikeid, ',');
		getline(s, duration, ',');  
		getline(s, from, ',');   
		getline(s, to, ',');
		getline(s, identifies, ',');   
		getline(s, birthyear, ',');
				
		// store into hash table
		Trips tr;
		tr.TripId = tripid;
		tr.Start = starttime;
		tr.Stop = stoptime;
		tr.BikeId = bikeid;
		tr.Duration = duration;
		tr.From = from;
		tr.To = to;
		tr.Identifier = identifies;
		tr.Birthyear = birthyear;
		
		// checks if bike was salready used
		if (!bikesById.search(bikeid, tr.usage, Hash) )
		{
			bikeCount++;
		}
		tr.usage++; // tracks times this bike was used
		bikesById.insert(bikeid, tr.usage, Hash);
		tripsById.insert(tripid, tr, Hash);
		tripCount++;
	}
	return true;  // we have data to be processed:
}


int main()
{
	cout << "** DIVVY analysis program **" << endl;
	cout << endl;
	
	hashmap<string, Stations> stationsById(10000);
	hashmap<string, Stations> stationsByAbbrev(10000);
	hashmap<string, Trips> tripsById(2500000);
	hashmap<string, int> bikesById(50000);
	int stationCount = 0;
	int tripCount = 0;
	int bikeCount = 0;

	string filename1;
	string filename2;
	
	cout << "Enter stations file> ";
	getline(cin, filename1);
	
	cout << "Enter trips file> ";
	getline(cin, filename2);
	cout << endl;
	
	// input the data, check if it worked
	bool success = inputStations(filename1, 
								 stationsById, 
								 stationsByAbbrev, 
								 stationCount);
	if (!success)
	{
		cout << "No data, file not found?" << endl;
		return 0;
	}
	
	success = inputTrips(filename2, 
						 tripsById, 
						 bikesById, 
						 tripCount,
						 bikeCount);
	if (!success)
	{
		cout << "No data, file not found?" << endl;
		return 0;
	}
	
	// print data counts
	cout << endl;
	cout << "# of stations: " << stationCount << endl;
	cout << "# of trips: " << tripCount << endl;
	cout << "# of bikes: " << bikeCount << endl;
	
	// allow the user to lookup certain things:
	string input;
	cout << endl;
	cout << "Please enter a command, help, or #> ";
	getline(cin, input);
	
	// input filter
	while (input != "#")
	{	
	// words to filter prompts given
	string temp = input;
	string testIfBike = input.erase(0,1);
	string testIfTrip = input.erase(0,1);
	input = temp;
	
	// 
	// help menu
	// 
	if (input == "help") {
		cout << "Available commands: " << endl;
		cout << " Enter a station id (e.g. 341)" << endl;
		cout << " Enter a station abbreviation (e.g. Adler)" << endl;
		cout << " Enter a trip id (e.g. Tr10426561)" << endl;
		cout << " Enter a bike id (e.g. B5218)" << endl;
		cout << " Nearby stations (e.g. nearby 41.86 -87.62 0.5)" << endl;
		cout << " Similar trips (e.g. similar Tr10424639 0.3)" << endl;
	}
	
	//
	// searches by stationId
	// 
	else if (isNumeric(input)) {
		Stations st;
		
		bool found = stationsById.search(input, st, Hash);
		if (found == true) {
			cout << "Station: " << endl;
			cout << " Id: " << st.StationId << endl;
			cout << " Abbrev: " << st.StationAbbrev << endl;
			cout << " Fullname: " << st.Full << endl;
			cout << " Location: (" << stod(st.Lat) << ", " << stod(st.Long) << ")" << endl;
			cout << " Capacity: " << st.Cap << endl;
			cout << " Online Date: " << st.Date << endl;
		}
		else {
			cout << "Station not found" << endl;
		}
	}
	
	//
	// searches by trip id
	// 
	// Finds an inidivdual trip by the tripid entered. 
	// 
	else if (input[0] == 'T' && input[1] == 'r' && isNumeric(testIfTrip)) {
		Trips tr;
		Stations st1;
		Stations st2;
		
		bool found1 = tripsById.search(input, tr, Hash);
		// used to get station names
		bool found2 = stationsById.search(tr.From, st1, Hash);
		bool found3 = stationsById.search(tr.To, st2, Hash);
		
		if (found1 && found2 && found3) {
			cout << "Trip: " << endl;
			cout << " ID: " << input << endl;
			cout << " Starttime: " << tr.Start << endl;
			cout << " Bikeid: " << tr.BikeId << endl;
			
			// splits duration into hrs, mins, secs
			int hours = 0;
			int minutes = 0;
			int seconds = 0;
			hours = stoi(tr.Duration) / 3600;
			minutes = (stoi(tr.Duration) - hours*3600) / 60;
			seconds = stoi(tr.Duration) - hours*3600 - minutes*60;
			cout << " Duration: ";
			if (hours > 0) {cout << hours << " hours, ";}
			if (minutes > 0) {cout << minutes << " minutes, ";}
			cout << seconds << " seconds" << endl;
			
			cout << " From station: " << st1.StationAbbrev << " (" << tr.From << ") " << endl;
			cout << " To station: " << st2.StationAbbrev << " (" << tr.To << ") " << endl;	
			cout << " Rider identifies as: " << tr.Identifier << endl;
			cout << " Birthyear: " << tr.Birthyear << endl;
		}
		else {
			cout << "Trip not found" << endl;
		}		
	}
	
	//
	// searches by bike id
	// 
	// Finds bike id in hashtable, print how many times the bike was used
	// 
	else if (input[0] == 'B' && isNumeric(testIfBike)) {
		int used;
		
		bool found = bikesById.search(input, used, Hash);
		if (found == true) {
			cout << "Bike: " << endl;
			cout << " Id: " << input << endl;
			cout << " Usage: " << used << endl;
		}
		else {
			cout << "Bike not found" << endl;
		}		
	}
	
	//
	// nearby
	// 
	// Find all staions within a certain distance of a 
	// given coordinate
	// 
	else if (input.find("nearby") != string::npos) {
		// copy input into strings
		stringstream s(input);
		string nearby, longitude, latitude, miles;
		getline(s, nearby, ' ');
		getline(s, latitude, ' ');  
		getline(s, longitude, ' ');   
		getline(s, miles, '\n');
		
		// grab keys from stations data
		set<string> keys = stationsById.collect();
		vector<double> closestDistance;
		vector<string> closestId;
		
		double long1, lat1, long2, lat2, distance, numberMiles;
		numberMiles = stod(miles);
		Stations st;
		
		// search copy over data from hashmap at each keys
		// get long and lat to calc. distance
		for (auto key : keys) {
			if(stationsById.search(key, st, Hash)) 
			{
				lat1 = stod(st.Lat);
				long1 = stod(st.Long);
				lat2 = stod(latitude);
				long2 = stod(longitude);
				
				distance = distBetween2Points(lat2, long2, lat1, long1);
				closestDistance.push_back(distance);
				closestId.push_back(key);
			}
		}
		
		// print stored data
		cout << "Stations within " << miles << " miles of (" 
			 << latitude << ", " << longitude << ")" << endl;
		
		// if none within range
		if (closestDistance.empty()) {
			cout << " none found" << endl;
			cout << endl;
			cout << "Please enter a command, help, or #> ";
			getline(cin, input);
			continue;
		}
		
		// if map has entrees
		// print in order where closest is first
		for (unsigned int i = 0; i < closestDistance.size(); i++) 
		{
			if (closestDistance.at(i) <= numberMiles) {
				cout << " station " << closestId.at(i) << ": " 
					 << closestDistance.at(i) << " miles" << endl;
			}
		}
	} 
		
	//
	// similar
	// 
	// Finds routes that are similar in distance/ path by comparing 
	// the station locations to those around it
	// 
	else if (input.find("similar") != string::npos) {
		// copy input into strings
		stringstream s(input);
		string similar, tripid, miles;
		getline(s, similar, ' ');
		getline(s, tripid, ' ');  
		getline(s, miles, '\n');
		
		cout << "Trips that follow a similar path (+/-" << miles
			 << " miles) as " << tripid << endl;
		
		Stations st;   // tracks station record
		Trips tr;      // tracks trip record
		
		// check if trip id doesnt exist
		bool found = tripsById.search(tripid, tr, Hash);
		
		if (!found) {
			cout << " no such trip" << endl;
			cout << endl;
			cout << "Please enter a command, help, or #> ";
			getline(cin, input);
			continue;
		}
		
		string from_id = tr.From; // id of from station
		string to_id = tr.To;     // id of to station
		
		// get lats and longs at the from and to stations
		stationsById.search(from_id, st, Hash); 
		double from_lat = stod(st.Lat);
		double from_long = stod(st.Long);
		stationsById.search(to_id, st, Hash);  
		double to_lat = stod(st.Lat);
		double to_long = stod(st.Long);
		
		// sets used to track station keys and stations within distance
		set<string> keys = stationsById.collect();
		vector<int> StartIds_vector;
		vector<int> EndIds_vector;
		set<string> StartIds_set;
		set<string> EndIds_set;
		
		//
		// calculate distances
		// 
		double numberMiles = stod(miles);
		double comp_lat, comp_long, from_distance, to_distance;
		for (auto key : keys) 
		{
			stationsById.search(key, st, Hash); // grab data using station id
			
			// grab lat and long from each id in keys
			comp_lat = stod(st.Lat);
			comp_long = stod(st.Long);
			
			// get the distances relative -> from & to
			from_distance = distBetween2Points(comp_lat, comp_long, from_lat, from_long);
			to_distance = distBetween2Points(comp_lat, comp_long, to_lat, to_long);
			
			// store if close enough
			if (from_distance <= numberMiles) {
				StartIds_vector.push_back(stoi(key));
				StartIds_set.insert(key);
			}
				
			if (to_distance <= numberMiles) {
				EndIds_vector.push_back(stoi(key));
				EndIds_set.insert(key);
			}
		}
		
		// sort and print data by ids
		cout << " nearby starting points: ";
		std::sort(StartIds_vector.begin(), StartIds_vector.end());
		for(unsigned int i = 0; i < StartIds_vector.size(); i++) {
			cout << StartIds_vector.at(i) << " ";
		}
		
		cout << endl << " nearby ending points: ";
		std::sort(EndIds_vector.begin(), EndIds_vector.end());
		for(unsigned int i = 0; i < EndIds_vector.size(); i++) {
			cout << EndIds_vector.at(i) << " ";
		}
		cout << endl;
		
		// go thru each tripid
		// if there is a from->to that corresponds, tripcount+1
		set<string> trips = tripsById.collect();
		int tripCount = 0;
		for (auto trip : trips) 
		{
			tripsById.search(trip, tr, Hash);
			if (StartIds_set.count(tr.From) > 0 && EndIds_set.count(tr.To) > 0 )
				tripCount++;
		}
		cout << " trip count: " << tripCount << endl;
	} 
	
	//
	// searches by stationAbbrev
	// 
	else {
		Stations st;
		bool found = stationsByAbbrev.search(input, st, Hash);
		if (found == true) {
			cout << "Station: " << endl;
			cout << " Id: " << st.StationId << endl;
			cout << " Abbrev: " << st.StationAbbrev << endl;
			cout << " Fullname: " << st.Full << endl;
			cout << " Location: (" << stod(st.Lat) << ", " << stod(st.Long) << ")" << endl;
			cout << " Capacity: " << st.Cap << endl;
			cout << " Online Date: " << st.Date << endl;
		}
		else {
			cout << "Station not found" << endl;
		}
	}
	
	cout << endl;
	cout << "Please enter a command, help, or #> ";
	getline(cin, input);
	}
		
	return 0;
}