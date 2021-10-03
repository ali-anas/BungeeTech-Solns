#include <bits/stdc++.h>
#include <fstream>
using namespace std;

// comparator for our sort function
bool compare(const vector<string> &first, const vector<string> &other) {
	if (stoi(first[3]) == stoi(other[3])) {
		return stoi(first[2]) > stoi(other[2]);
	}
	return stoi(first[3]) > stoi(other[3]);
}

int main() {
	ifstream inputFile;
	inputFile.open("../input/question-3/main.csv");
	ofstream outputFile;
	outputFile.open("./main.csv");

	unordered_set<int> isUsefulCol = {0, 30, 31};

	// read and ignore titles row
	if (inputFile.good()) {
		string line;
		getline(inputFile, line, '\n');
	}

	vector<vector<string>> allData;

	int index = 0;
	while (inputFile.good()) {
		vector<string> temp(35);
		vector<string> usefulContent;
		usefulContent.push_back(to_string(index));
		for (int i = 0; i < 35; i++) {
			if ( i == 34 ) {
				getline(inputFile, temp[i], '\n');
			} else {
				getline(inputFile, temp[i], ',');
			}
			if (isUsefulCol.find(i) != isUsefulCol.end()) {
				usefulContent.push_back(temp[i]);
			}
		}
		allData.push_back(usefulContent);

		index++;
	}

	sort(allData.begin(), allData.end(), compare);


	size_t totalCols = isUsefulCol.size() + 1;
	// start writing the output file
	outputFile << "" << "," << "Team" << "," << "Yellow Cards" << "," << "Red Cards" << '\n';
	for (size_t i = 0; i < allData.size(); i++) {
		for (size_t j = 0; j < allData[i].size(); j++) {
			if (j == totalCols - 1) {
				outputFile << allData[i][j];
			} else {
				outputFile << allData[i][j] << ",";
			}
		} outputFile << '\n';
	}

	return 0;
}