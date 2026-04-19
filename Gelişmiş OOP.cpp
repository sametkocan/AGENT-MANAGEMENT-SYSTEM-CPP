#include<iostream>
#include<string>
#include<fstream>
#include<vector>
using namespace std;


class Agents
{
	string* name{};
	int* health{};

public:
	Agents(string nm, int _h)
	{
		name = new string(nm);
		health = new int(_h);
	}
	virtual ~Agents()
	{
		delete name;
		delete health;
		name = nullptr;
		health = nullptr;
	}
	Agents(const Agents& other)
	{
		name = new string(*other.name);
		health = new int (*other.health);
	}
	Agents& operator=(const Agents& other)
	{
		if (this == &other)
		{
			return *this;
		}

		delete name;
		delete health;
		name = nullptr;
		health = nullptr;

		name = new string(*other.name);
		health = new int(*other.health);

		return *this;
	}


	friend ostream& operator<<(ostream& os, const Agents& other);

	virtual void UseAbility() = 0;

};
	
ostream& operator<<(ostream& os, const Agents& other)
{
	os <<"Ajan Ismi: " << *other.name << "  Cani:  " << *other.health;
	return os;

}


class Yoru :public Agents
{
public:
	Yoru(string nm, int _h) :Agents(nm, _h) {}

	void UseAbility() override
	{
		cout << "Klon Gonderildi...";
	}
};

class Omen : public Agents
{
public:
	Omen(string nm, int _h) :Agents(nm, _h) {}
	void UseAbility() override
	{
		cout << "Sis Gonderildi...";
	}
};

class Clove :public Agents
{
public:
	Clove(string nm, int _h) :Agents(nm, _h) {}
	void UseAbility()override
	{
		cout << "Katakulli Aktif...";
	}
};

int main()
{ 
	vector<Agents*>ajanlar;
	ajanlar.push_back(new Yoru("Yoru", 100));
	ajanlar.push_back(new Omen("Omen", 80));
	ajanlar.push_back(new Clove("Clove", 60));

	vector<Agents*>::iterator it;
	ofstream dosya("Save.txt", ios::app);

	for (it = ajanlar.begin();it != ajanlar.end(); ++it)
	{
		dosya << **it << "\n";
	}

	for (it = ajanlar.begin(); it != ajanlar.end(); ++it)
	{
		delete* it;
	}

	ajanlar.clear();

	dosya.close();


	return 0;
}






