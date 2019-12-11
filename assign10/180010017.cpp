/*
	Acknowledgements :
		My Acknowledgements for this assignment goes to GeeksForGeeks for 'std::tuple' and Introduction To Algorithms (CLRS) for Extended Euclidean Theorem
*/

#include<bits/stdc++.h>
using namespace std;

#define ll long long int

/*
	Extended Euclidean Theorem :
		Given two non negative integers, find their GCD and the coeeficients, in their linear combination such that the linear combination results in gcd. 

		i.e. given non negative a, b find x, y such that ax + by = gcd(x, y)

		complexity = O(log(|b|) + log(|a|)) : linear in terms of number of  bits required to represent the inputs.

*/


// Using class based solution to understand it better
class ExtendedEuclid{
	private:
	public:
		// tuple of gcd, x, y for ax + by, where a, b are given
		tuple<int, int, int> extend(int a=0, int b=0){
			
			// assert(a >= 0 && b >= 0);
			if(b==0){
				// if b is 0, gcd is a, and coefficients are x=1 and y=0
				return make_tuple(a, 1, 0);
			}
			int gcd, x_, y_;

			// else recursively calculate the solution and update the final result
			tie(gcd, x_, y_) = this->extend(b, a%b);

			// update the result of last formula
			return make_tuple(gcd, y_, x_ - (a/b)*y_);
		}
};

int main(int argc, char**argv){

	ExtendedEuclid newObject;
	int gcd, x, y, a, b;

	a = stoi(argv[1]);
	b = stoi(argv[2]);

	tie(gcd, x, y) = newObject.extend(a, b);
	cout << gcd << " " << x << " " << y << endl;

	return 0;
}