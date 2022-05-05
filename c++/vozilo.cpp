#include <iostream>
#include <string> 
#include <vector>  
#include <algorithm> 
#include <fstream>

using namespace std;

class Vozilo {
	string marka, model; 
	float snagaMotora; 
protected: 
	string brojSasije;
public: 
	Vozilo(string marka, string model, string brojSasije, float snagaMotora = 150.0) {
		this->marka = marka; 
		this->model = model; 
		this->brojSasije = brojSasije; 
		this->snagaMotora = snagaMotora;
	} 
	virtual bool proveriBrojSasije() const = 0;
	friend ostream& operator <<(ostream& out, const Vozilo& v) {
		return out << v.marka << " " << v.model << " " << v.brojSasije << " " << v.snagaMotora << endl;
	
	} 

	float getSnagaMotora() { return snagaMotora; }

}; 

class Dvotockas : public Vozilo {

public: 
	using Vozilo::Vozilo; 
	bool proveriBrojSasije() const override {
	
		int n = brojSasije.length(); 

		if (n < 4) return false; 

		if (brojSasije[0] != brojSasije[n - 1] || brojSasije[1] != brojSasije[n - 2]) return false;

		if (any_of(brojSasije.begin(), brojSasije.end(), [](char c)
		{return !islower(c) && !isdigit(c); })) return false; 

		return true;
	}

}; 

class Cetvorotockas : public Vozilo {
public:
	using Vozilo::Vozilo;
	bool proveriBrojSasije() const override {
	
		int n = brojSasije.length(); 

		if (n < 4) return false; 

		if (brojSasije[0] != brojSasije[n - 1] || brojSasije[1] != brojSasije[n - 2]) return false;

		if (!none_of(brojSasije.begin(), brojSasije.end(), [](char c) 
			{return !isupper(c) && !isdigit(c); })) return false;

		return true;
	
	}
};


int main() {  

	ifstream in("input.txt"); 
	ofstream out("output.txt");

	if (!in.is_open()) return EXIT_FAILURE;

	vector<Vozilo*> vozila;

	while (!in.eof()) {
		char oznaka; 
		string marka, model, brojSasije; 
		float snagaMotora;

		in >> oznaka >> marka >> model >> brojSasije >> snagaMotora;

		Vozilo* vozilo;
		if (oznaka == 'D') {
			if (snagaMotora == -1) vozilo = new Dvotockas(marka, model, brojSasije); 
			else vozilo = new Dvotockas(marka, model, brojSasije, snagaMotora);
		
		}
		else {
		
			if (snagaMotora == -1) vozilo = new Cetvorotockas(marka, model, brojSasije); 
			else vozilo = new Cetvorotockas(marka, model, brojSasije, snagaMotora);
		} 

		vozila.push_back(vozilo);
	
	}
	sort(vozila.begin(), vozila.end(), [](Vozilo* v1, Vozilo* v2) {return v1->getSnagaMotora() > v2->getSnagaMotora();});
	auto newEnd = remove_if(vozila.begin(), vozila.end(), [](Vozilo* v) {return v->proveriBrojSasije();}); 
	out << **max_element(vozila.begin(), newEnd, [](Vozilo* v1, Vozilo* v2) {return v1->getSnagaMotora() > v2->getSnagaMotora();}); 



	


	system("pause");
	return 0;
}