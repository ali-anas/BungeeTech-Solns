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
	ofstream outputFile;
	outputFile.open("./main.csv");


	// getting the data
	vector<vector<ll>> inputData;
	vector<vector<ll>> outputData;
	vector<string> columnTitles;
	getData(inputFile, inputData, columnTitles);

	// business logic

	// modular & scalable ignore column list
	// can add/remove columns in future.
	set<int> ignore_col_list = {2};

	vector<ll> temp(12, 0);
	int flag = 0;
	for (size_t row = 0; row < inputData.size(); row++) {
		for (size_t col = 0; col < inputData[row].size(); col++) {
			if (flag == 0) {
				// data of starting year of decade e.g. 1960, 1970 etc
				temp[0] = inputData[row][0];
			}

			if (col == 0) continue;
			temp[col] += inputData[row][col];
		}

		bool endOfInput = (row == ((int)inputData.size() - 1));
		// cout << endOfInput << endl;

		if (endOfInput || flag == 9) {
			// time to change the decade or end of inputData
			outputData.push_back(temp);

			// if decade has been changed
			// set temp values to default && flag value to 0
			if (!endOfInput) {
				fill(temp.begin(), temp.end(), 0);
				flag = -1; // will be updated to zero in below line
			}
		}
		flag++;
	}

	// write data titles to output file
	for (size_t col = 0; col < columnTitles.size(); col++) {
		// ignore the column from ignore_col_list
		if (ignore_col_list.find(col) != ignore_col_list.end()) continue;
		outputFile << columnTitles[col] << ",";
	} outputFile << endl;

	// write the rest data to the file
	for (size_t row = 0; row < outputData.size(); row++) {
		for (size_t col = 0; col < outputData[row].size(); col++) {
			// ignore the column from ignore_col_list
			if (ignore_col_list.find(col) != ignore_col_list.end()) continue;
			outputFile << outputData[row][col] << ",";
		} outputFile << endl;
	}

	return 0;
}