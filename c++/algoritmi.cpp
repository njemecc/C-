#include <iostream> 
#include <vector> 
#include <algorithm> 

using namespace std;

int main() { 

	int arr[10] = { 1,2,-3,4,5,6 };

	all_of(arr, arr + 6, [](int x) {return x > 0;}) ?
		cout << "Svi elementi su veci od 0" : cout << "Nisu svi elementi veci od 0" << endl; 

	//all_of vraca true ako su svi elemnti zadovoljili uslov 

	any_of(arr, arr + 6, [](int x) {return x < 0;}) ?
		cout << "Barem jedan clan niza je manji od 0" : cout << "Nijedan clan niza nije manji od 0" << endl;

	//any_of vraca true ako barem jedan element zadovoljava uslov
	cout << endl;
	int arr2[10] = { 1,2,3,4,-5,6,7,8 };
	none_of(arr2, arr2 + 10, [](int x) {return x < 0; }) ?
		cout << "Nema brojeva koji su manji od 0" : cout << "Postoji barem 1 broj manji od 0" << endl;
	// none_of vraca true ako nijedan element ne zadovoljava uslov 

	vector<int> vektor = { 2,1,5,3,8,4 }; 
	partition(vektor.begin(), vektor.end(), [](int x) {return x % 2 == 0;});



	system("pause");
	return 0;
}