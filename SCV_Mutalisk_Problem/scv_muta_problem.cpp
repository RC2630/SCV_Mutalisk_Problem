#include <iostream>
#include <vector>
#include <cassert>
#include <numeric>
#include <algorithm>

using namespace std;

// finds the indexes in the list of SCV's to attack, returned as [first bounce, second bounce, third bounce]
// side effect: may change the order of the elements in the list, but that probably won't cause any problems
vector<int> findBounceIndexes(vector<int>& v) {
	sort(v.begin(), v.end(), [] (int a, int b) {
		return a > b;
	});
	// the 1st bounce index is always the frontmost element's index (which is 0)
	vector<int> bounces = {0, -1, -1};
	// find the 3rd bounce index (probably the last index, but not if it has element value of 0)
	int bounce3 = v.size() - 1;
	while (v.at(bounce3) == 0 && bounce3 >= 3) {
		bounce3--;
	}
	bounces.at(2) = bounce3;
	// find the 2nd bounce index
	int bounce2 = 1;
	while (bounce2 < bounce3 - 1 && v.at(bounce2) >= 9) {
		bounce2++;
	}
	bounces.at(1) = bounce2;
	return bounces;
}

// subtracts takeAway from v.at(index), but if the result makes v.at(index) negative, then sets v.at(index) to 0
void subtract(vector<int>& v, int index, int takeAway) {
	if (v.at(index) - takeAway < 0) {
		v.at(index) = 0;
	} else {
		v.at(index) -= takeAway;
	}
}

int mutalistAttack(const vector<int>& scvs) {
	int counter = 0;
	vector<int> curr = scvs;
	while (curr.size() < 3) {
		curr.push_back(0);
	}
	while (accumulate(curr.begin(), curr.end(), 0) > 0) {
		vector<int> bounceIndexes = findBounceIndexes(curr);
		subtract(curr, bounceIndexes.at(0), 9), subtract(curr, bounceIndexes.at(1), 3), subtract(curr, bounceIndexes.at(2), 1);
		counter++;
	}
	return counter;
}

void customAssert(int a, int b, int testNumber) {
	if (a != b) {
		cout << "\n\ntest #" << testNumber << " failed! expected: " << b << ", actual: " << a << ", error: ";
		assert(false && "algorithm produced the wrong answer!");
	}
}

void testMutaliskAttack() {
	vector<vector<int>> inputs = {
		/* 1 */ {19, 4, 3},
		/* 2 */ {60, 60, 60, 60, 60, 60, 60, 60, 60},
		/* 3 */ {54, 18, 6},
		/* 4 */ {19, 9, 3, 3, 1},
		/* 5 */ {27, 6, 3, 1, 1, 1},
		/* 6 */ {9},
		/* 7 */ {24},
		/* 8 */ {17, 8},
		/* 9 */ {55, 23}
	};
	vector<int> outputs = {3, 42, 6, 3, 3, 1, 3, 3, 7};
	for (int i = 0; i < inputs.size(); i++) {
		customAssert(mutalistAttack(inputs[i]), outputs[i], i + 1);
		cout << "\n" << (i + 1) << " tests have passed!";
	}
	cout << "\n\nall tests pass!\n";
}

int main() {
	testMutaliskAttack();
}