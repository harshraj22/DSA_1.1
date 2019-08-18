#include<bits/stdc++.h>
using namespace std;

int main(int argc,char** argv){
	ifstream ifn;
	ofstream ofn;
	if(argc<2){	//If no command line argument is given.
		cout<<"Enter the file name as command line argument.\n";
		return 0;
	}

	//open the asked file
	ifn.open(argv[1]);

	int type=argv[1][5]-'0',i;

	//for output in similar named file
	string final="output"+to_string(type)+".txt";
	ofn.open(final);

	//creating vector for storing numbers (size of data is not known)
	vector<int> v;

	//taking input till EOF is reached
	while(ifn>>i)
		v.push_back(i);

	//if file is not empty
	if(v.empty()==0){
		ofn<<v.size()<<"\n"<<*min_element(v.begin() , v.end())<<"\n"<<*max_element(v.begin() , v.end())<<"\n"; 
		long long int sum=accumulate(v.begin(),v.end(),0LL)
		ofn<<fixed<<setprecision(2)<<sum<<"\n"<<sum*1.00/v.size()<<endl;
	}
	// else if file is empty
	else 
		cout<<"file is empty or doesnt exist\n";

	return 0;
}