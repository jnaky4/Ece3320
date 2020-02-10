#include <iostream>
#include <cstdlib>

using namespace std;

main(){
	
	int guess;
	int run = 1;
	int rangen = rand() % 10 + 1;
	while(run == 1){
		cout << "guess a values from 1-10\n";
		cin >> guess;
		if(guess == rangen){
			cout << "correct, game over.\n:";
			run = 0;
		}
		else if (guess < rangen){
			cout << "too low\n" ;
		}
		else {
			cout << "too high\n" ;
		}
		

	}
	return 0;
}
