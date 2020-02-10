#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

main(){
	
	int value1;
	int value2;
	char opera;
	
	
	cout << "give me the first value\n";
	cin >> value1;
	cout << "give me the operator\n";
	cin >> opera;
	cout << "give me second value\n";
	cin >> value2;
	
	switch(opera){
		case '+' :
			cout << value1 << " + " << value2 << " = " << (value1 + value2) << "\n";
			break;
		case '-' : 
			cout << value1 << " - " << value2 << " = " << (value1 - value2) << "\n";
			break;
		case '*' : 
			cout << value1 << " * " << value2 << " = " << (value1 * value2) << "\n";
			break;
		case '/' : 
			cout << value1 << " / " << value2 << " = " << (value1 / value2) << "\n";
			break;
		default :
			cout << opera << " is an invalid input\n";
			break;
	}
	return 0;
}
