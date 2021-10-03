#include<bits/stdc++.h>

using namespace std;

int main() {
	ifstream inputFile;
	inputFile.open("../input/question-2/main.csv");
	ofstream outputFile;
	outputFile.open("./main.csv");

	map<string, pair<int, int>> outputData; // automatically sort output in alphabetical order based on occupation col

	// just read the title lines and ignore list
	if (inputFile.good()) {
		string line;
		getline(inputFile, line, '\n');
	}


	while (inputFile.good()) {
		string userId, age, gender, occupation, zip;
		getline(inputFile, userId , ',');
		getline(inputFile, age , ',');
		getline(inputFile, gender , ',');
		getline(inputFile, occupation , ',');
		getline(inputFile, zip , '\n');

		if (outputData.find(occupation) == outputData.end()) {
			outputData[occupation] = {stoi(age), stoi(age)}; // stoi => string to integer, provided by c++
		} else {
			auto temp = outputData[occupation];
			// cout << temp << endl;
			outputData[occupation].first = min(temp.first, stoi(age));
			outputData[occupation].second = max(temp.second, stoi(age));
		}
	}

	inputFile.close();

	outputFile << "" << "," << "min" << "," << "max" << '\n';
	outputFile << "occupation" << "," << "" << "," << "" << '\n';

	for (auto data : outputData) {
		outputFile << data.first << "," << data.second.first << "," << data.second.second << '\n';
	}
	outputFile.close();
	return 0;

}