#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <vector>  
#include <sstream>
#include "String.h"
#include "Expression.h"
#include "Scalar.h"
#include <map>


using namespace std;
using namespace Freeky;

vector<String> findConjuctions(String line, String delimiter = "=>") {
	vector<String> results;
	size_t pos = 0;
	string s = line.toString(); // edit this

	while ((pos = s.find(delimiter.toString())) != std::string::npos) {
		results.push_back(String(s.substr(0, pos)));
		s.erase(0, pos + delimiter.length());
	}
	return results;
}

int main() {

	String str;
	str.read("Here tell me?");
	//map<string, int> m;
	//m["test"] = 1;
	//cout << m["test"];
	////str.print();
	//Expression exps(str);
	//String ss = exps[20];
	//ss.print();

	// ADD ALL DATA TYPES LIST; IN MEMENTO
	// FROM THGE MOMENT A VARIABLE IS DERFINED USE THE BEST AND MIMUM MEMORY NEEDED TO SAVE THE VALUE
	// WHEN THE NUMBER IS LARGER THAN THE CURRENT DATA TYPE (FOR EX: SHORT INT VS INT), THEN SHIFT THE VARTIABLE TO LARGER SCOPE

	//String x = "test";
	//cout << sizeof("testddd")<<endl;
	//map<String, int> y;
	//y[x] = 10;
	//cout << y[x];
	//Scalar y1 = 123;
	vector<String> sides = findConjuctions(str);
	Scalar s = "0";

	for (String side: sides) {
		vector<String> params = findConjuctions(side, " ");
		String operation = params[0];
		if (operation == "+") {
			for (auto i = 1; i < params.size(); i++) {
				Scalar x = params[i].toString();
				cout << s + x;
			}
		}

		break;
	}
	cout << s;
	Scalar x = "12343646837837468343467837746877824234", y = "12465464646574687879741479878978945548783";
	cout << endl << x + y;
	//cout << "answer s= " << x + y ;
	return 0;
}
