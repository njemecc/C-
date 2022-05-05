#include <iostream> 
#include <string> 
#include <vector>  
#include <algorithm> 
#include <functional>
#include <iterator>
using namespace std;

class Student{
	
	string ime, prezime; 
	float prosek; 
protected: 
	string brojIndeksa; 

public: 
	Student(string ime, string prezime, string brojIndeksa, float prosek = 6.5) {
	
		this->ime = ime; 
		this->prezime = prezime; 
		this->brojIndeksa = brojIndeksa; 
		this->prosek = prosek;
	
	} 

	virtual bool proveriBrojIndeksa() const = 0;

	friend bool operator <(const Student& s1, const Student& s2) {
		return s1.prosek < s2.prosek;
	
	}

	friend ostream& operator << (ostream& out, const Student& s) {
		return out << s.ime << " " << s.prezime << " " << s.brojIndeksa << " " << s.prosek << endl;

	} 
};

class StudentInformatike : public Student {
public: 
	using Student::Student;
	

	bool proveriBrojIndeksa() const override {
		int n = brojIndeksa.length(); 

		if (n < 10) return false; 

		for (int i = 0; i < n; i++) {
			if (isalpha(brojIndeksa[i])) return false;
		}
		return true;
	}
}; 

class StudentElektrotehnike : public Student {

public: 
	using Student::Student; 

	bool proveriBrojIndeksa() const override {
		int n = brojIndeksa.length();

		if (n < 10) return false;

		for (int i = 0; i < n; i++) {
			if (isalpha(brojIndeksa[i])) return false;
		}
		return true;
	}
};

int main() {

	StudentInformatike si1("ime1", "prezime1", "2020123456", 8.90); 
	StudentInformatike si2("ime 2", "prezime 2", "2019345678", 9.20); 

	StudentElektrotehnike se1("ime3", "prezime 3", "2015123456", 9.50); 
	StudentElektrotehnike se2("ime4", "prezime 4", "2014200456", 9.70); 

	vector <Student*> studenti;

	studenti.push_back(&si1);
	studenti.push_back(&si2);
	studenti.push_back(&se1);
	studenti.push_back(&se2);

	Student* najslabijiProsek = nullptr;

	for (auto s : studenti) {
		if (s->proveriBrojIndeksa())
			if (najslabijiProsek == nullptr || *s < *najslabijiProsek)
				najslabijiProsek = s;
	} 

	if (najslabijiProsek == nullptr)
		cout << "Svi studenti su sa nevalidnim brojem indeksa" << endl;
	else
		cout << "Student sa najslabijim prosekom je " << *najslabijiProsek << endl; 
	//Kraj zadataka Student

	/*
		Sortiranje 
	
	vector<int> niz1{ 7,9,11,13,15 }; 
	vector<int> niz2{ 8,10,12,14,6 };

	stable_sort(begin(niz1), end(niz1), greater<>());
	stable_sort(begin(niz2), end(niz2), greater<>());


	vector<int> niz3(niz1.size() + niz2.size() + 10);

	auto itr = merge(begin(niz1), end(niz1), begin(niz2), end(niz2), begin(niz3), greater<>());*/


	system("pause");
	return 0;

}