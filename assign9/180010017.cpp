// Acknowledgements to StackOverFlow for doubts in usage of class/oops

#include<bits/stdc++.h>
using namespace std;

// Clss based implementation

class HashTable{
	private:
		// an array of list that stores the annagrams (list of strings)
		// each annagram is hashed to same hash value, and thus stored in same linked list
		vector<list<string> > table;
		int numOfSlots;

		void link(string s, int hashedValue){
			// takes hashvalue and string as parameters and inserts at the correct position 
			// insert at front as said in the question
			table[hashedValue].push_front(s);
		}

		int CalculateHash(string s){
			// given a string, calculate its hash value, and insert at the desired location, in the hash table
			long long int sum = 0;

			// calculate the sum of ASCII values of all characters in the string
			for(auto character:s)
				sum += character;

			// Use the hash formula as provided in the problem statement
			int hashedValue = sum % numOfSlots;

			return hashedValue;
		}

	public:
		HashTable(int numberOfSlots): table(numberOfSlots+1),numOfSlots(numberOfSlots){
			// do nothing, used list initialisation
		}

		void insert(string s){
			// calculate hash value of the given string
			int hashedValue = CalculateHash(s);

			// add the string to its corresponding linked list
			link(s, hashedValue);
		}

		void print(string InputFile, string OutputFile){
			ifstream in(InputFile);	
			ofstream out(OutputFile);

			string curWord;
			while(in >> curWord){
				// calculate hash value of current word
				int hashedValue = CalculateHash(curWord);

				sort(curWord.begin(), curWord.end());

				// for each word that hashed to same hash value as that of curent word
				for(auto word:table[hashedValue]){
					string WordToBeInserted = word;
					sort(word.begin(), word.end());

					// comparision using sorting is important as two words which are not annagrams, can hash to same hash value 
					if(curWord == word)
						out << WordToBeInserted << ' ';
				}

				// after each annagram of current queried word is printed (separated with a space), end the line
				out << '\n';
			}

			in.close();
			out.close();
		}
};

int main(int argc, char**argv){

	ifstream FileInput(argv[1]);
	int numOfSlots = stoi(argv[2]);

	HashTable encode(numOfSlots);

	// take input
	string word;

	while(FileInput >> word)
		encode.insert(word);	

	FileInput.close();

	encode.print(argv[3], "anagrams.txt");

	return 0;	
}