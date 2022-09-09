#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using std::sort;
using std::pair;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::make_pair;
using std::unordered_map;

bool acceptedChars(char c){
	return isalpha(c);// or isdigit(c);
}

unordered_map<char,int> fileParsing(const string& fileName){
	unordered_map<char,int> histogram;
	std::ifstream infile(fileName);
	char c;

	while(infile.get(c)){
		if(acceptedChars(c)){
			if(isalpha(c)) c = tolower(c);
			histogram[c]++;
		}
	}
	return histogram;
}

class CharHistogram {

	public:
		CharHistogram(const string& fileName){
			fileName_ = fileName;
			unordered_map<char,int> inputChars = fileParsing(fileName);
			histo_ = buildHisto(inputChars);
		}
		//Function to print out on STDOUT histogram.
		void publishHisto(){
			cout << fileName_ << endl;

			int size = histo_.size();
			for(int i = 0; i < size; i++){
				cout << histo_[i].second << " " << histo_[i].first << endl;
			}
		}
	private:
		string fileName_;
		vector<pair<int,char>> histo_;

		vector<pair<int,char>> buildHisto(unordered_map<char,int>& inputChars){
			unordered_map<char,int>::iterator it;
			for(it = inputChars.begin(); it != inputChars.end(); ++it){
				histo_.push_back(make_pair(it->second,it->first));
			}
			sort(histo_.rbegin(),histo_.rend());
			return histo_;
		}
};

int main(int argc, char *argv[]){
	for(int i = 1; i < argc; i++){
		CharHistogram cHisto(argv[i]);
		cHisto.publishHisto();
		cout << endl;
	}

	return 0;
}
