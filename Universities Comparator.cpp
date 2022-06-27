#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

// Store maximum number of universities in memory constsant
const int maxUniversities = 1000;

// Prototype
int getData(ifstream& fileInput, string universityNames[], string states[], string city[], double tuition[], int enrollment[], double averageRetention[], double graduationPercentage[]);
void writeFile(ofstream& fileOutput, string universityNames[], string states[], double tuition[], int enrollment[], double averageRetention[], double graduationPercentage[], int numUniversities);
double calcAvgTuition(double tuition[], int numUniversities);
void maxTutionFee(string universityNames[], double tuition[], int numUniversities);
void stateCollegesInformation(ofstream& fileOutput, string universityNames[], string states[], double tuition[], int enrollment[], double averageRetention[], double graduationPercentage[], int numUniversities);
double calcLowestTution(double tuition[], int numUniversities);
void sort(string universityNames[], string states[], double tuition[], int enrollment[], double averageRetention[], double graduationPercentage[], int numUniversities);

int main() {
	// Declare arrays
	string universityNames[maxUniversities];
	string states[maxUniversities];
	string city[maxUniversities];
	double tuition[maxUniversities];
	int enrollment[maxUniversities];
	double averageRetention[maxUniversities];
	double graduationPercentage[maxUniversities];
	
	// Declare variables
	int numUniversities;
	double tuitionAverage;
	
	// Open file for input
	ifstream fileInput;
	fileInput.open("UniversitiesData.txt");
	
	// Create/open file for output
	ofstream fileOutput;
	fileOutput.open("Universities Comparator Output.txt");
	
	// Check if input file exists - if file does not exist, terminate the program
	if(fileInput.fail()) {
			cout << "No such file exists" << endl;
			system("pause");
			exit(100);
	}
	
	// Call getData() function to get number of universities
	numUniversities = getData(fileInput, universityNames, states, city, tuition, enrollment, averageRetention, graduationPercentage);
	fileOutput << setprecision(2) << fixed;
	cout << setprecision(2) << fixed;
	
	// Convert decimal values for retention/graudation rates to percentages
	for(int i = 0; i < numUniversities; i++) {
		averageRetention[i] *= 100.00;
		graduationPercentage[i] *= 100.00;
	}
	
	// Output to a file all data in the original order (unsorted)
	writeFile(fileOutput, universityNames, states, tuition, enrollment, averageRetention, graduationPercentage, numUniversities);
	
	// Call calcAvgTuition() function to get average tuition amount
	tuitionAverage = calcAvgTuition(tuition, numUniversities);
	cout << "Average tution: " << tuitionAverage << endl;
	cout << endl;
	
	// Call maxTuitionFee() function to ask user for maximum he/she can pay for tuition and tell user what schools he/she can afford
	maxTutionFee(universityNames, tuition, numUniversities);
	
	// Call stateCollegesInformation() function to prompt user for a two-letter abbreitvation for a state and output to file all information for colleges within that state or output message "No colleges in XXX state in the list"
	stateCollegesInformation(fileOutput, universityNames, states, tuition, enrollment, averageRetention, graduationPercentage, numUniversities);
	
	// Calculate university/universities with lowest tuition
	double lowestTuition = calcLowestTution(tuition, numUniversities);
	
	// Output to screen university/universities with lowest tuition
	cout << "University/universities with lowest tuition: " << endl;
	for(int i = 0; i < numUniversities; i++) {
		if(tuition[i] == lowestTuition) {
			cout << universityNames[i] << " - " << tuition[i] << endl;
		}
	}
	
	// Call sort() function to sort universities in descending order by percentage graduating in 6 years
	sort(universityNames, states, tuition, enrollment, averageRetention, graduationPercentage, numUniversities);
	
	// Output sorted array to file
	fileOutput << endl;
	writeFile(fileOutput, universityNames, states, tuition, enrollment, averageRetention, graduationPercentage, numUniversities);
	
	// Close input file and output file
	fileInput.close();
	fileOutput.close();
}

int getData(ifstream& fileInput, string universityNames[], string states[], string city[], double tuition[], int enrollment[], double averageRetention[], double graduationPercentage[]) {
	int i = 0;
	double temp;
	while(!fileInput.eof()) {
		getline(fileInput, universityNames[i]);
		fileInput >> states[i];
		getline(fileInput, city[i]);
		fileInput >> tuition[i] >> enrollment[i];
		fileInput >> temp;
		fileInput >> averageRetention[i] >> graduationPercentage[i];
		
		// Ignore newlines
		fileInput.ignore();
		
		i++;
	}
	return i;
}

void writeFile(ofstream& fileOutput, string universityNames[], string states[], double tuition[], int enrollment[], double averageRetention[], double graduationPercentage[], int numUniversities) {
	fileOutput << setprecision(2) << fixed;
	fileOutput << "University                          State Tuition Enrollment %Fresh    %Graduate" << endl;
	fileOutput << "                                                             Succeed   in six years" << endl;
	for(int i = 0 ; i < numUniversities; i++) {
		fileOutput << setw(40) << left << universityNames[i] << setw(2) << left << states[i] << " " << tuition[i] << " " << setw(7) << right << enrollment[i] << "  " <<  averageRetention[i] << "%" << "    " << graduationPercentage[i] << "%" << endl;
	}
}

double calcAvgTuition(double tuition[], int numUniversities) {
	double sum = 0;
	double average = 0;
	for(int i = 0; i < numUniversities; i++) {
		sum += tuition[i];
	}
	average = sum / numUniversities;
	return average;
}

void maxTutionFee(string universityNames[], double tuition[], int numUniversities) {
	double maxTuition;
	cout << "Enter maximum tuition you can pay: ";
	cin >> maxTuition;
	cout << "All schools you can afford:" << endl;
	for(int i = 0; i < numUniversities; i++) {
		if(tuition[i] <= maxTuition) {
			cout << universityNames[i] << endl;
		}
	}
}

void stateCollegesInformation(ofstream& fileOutput, string universityNames[], string states[], double tuition[], int enrollment[], double averageRetention[], double graduationPercentage[], int numUniversities) {
	string stateInput;
	cout << endl;
	cout << "Enter two-letter abbreviation for a state: ";
	cin >> stateInput;
	int status = 0;
	fileOutput << endl;
	fileOutput << "Information about colleges in " << stateInput << ":" << endl;
	for(int i = 0; i < numUniversities; i++) {
		if(stateInput == states[i]) {
			fileOutput << setw(40) << left << universityNames[i] << setw(2) << left << states[i] << " " << tuition[i] << " " << setw(7) << right << enrollment[i] << "  " <<  averageRetention[i] << "%" << "    " << graduationPercentage[i] << "%" << endl;
			status = 1;
		} 
	}
	if(status == 0) {
		fileOutput << "No colleges in " << stateInput << " state in the list" << endl;
	}
	cout << endl;
}

double calcLowestTution(double tuition[], int numUniversities) {
	double lowestTution = tuition[0];
	for(int i = 1; i < numUniversities; i++) {
		if(lowestTution > tuition[i]) {
			lowestTution = tuition[i];
		}
	}
	return lowestTution;
}

void sort(string universityNames[], string states[], double tuition[], int enrollment[], double averageRetention[], double graduationPercentage[], int numUniversities) {
	string tempString;
	int tempInteger, indexLargest;
	double tempDouble;
	for(int i = 0; i < numUniversities - 1; i++) {	
		// Find index of largest unsorted element
		indexLargest = i;
		for(int j = i + 1; j < numUniversities; j++) {
			if(graduationPercentage[indexLargest] < graduationPercentage[j]) {
				indexLargest = j;
		}
	}
	// Swap data from lowest index unsorted university with largest remaining unsorted university
	tempString = universityNames[i];
	universityNames[i] = universityNames[indexLargest];
	universityNames[indexLargest] = tempString;
	tempString = states[i];
	states[i] = states[indexLargest];
	states[indexLargest] = tempString;
	tempDouble = tuition[i];
	tuition[i] = tuition[indexLargest];
	tuition[indexLargest] = tempDouble;
	tempInteger = enrollment[i];
	enrollment[i] = enrollment[indexLargest];
	enrollment[indexLargest] = tempInteger;
	tempDouble = averageRetention[i];
	averageRetention[i] = averageRetention[indexLargest];
	averageRetention[indexLargest] = tempDouble;
	tempDouble = graduationPercentage[i];
	graduationPercentage[i] = graduationPercentage[indexLargest];
	graduationPercentage[indexLargest] = tempDouble;
	}
}
