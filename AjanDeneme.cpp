#include<iostream>
#include<string>
#include<fstream>
#include<vector>
using namespace std;


class Agents
{
	unique_ptr <string> name;
	unique_ptr <int> health;
public:
	Agents(string nm, int hp)
	{
		name = make_unique<string>(nm);
		health = make_unique<int>(hp);
	}
	virtual ~Agents(){}

	virtual void UseAbility() = 0;
	friend ostream& operator<<(ostream& os, const Agents& other);
	
};

ostream& operator<<(ostream& os, const Agents& other)
{
	os << *other.name << " Ajanin Cani: " << *other.health << "\n";
	return os;
}

class yoru :public Agents
{
public:
	yoru(string nm1, int hp1) :Agents(nm1, hp1) {}
	void UseAbility() override
	{
		cout << "Klon Gonderildi...\n";
	}
};

class omen :public Agents
{
public:
	omen(string nm1, int hp1) :Agents(nm1, hp1) {}
	void UseAbility() override
	{
		cout << "Karanlik Ortu Yollaniyor...\n";
	}
};

class clove :public Agents
{
public:
	clove(string nm1, int hp1) :Agents(nm1, hp1) {}
	void UseAbility() override
	{
		cout << "Katakulli Aktif...\n";
	}
};



int main()
{
	unique_ptr<yoru> Yoru = make_unique<yoru>("Yoru", 100);
	unique_ptr<omen> Omen = make_unique<omen>("Omen", 75);
	unique_ptr<clove> Clove = make_unique<clove>("Clove", 55);
	

	cout << "==========YETENEKLER KULLANILIYOR=========\n";
	 Yoru->UseAbility();
	 Omen->UseAbility();
	 Clove->UseAbility();
	 cout << "\n==========YETENEKLER KULLANILDI==========\n";

	 cout << "\n==========DOSYA OLUSTURULUYOR==========\n";
	 ofstream dosyam("SAVE.txt"/*ios:.app*/);// eger gercek bir save dosyasý olsaydý ios::app kullanmalýydýk cunku dosyanýn onceki halini deðiþtirmeden devamýna yazmayý saðlýyor.
	 dosyam << *Yoru << *Omen << *Clove;
	 dosyam.close();

	 cout << "\n==========DOSYA YAZILIYOR==========\n";

	 ifstream dosya("SAVE.txt");
	 string line;
	 while (getline(dosya, line))
	 {
		 cout << line << "\n";
	 }

	 dosya.close();
	 
	 return 0;
}




















