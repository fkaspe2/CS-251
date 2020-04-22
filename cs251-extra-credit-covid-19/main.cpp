/*main.cpp*/

//
// Frank Kasper
// CS 251
// Spring 2020
// COVID-19 extra credit
// 
// This program reads in data regarding the number of COVID-19
// cases across the globe and sorts them into a map so that 
// the most recent data can be easily accessed for each country
// 
// Data last recorded 3-18-2020
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <experimental/filesystem>
#include <locale>
#include <iomanip>
#include <vector>


#include <algorithm> 
#include <map>

using namespace std;
namespace fs = std::experimental::filesystem;

struct COVID_data {
	string confirmed;
	string deaths;
	string recovered;
};

struct country_data {
	string population;
	string life_expectancy;
};


//
// getFilesWithinFolder
//
// Given the path to a folder, e.g. "./daily_reports/", returns 
// a vector containing the full pathnames of all regular files
// in this folder.  If the folder is empty, the vector is empty.
//
vector<string> getFilesWithinFolder(string folderPath)
{
	vector<string> files;
	
	for (const auto& entry : fs::directory_iterator(folderPath))
	{
		files.push_back(entry.path().string());
	}
	
	// let's make sure the files are in alphabetical order, so we
    // process them in the correct order by date:
    std::sort(files.rbegin(), files.rend());
	
	return files;
}

//
// getDate()
// 
// truncates and returns daily_reports file 
// name to just the date in form . . .
// "XX-XX-XXXX"
// 
string getDate (string temp) 
{
	int pos1 = temp.find('-') - 2;
	temp.erase(0, pos1); 
	int pos2 = temp.find('.');
	temp.erase(pos2); 
	
	return temp;
}

//
// checkList()
// 
// check if country is in data set
// 
bool checkList(string countryName, vector<string> list) 
{
	for (unsigned int i = 0; i < list.size(); i++) {
		if (list.at(i) == countryName)
			return true;
	}
	return false;
}

//
// checkList()
// 
// check if country is in data set
// 
string find_firstConfirmed(unsigned int &counter, 
				  string name,
				  vector<string> dateList,
				  map<string, map<string, COVID_data> > file_map)
{
	string firstCase;
	map<string, COVID_data> find_case;
	unsigned int i;
	for (i = 0; i < dateList.size(); i++) {
		find_case = file_map[dateList[i]];
		
		if (find_case[name].confirmed == "") 
			find_case[name].confirmed = "0";
		
		if (stoi(find_case[name].confirmed) > 0) {
			firstCase = dateList[i];
			counter = i;
			break;
		}
	}
	if (firstCase == "")
		firstCase = "none";
	
	return firstCase;
}

string find_firstDeath(unsigned int &counter, 
				  string name,
				  vector<string> dateList,
				  map<string, map<string, COVID_data> > file_map)
{
	string firstCase;
	map<string, COVID_data> find_case;
	unsigned int i;
	for (i = 0; i < dateList.size(); i++) {
		find_case = file_map[dateList[i]];
		
		if (find_case[name].deaths == "") 
			find_case[name].deaths = "0";
		
		if (stoi(find_case[name].deaths) > 0) {
			firstCase = dateList[i];
			counter = i;
			break;
		}
	}
	if (firstCase == "")
		firstCase = "none";
	
	return firstCase;
}

string find_firstRecovered(unsigned int &counter, 
				  string name,
				  vector<string> dateList,
				  map<string, map<string, COVID_data> > file_map)
{
	string firstCase;
	map<string, COVID_data> find_case;
	unsigned int i;
	for (i = 0; i < dateList.size(); i++) {
		find_case = file_map[dateList[i]];
		
		if (find_case[name].recovered == "") 
			find_case[name].recovered = "0";
		
		if (stoi(find_case[name].recovered) > 0) {
			firstCase = dateList[i];
			counter = i;
			break;
		}
	}
	if (firstCase == "")
		firstCase = "none";
	
	return firstCase;
}


// 
// store_virus_data
// 
// Stores data from a file into each country and returns 
// a map where:
// key = country, value = map of data about country
// 
void store_virus_data (string country, COVID_data virus_data, map<string, COVID_data> &virus_map) 
{
	if (virus_map[country].confirmed == "") 
		virus_map[country].confirmed = "0";
	if (virus_map[country].deaths == "")
		virus_map[country].deaths = "0";
	if (virus_map[country].recovered == "")
		virus_map[country].recovered = "0";
	
	// convert string to int, then int back into string
	int intConfirmed = stoi(virus_map[country].confirmed) + stoi(virus_data.confirmed);
	int intDeaths = stoi(virus_map[country].deaths) + stoi(virus_data.deaths);
	int intRecovered = stoi(virus_map[country].recovered) + stoi(virus_data.recovered);
	
	virus_data.confirmed = to_string(intConfirmed);
	virus_data.deaths = to_string(intDeaths);
	virus_data.recovered = to_string(intRecovered);
	
	virus_map[country] = virus_data;
}


// 
// retrieve_country_map
// 
// Stores data from a line into map for a given country,
// updating the info for that date
// key = country, value = map of data about country
// 
map<string, COVID_data> retrieve_country_map (string filename, vector<string> &countryList) 
{
	string line;
	string country;
	COVID_data virus_data; // holds data from each line
	map<string, COVID_data> virus_map;
	
	ifstream infile;
	infile.open(filename);
	getline(infile, line); // ignores first line of file
	
	// reformat line 
	getline(infile, line);
	if (line[0] == '"') {
		line.erase(0,1);
		size_t pos = line.find(',');
		line.erase(pos, 1);
		pos = line.find('"');
		line.erase(pos, 1);
	}

	// store data into variables
	stringstream s(line);
	string last_update, province;
	getline (s, province, ',');
	getline (s, country, ','); // key for virus_map
	getline (s, last_update, ',');
	getline (s, virus_data.confirmed, ',');
	getline (s, virus_data.deaths, ',');
	getline (s, virus_data.recovered, ',');

	if (virus_data.confirmed == "")
		virus_data.confirmed = "0";
	if (virus_data.deaths == "")
		virus_data.deaths = "0";
	if (virus_data.recovered == "")
		virus_data.recovered = "0";
	if (country == "Mainland China")
		country = "China";
	
	// then store virus_data into file_data for that file
	while (!infile.eof())
	{
		// for the country on this line, 
		// store COVID_data into country's map
		store_virus_data(country, virus_data, virus_map);
		// store unique country names
		if (!checkList(country, countryList)) 
			countryList.push_back(country);		
		
		// reformat line 
		getline(infile, line);
		if (line[0] == '"') {
			line.erase(0,1);
			size_t pos = line.find(',');
			line.erase(pos, 1);
			pos = line.find('"');
			line.erase(pos, 1);
		}
		
		// store data into variables
		stringstream s(line);
		string last_update, province;
		getline (s, province, ',');
		getline (s, country, ','); // key for virus_map
		getline (s, last_update, ',');
		getline (s, virus_data.confirmed, ',');
		getline (s, virus_data.deaths, ',');
		getline (s, virus_data.recovered, ',');
		
		if (virus_data.confirmed == "")
			virus_data.confirmed = "0";
		if (virus_data.deaths == "")
			virus_data.deaths = "0";
		if (virus_data.recovered == "")
			virus_data.recovered = "0";
		if (country == "Mainland China")
			country = "China";
	}
	
	return virus_map;
}

//
// store_worldfacts_life_expectancy
// 
// store life_expectancy data for each country in most recent date
// 
void store_worldfacts_life_expectancy (string factsfile, map<string, country_data> &worldfacts_map )
{	
	string line;
	ifstream infile;
	infile.open(factsfile);
	
	getline(infile, line); // first line
	while (!infile.eof())
	{
		getline(infile, line);
				
		// store data into variables
		stringstream s(line);
		string position, country, fact_value;
		getline (s, position, ',');
		getline (s, country, ','); // key for virus_map
		getline (s, fact_value);
		
		if (fact_value == "")
			fact_value = "0";
		if (country == "Mainland China")
			country = "China";
		
		worldfacts_map[country].life_expectancy = fact_value;
	}
}

//
// store_worldfacts_population
// 
// store population data for each country in most recent date
// 
void store_worldfacts_population (string factsfile, map<string, country_data> &worldfacts_map )
{	
	string line;
	ifstream infile;
	infile.open(factsfile);
	
	getline(infile, line); // first line
	while (!infile.eof())
	{		
		getline(infile, line);
		
		// store data into variables
		stringstream s(line);
		string position, country, fact_value;
		getline (s, position, ',');
		getline (s, country, ','); // key for virus_map
		getline (s, fact_value);
		
		if (fact_value == "")
			fact_value = "0";
		if (country == "Mainland China")
			country = "China";
		
		worldfacts_map[country].population = fact_value;
	}
}



//
// "countries"
// 
// store population data for each country in most recent date
// 
void commandCountries (map<string, map<string, COVID_data> > file_map, 
					   vector<string> dateList) 
{
	vector<string> tempDates = dateList;
	vector<string> uniqueCountries;
	map<string, COVID_data> virus_data;
	
	for (int i = dateList.size()-1; i >= 0 ; i--) {
		map<string, COVID_data> map_info = file_map[tempDates[i]];
		
		for (auto store: map_info) {
			if (!checkList(store.first, uniqueCountries) ) {
				uniqueCountries.push_back(store.first);
				virus_data.emplace(store.first, store.second);
			}
		}
	}
	for (auto printmap: virus_data) {
		cout << printmap.first
			 << ": " << printmap.second.confirmed 
			 << ", " << printmap.second.deaths
			 << ", " << printmap.second.recovered
			 << endl;
	}
	
}

//
// "top10"
// 
// store population data for each country in most recent date
// 
void commandTop10 (map<string, map<string, COVID_data> > file_map, string date) 
{
	map<string, COVID_data> virus_data = file_map[date];
	map<int, string> confirmed_data; // <confirmed, name>
	map<int, string>::reverse_iterator it; 
	for (auto storemap: virus_data) {
		confirmed_data[stoi(storemap.second.confirmed)] = storemap.first; 
	}
	
	//std::sort(confirmed_data.begin(), confirmed_data.end());
	
	int rank = 1;	
	
	// loop thru map backwards, stop at 10
    for (it = confirmed_data.rbegin(); it != confirmed_data.rend(); it++) { 
        cout << rank << ". ";
		cout << it->second;
		cout << ": " << it->first << endl;
		rank++;
		if (rank > 10) 
			break;
    } 
	
}

//
// "totals"
// 
// store population data for each country in most recent date
// 
void commandTotals (map<string, map<string, COVID_data> > file_map, string date) 
{
	int confirmedtotal = 0;
	int deathstotal = 0;
	int recoveredtotal = 0;
	map<string, COVID_data> virus_data = file_map[date];
	for (auto printmap: virus_data) {
		confirmedtotal += stoi(printmap.second.confirmed);
		deathstotal += stoi(printmap.second.deaths);
		recoveredtotal += stoi(printmap.second.recovered);
	}
	double percentdeath = 100 * ( ((double) deathstotal)/ ((double) confirmedtotal));
	double percentrecovered = 100 * ( ((double) recoveredtotal)/ ((double) confirmedtotal));
	
	cout << "As of " << date << ", the world-wide totals are:" << endl;
	cout << " confirmed: " << confirmedtotal << endl;
	cout << " deaths: " << deathstotal << " (" << percentdeath << "%)" << endl;
	cout << " recovered: " << recoveredtotal << " (" << percentrecovered << "%)" << endl;
}


//
// <name>
// 
// store population data for each country in most recent date
// 
void commandName (string name,
				  map<string, map<string, COVID_data> > file_map,
				  vector<string> dateList,
				  map<string, country_data> worldfacts_map) 
{
	map<string, COVID_data> virus_data = file_map[dateList.back()];
	string firstCase, firstDeath;
	unsigned int counter;
	
	cout << "Population: " << stoi(worldfacts_map[name].population) << endl;
	cout << "Life Expectancy: " << worldfacts_map[name].life_expectancy << " years" << endl;
	cout << "Latest data:" << endl; 
	cout << " confirmed: " << stoi(virus_data[name].confirmed) << endl;
	cout << " deaths: " << stoi(virus_data[name].deaths) << endl;
	cout << " recovered: " << stoi(virus_data[name].recovered) << endl;
	
	firstCase = find_firstConfirmed(counter, name, dateList, file_map);
	firstDeath = find_firstDeath(counter, name, dateList, file_map);
		
	cout << "First confirmed case: " << firstCase << endl;
	cout << "First confirmed death: " << firstDeath << endl;
	cout << "Do you want to see a timeline? Enter c/d/r/n> ";
	string response;
	cin >> response;
		
	// confirmed timeline
	if (response == "c") {
		cout << "Confirmed:" << endl;
		
		map<string, COVID_data> timeline = file_map[dateList[counter]];
		unsigned int day = 1;
		bool time_skip = false;
		while (dateList.back() != dateList[counter])
		{
			cout << dateList[counter] 
				 << " (day " << day << "): " 
				 << stoi(timeline[name].confirmed)
				 << endl;	
			counter++;
			day++;
			if (day > 7 && time_skip == false) {
				cout << " ." << endl << " ." << endl << " ." << endl;
				counter = dateList.size() - 8;
				day = dateList.size() - 7;
				time_skip = true;
				counter++;
				day++;
			}
			timeline = file_map[dateList[counter]];
		}
		cout << dateList[counter] 
			 << " (day " << day << "): " 
			 << stoi(timeline[name].confirmed)
			 << endl;	
	}
	
	
	
	// deaths timeline
	else if (response == "d") {
		cout << "Deaths:" << endl;
		
		map<string, COVID_data> timeline = file_map[dateList[counter]];
		unsigned int day = 1;
		bool time_skip = false;
		while (dateList.back() != dateList[counter])
		{
			cout << dateList[counter] 
				 << " (day " << day << "): " 
				 << stoi(timeline[name].deaths)
				 << endl;	
			counter++;
			day++;
			if (day > 7 && time_skip == false) {
				cout << " ." << endl << " ." << endl << " ." << endl;
				counter = dateList.size() - 8;
				day = dateList.size() - 7;
				time_skip = true;
				counter++;
				day++;
			}
			timeline = file_map[dateList[counter]];
		}
		cout << dateList[counter] 
			 << " (day " << day << "): " 
			 << stoi(timeline[name].deaths)
			 << endl;	
	}
	
	// recovered timeline
	else if (response == "r") {
		cout << "Recovered:" << endl;
		string firstRecovered = find_firstDeath(counter, name, dateList, file_map);
		
		map<string, COVID_data> timeline = file_map[dateList[counter]];
		unsigned int day = 1;
		bool time_skip = false;
		while (dateList.back() != dateList[counter])
		{
			cout << dateList[counter] 
				 << " (day " << day << "): " 
				 << stoi(timeline[name].recovered)
				 << endl;	
			counter++;
			day++;
			
			
			if (day > 7 && time_skip == false) {
				cout << " ." << endl << " ." << endl << " ." << endl;
				counter = dateList.size() - 8;
				day = dateList.size() - 7;
				time_skip = true;
				counter++;
				day++;
			}
			timeline = file_map[dateList[counter]];
		}
		cout << dateList[counter] 
			 << " (day " << day << "): " 
			 << stoi(timeline[name].recovered)
			 << endl;
	}
	
	// no timeline needed B^)
	else if (response == "n") {
		return;
	}
	
}

//
// main:
//
int main()
{
	cout << "** COVID-19 Data Analysis **" << endl;
	cout << endl;
	cout << "Based on data made available by John Hopkins University" << endl;
	cout << "https://github.com/CSSEGISandData/COVID-19" << endl;
	cout << endl;
	
	//
	// setup cout to use thousands separator, and 2 decimal places:
	//
	cout.imbue(std::locale(""));
	cout << std::fixed;
	cout << std::setprecision(2);
	
	//
	// get a vector of the daily reports, one filename for each:
	//
	vector<string> files = getFilesWithinFolder("./daily_reports/");
		
	map<string, map<string, COVID_data> > file_map; // <date, virus_data>
	string filename, date;
	ifstream infile;
	map<string, COVID_data> virus_data;             // holds data from each line
	int reportsFileCounter = 0;
	vector<string> countryList;
	vector<string> dateList;
			
	//
	// for first file
	filename = files.back();
	infile.open(filename);
	if (!infile.is_open()) {
		cout << "**file not found**" << endl;
		return 0;
	}
	
	// store date into map as key
	date = getDate(filename);
	dateList.push_back(date);
	file_map[date] = retrieve_country_map(filename, countryList);
	files.pop_back();
	reportsFileCounter++;
	
	//
	// rest of files
	while (!files.empty()) 
	{
		filename = files.back();
		infile.open(filename);
		if (!infile.is_open()) {
			cout << "**file not found**" << endl;
			return 0;
		}
		
		// store date into map as key
		date = getDate(filename);
		dateList.push_back(date);
		file_map[date] = retrieve_country_map(filename, countryList);    // add new counts
		files.pop_back();
		reportsFileCounter++;
	}
	
	
	//
	// worldfacts
	// 
	// worldfacts files
	vector<string> facts = getFilesWithinFolder("./worldfacts/");
	int factsFileCounter = 0;
	map<string, country_data> worldfacts_map; // <name, data>
	
	// life_expectancy
	infile.open(facts.back());
	if (!infile.is_open()) {
		cout << "**file not found**" << endl;
		return 0;
	}
	store_worldfacts_life_expectancy(facts.back(), worldfacts_map);
	factsFileCounter++;
	facts.pop_back();
	
	// population
	infile.open(facts.back());
	if (!infile.is_open()) {
		cout << "**file not found**" << endl;
		return 0;
	}
	store_worldfacts_population(facts.back(), worldfacts_map);
	factsFileCounter++;
	facts.pop_back();
	
	// changes blank values to 0
	for (auto printmap: worldfacts_map) {
		if (printmap.second.population == "")
			printmap.second.population = "0";
		if (printmap.second.life_expectancy == "")
			printmap.second.life_expectancy = "0";
	}
	
	// end storing
	// proceed with data output
	std::sort(countryList.begin(), countryList.end());
	cout << endl;
	cout << ">> Processed " << reportsFileCounter << " daily reports" << endl;
	cout << ">> Processed " << factsFileCounter << " files of world facts" << endl;
	cout << ">> Current data on " << countryList.size() << " countries" << endl;
	cout << endl;
	cout << "Enter command (help for list, # to quit)> ";
	string command;
	cin >> command;
	
	while (command != "#" )
	{
		// help menu
		if (command == "help") {
			cout << "<name>: enter a country name such as US or China" << endl;
			cout << "countries: list all countries and most recent report" << endl;
			cout << "top10: list of top 10 countires based on most recent # of confirmed cases" << endl;
			cout << "totals: world-wide totals of confirmed, deaths, recovered" << endl;
			cout << endl;
		}
		
		else if (command == "countries") {
			commandCountries(file_map, dateList);	
		}
		
		else if (command == "top10") {
			commandTop10(file_map, date);	
		}
		
		else if (command == "totals") {
			commandTotals(file_map, date);	
		}
		
		else if (checkList(command, countryList)) {
			commandName(command, file_map, dateList, worldfacts_map);
		}
		
		else {
			cout << "country or command not found..." << endl;
		}
		
		cout << endl << "Enter command> ";
		cin >> command;
	}
	
	
	
	
	return 0;
}
