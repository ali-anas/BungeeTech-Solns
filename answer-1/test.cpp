#include <bits/stdc++.h>
#include <fstream>
#include <sstream>
using namespace std;

#define ll long long int


void getTitles(const string &line, vector<string>& columnTitles) {
	if (line.size() == 0) {
		cout << "something went wrong while parsing titles line..." << endl;
		return;
	}
	istringstream iss(line);

	while (iss.good()) {
		string substr;
		getline(iss, substr, ',');
		columnTitles.push_back(substr);
	}

	// cout << "titles size in getTitles: " << columnTitles.size() << endl;
}

void getSingleLineData(const string& line, vector<ll> &singleLineData) {
	if (line.size() == 0) {
		cout << "something went wrong while parsing titles line..." << endl;
		return;
	}

	istringstream iss(line);
	for (ll value; iss >> value; ) {
		singleLineData.push_back(value);
		if (iss.peek() == ',')
			iss.ignore();
	}

}

void getData(ifstream& inputFile, vector<vector<ll>>& inputData, vector<string>& columnTitles) {
	// read column titles
	if (inputFile.good()) {
		string titlesLine;
		getline(inputFile, titlesLine, '\n');
		getTitles(titlesLine, columnTitles);
	}

	// read rest of the data
	while (inputFile.good()) {
		vector<ll> singleLineData;
		string line;
		getline(inputFile, line, '\n');
		getSingleLineData(line, singleLineData);
		inputData.push_back(singleLineData);
	}

}

int main() {
	ifstream inputFile;
	inputFile.open("../input/question-1/main.csv");
	// ofstream outputFile;
	// outputFile.open("./main.csv");

	vector<vector<ll>> inputData;
	vector<string> columnTitles;


	getData(inputFile, inputData, columnTitles);

	// cout << "parsing completed..." << endl;
	// cout << columnTitles.size() << endl;
	for (size_t i = 0; i < columnTitles.size(); i++) {
		cout << columnTitles[i] << " ";
	} cout << endl;

	for (size_t i = 0; i < inputData.size(); i++) {
		for (size_t j = 0; j < inputData[i].size(); j++) {
			cout << inputData[i][j] << " ";
		} cout << endl;
	}

	return 0;
}