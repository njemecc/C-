#include <iostream>
#include <string> 
#include <vector> 

using namespace std; 

class Kontejner {
	string ime; 

public: 
	Kontejner(string ime) {
		this->ime = ime;
	
	} 

	string dohvatiIme() {
		return ime;
	}
	virtual long dohvatiVelicinu() const = 0;
	// [film] => 6854654B
	friend ostream& operator << (ostream& out, Kontejner& k) {
		return out << "[" << k.ime << "] =>" << k.dohvatiVelicinu() << "B" << endl;
		
	}

}; 

class Fajl : public Kontejner {
	long velicina;
public: 
	Fajl(string ime, long velicina) : Kontejner(ime) {
		this->velicina = velicina;
	} 
	long dohvatiVelicinu() const override {
		return velicina;
	} 

}; 

class Folder : public Kontejner {
	vector<Kontejner*> kontejneri; 
public: 
	Kontejner::Kontejner; 

	Folder& operator+(Kontejner* k) {
		kontejneri.push_back(k); 
		return *this;
	
	}
	Kontejner* operator[](unsigned i) {
		if (i < 0 || i >= kontejneri.size()) return nullptr;
		return kontejneri[i];
	} 

	long dohvatiVelicinu() const override {
		long ukupnaVelicina = 0; 

		for (auto kont : kontejneri) {
			ukupnaVelicina += kont->dohvatiVelicinu();
		
		} 

		return ukupnaVelicina;
	
	}


};


int main() { 

	Folder root("root"); 
	Folder folder1("folder12"); 
	Folder folder12("folder12");
	Fajl fajl121("fajl121", 1560); 
	Fajl fajl122("fajl122", 20567); 
	Folder folder2("folder2"); 

	root + &(folder1 + &(folder12 + &fajl121 + &fajl122)) + &folder2; 
	cout << root << endl;

	system("pause");
	return 0;
}