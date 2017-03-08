#include <iostream>

using namespace std;
class Stirlitz{};
int main(int argc, char *argv[1]){
	Stirlitz dkod;
	if(argc!=2){
			cout << "At the command prompt, you must enter the file name." << endl;
		return 1;
	}
	dkod.transcoder(argv[1]);
	return 0;
}
