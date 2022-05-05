#include <iostream> 
#include <string> 
#include <vector> 
#include <algorithm> 
#include <fstream> 

using namespace std;
class Racunar {

	string brend; 
	float brzinaCpu;  
	int memorija; 
protected: 
	string serijskiBroj; 
public: 

	Racunar(string brend, string serijskiBroj, float brzinaCpu, int memorija = 16) {
		this->brend = brend; 
		this->serijskiBroj = serijskiBroj; 
		this->brzinaCpu = brzinaCpu; 
		this->memorija = memorija;
	}

	virtual bool proveriSerijskiBroj() const = 0; 

	friend ostream& operator <<(ostream& out, Racunar& r) {
		return out << r.brend << " " << r.serijskiBroj << " " << r.brzinaCpu << " " << r.memorija << endl;
	}

	float getBrzinaCpu() { return brzinaCpu; }

}; 

class Desktop : public Racunar {
public: 
	using Racunar::Racunar;

	bool proveriSerijskiBroj() const override {
		
		string s = this->serijskiBroj; 
		if (s.length() != 10) return false;

		if (all_of(s.begin(), s.end(), [](char c) {return !isupper(c) && !isdigit(c); })) return false;
		
		return true;
	}


}; 

class Laptop : public Racunar { 
public: 
	using Racunar::Racunar;

	bool proveriSerijskiBroj() const override {
		string s = this->serijskiBroj;

		if (s.length() != 8) return false; 
		if (!none_of(s.begin(), s.end(), [](char c) 
		{return !islower(c) && !isdigit(c); })) return false;

		return true;
	}

};



int main() {

	ifstream in("input.txt"); 
	ofstream out("output.txt"); 

	if (!in.is_open()) return EXIT_FAILURE;  

	vector<Racunar*> racunari;

	while (!in.eof()) {
		char oznaka; 
		string brend, serijskiBroj; 
		float brzinaCpu; 
		int memorija; 

		in >> oznaka >> brend >> serijskiBroj >> brzinaCpu >> memorija;

		Racunar* racunar;
		if (oznaka == 'L') {
			if (memorija == -1) racunar = new Laptop(brend, serijskiBroj, brzinaCpu);
			else racunar = new Laptop(brend, serijskiBroj, brzinaCpu, memorija);
		
		}
		else {
			if (memorija == -1) racunar = new Desktop(brend, serijskiBroj, brzinaCpu); 
			else racunar = new Desktop(brend, serijskiBroj, brzinaCpu, memorija);
			
		} 
		
		racunari.push_back(racunar);
	
	} 
	sort(racunari.begin(), racunari.end(), [](Racunar* r1, Racunar* r2) {return r1->getBrzinaCpu() > r2->getBrzinaCpu(); });
	auto newEnd = remove_if(racunari.begin(), racunari.end(), [](Racunar* r) {return !r->proveriSerijskiBroj();});
	out << **min_element(racunari.begin(), newEnd, [](Racunar* r1, Racunar* r2) {return r1->getBrzinaCpu() < r2->getBrzinaCpu();});


	return 0;
}