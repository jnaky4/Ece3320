#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

main(){
	
	int cost;
	int sellP;
	
	cout << "give me the cost\n";
	cin >> cost;
	cout << "give me the selling prince\n";
	cin >> sellP;

	if(cost > sellP){
		cout << "you're wasting your money\n:";
		cout << "you're losing " << (cost - sellP) << " in Dong(vietnamese currency)\n";
	}
	else if (cost < sellP){
		cout << "you've made a profit\n" ;
		cout << "your gaining " << (sellP - cost) << " in pounds of gold\n";
	}
	else {
		cout << "you broke even\n" ;
	}
	
	return 0;
}
