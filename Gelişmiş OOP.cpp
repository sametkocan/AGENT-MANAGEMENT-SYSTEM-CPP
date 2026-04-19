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








/*	POLYMORPHÝSM VÝRTUAL TAMAMEN SOYUTLAÞTIRMA OVERRÝDE VECTOR ÝLE YAZDIRMA KONULARI HAKKINDA ÖRNEK.
* 
class Agents
{
public:
	virtual ~Agents() {}	
	virtual void UseAbility() = 0;	//tamamen soyut yaptýk.Cunku Gercek Dunyada Ajan diye bi nesne olamaz ya yoru olursun ya omen vsvs... 
	
};


class Yoru :public Agents
{
public:
	void UseAbility() override
	{
		cout << "Yanilsama Gonderildi.\n";
	}
};

class Omen :public Agents
{
public:
	void UseAbility() override
	{
		cout << "Karanlik Ortu Birakildi.\n";
	}
};

class Clove :public Agents
{
public:
	void UseAbility() override
	{
		cout << "Katakulli Aktif!\n";
	}
};

int main()
{
	Agents* yoru{ new Yoru() };
	Agents* clove  { new Clove() };
	Agents* omen{ new Omen() };
	// Agents* test = new Agents(); parent class a desctructor koyduk bu nedenle bu class a ait bi nesne olusturamazsin
	// ayrýca fonk u da 0 a eþitledik bu sayede her child class bu fonk un gövdesini mecbur yazmak zorunda kaldý bu da hata ihtimalini azalttý.

	yoru->UseAbility();
	clove->UseAbility();
	omen->UseAbility();

	vector<Agents*> characters { yoru,clove,omen };
	
	cout<<"\n";
	for (Agents* i : characters)
	{
		i->UseAbility();
	}

	delete yoru;
	delete clove;
	delete omen;
	yoru = nullptr;
	clove = nullptr;
	omen = nullptr;

	return 0;
}
*/






/*		COPY CONSTRUCTOR ÝLE YORU NESNEMÝZÝ OMEN NESNEMÝZE ATADIK AMA FARKLI ADRESLER KULLANMAK GEREKÝYORDU YOKSA BÝRÝNÝ DELETE EDÝNCE DÝÐERÝ AYNI ADRESÝ
* GÖSTERDÝÐÝ ÝÇÝN PROGRAM CRASH YERDÝ BU NEDENLE YORUNUN TUM OZELLÝKLERÝNÝ OMEN ÝCÝN YENÝ BÝR ADRES ACIP ORAYA ATADIK
class Agents
{
	int* health;
public:

	Agents(int h)
	{
		health = new int{ h };
	}

	Agents(const Agents& other)
	{
		health = new int;
		*health = *(other.health);

		cout << "Copy Constructor Basarili...\n";
	}

	~Agents()
	{
		delete health;
		health = nullptr;
	}
};

int main()
{
	Agents Yoru(80);
	Agents Omen = Yoru;
}
*/







/*		ÜÇLEME KURALI(RULE OF THREE) DESTRUCTOR COPYCONSTRUCTOR VE copy assignment operator=  3 ünden birisi varsa diðer ikiside olacak.
* 
* "Üçlemeci Kuralý" (Rule of Three) tek bir cümleyle þudur: "Eðer sýnýfta new ile açtýðýn bir pointer varsa, þu 3 fonksiyonu yazmazsan programýn patlar."

Nedenleri ise aþýrý kýsa þu þekilde:

1) Destructor (Yýkýcý): new ile aldýðýn yeri delete ile geri vermezsen bellek sýzýntýsý (memory leak) olur, RAM dolar.

2) Copy Constructor (Kopyalama Yapýcý): Eðer yazmazsan, A = B dediðinde ikisi de ayný adrese bakar. Biri ölürse diðeri çöpü gösterir (Dangling Pointer).

3) Assignment Operator (Atama Operatörü): Mevcut bir nesneyi diðerine eþitlerken derin kopyalama (içindeki deðeri kopyalama) yapman gerekir ki 
pointer'lar birbirine karýþmasýn.

Özet: Bellek sýzýntýsýný ve programýn "çat" diye kapanmasýný (segmentation fault) engellemek için bu üçü birbirinden ayrýlamaz bir takýmdýr.

class Agents
{
	int* health;
public:
	~Agents()
	{
		delete health;
		health = nullptr;
	}
	Agents(int h)
	{
		health = new int (h);
	}
	Agents(const Agents& other)
	{
		health = new int;
		*health = *other.health;
	}

	Agents& operator=(const Agents& other)
	{
		if (this == &other)	//eðer yanlýslýkla n1=n1 yapsaydýk ve bunu koymasaydýk program once adresini siler sonra yeni adresini almaya calýsýrdý ama elinde biþey kalmazdý
		{
			return *this;
		}

		delete health;//eski adresi sildik

		health = new int (*other.health); //sonra yeni adres olusturup deðeri kopyaladýk

		return *this;	//guncellenmiþ nesneyi döndür.

	}

	void print()
	{
		cout << *health << endl;
	}
};


int main()
{
	Agents yoru(80);
	Agents omen(20);
	yoru.print();
	omen.print();
	omen = yoru;  
	yoru.print();
	omen.print();
	
}
*/







/*			OPERATOR OVERLOADÝNG + ORNEGÝ (-,*,/ DE MANTIK ZATEN AYNI).

class Agents
{
	int* health = new int{};
public:
	 Agents(int _h) { *health = _h; }
	 ~Agents()
	 {
		 delete health;
		 health = nullptr;
	 }

	 Agents operator=(const Agents& other)
	 {
		 if (*(this->health) == *(other.health))
		 {
			 return *this;
		 }
		 *(this->health) = *(other.health);
		 return *this;
	 }

	Agents operator+(const Agents& other)const		//AJAN=AJAN+AJAN YAPMAK ÝÇÝN
	{
		return Agents(*health + *other.health);	//tek satýrda birden fazla iþlem hýz için
	}

	Agents operator+(int n)const	//AJAN=AJAN+SAYI ÝÇÝN
	{
		return Agents(*health + n);
	}

	friend Agents operator+(int, const Agents&);	//AJAN=SAYI+AJAN ÝÇÝN ZORUNLU!!!

	int gethealth()
	{
		return *health;
	}

};

Agents operator+(int n, const Agents& other)
{
	return Agents(n + *other.health);	
}


int main()
{
	Agents yoru(70), omen(50), clove(80);
	int MaxCan;

	cout << "====ISLEMLERDEN ONCE====\n";
	cout << "Yorunun Cani: " << yoru.gethealth();
	cout << "\nOmenin Cani: " << omen.gethealth();
	cout << "\nClove un Cani: " << clove.gethealth();
	cout << "\nMax Can: " << (yoru + omen + clove).gethealth();	//max can 200

	cout << "\n\n";
	cout << "====ISLEMLERDEN SONRA====";

	yoru = clove + omen;	//yoru 130 can oldu
	clove = 15 + omen;		//clove 65 can oldu
	omen = yoru + 45;		//omen 175 can oldu
	MaxCan = (yoru + clove+omen).gethealth();		//maxcan 375

	cout << "\nYorunun Cani: " << yoru.gethealth();
	cout << "\nOmenin Cani: " << omen.gethealth();
	cout << "\nClove un Cani: " << clove.gethealth();
	cout << "\nMax Can: " << MaxCan << endl;

	return 0;
}
*/






/*+=,-= operatorleri kullanýmý(*=,/= mantýgý ayný)NORMALDEN FARKI BURDA DÝREKT SOLDAKÝ NESNENÝN AYNISIYLA ÝÞLEM YAPIYORUZ CUNKU SONUC  AYNI NESNEYE YAZILACAK.
	AYRICA return *this YAPIYORUZ NORMALDEN BÝR FARKI DA BUDUR.
class Agents
{
	int* health = new int{};
public:
	Agents(int _h = 0) { *health = _h; }
	~Agents() { delete health; health = nullptr; }

	Agents& operator+=(const Agents& other)		//TEK FARK RETURN TYPE DA & KULLANMAK !!this dondurmek de farklardandýr
	{
		*this->health += *other.health;
		return *this;
	}

	Agents& operator+=(int a)
	{
		*this->health += a;
		return *this;
	}

	Agents& operator-=(const Agents& other)
	{
		*this->health -= *other.health;
		return *this;
	}

	Agents& operator-=(int a)
	{
		*this->health -= a;
		return *this;
	}

	Agents operator+(const Agents& other)
	{
		return Agents(*this->health + *other.health);
	}

	int getHealth()
	{
		return *health;
	}

};


int main()
{
	Agents yoru(80), omen(40), clove(60);

	cout << "====HESAPLAMADAN ONCE====\n";
	cout << "Yorunun Cani: " << yoru.getHealth() << "\n";
	cout << "Omenin Cani: " << omen.getHealth() << "\n";
	cout << "Clove'un Cani: " << clove.getHealth() << "\n";

	yoru += omen;	//yoru 120 oldu
	omen += 15;		//omen 55 oldu
	clove += yoru + omen;		//clove 235 oldu
	cout << "\n====HESAPLAMADAN SONRA====\n";
	cout << "Yorunun Cani: " << yoru.getHealth() << "\n";
	cout << "Omenin Cani: " << omen.getHealth() << "\n";
	cout << "Clove'un Cani: " << clove.getHealth() << "\n";
	
	return 0;
}
*/







/*	KARÞILAÞTIRMA OPERATORLERÝ BOOL DONDURUR UNUTMA AYRICA 3 LEMECÝ KURALINI DA UNUTMA DESTRUCTOR,COPYCONSTRUCTOR,ASSÝGNMENT OPERATOR OVERLOADÝNG...

class Agents
{
	int* health = new int{};
public:
	Agents(int _h = 0) { *health = _h; }
	~Agents() { delete health; health = nullptr; }

	Agents(const Agents& other)
	{
		health = new int{};

		*health = *other.health;
	}

	Agents& operator=(const Agents& other)
	{
		if(this==&other)
		{
			return *this;
		}

		*health = *other.health;
		return *this;

	}

	// 2 nesne karþýlaþtýrmasý yaparken 

	bool operator==(const Agents& other)	
	{
		return *(this->health) == *(other.health);
	}

	bool operator<(const Agents& other)
	{
		return *(this->health) <*(other.health);
	}


	bool operator<=(const Agents& other)
	{
		return *(this->health) <=*(other.health);
	}

	bool operator!=(const Agents& other)
	{
		return *(this->health) != *(other.health);
	}

	//nesne ve sayý karþýlaþtýrmasý yaparken

	bool operator<(int a)
	{
		return *(this->health) < a;
	}

	//sayý ve nesne karþýlaþtýrýrken (yani solda sayý varsa dýþta tanýmlarýz)

	friend bool operator>(int, const Agents&);

	int gethealth()
	{
		return *health;
	}
};

bool operator>(int a, const Agents& other)
{
	return a > *(other.health);
}




int main() {
	Agents yoru(100), omen(100), clove(70);

	cout << "==== ISLEMLERDEN ONCE ====" << endl;

	// yoru == omen testi
	if (yoru == omen) {
		cout << "Yoru ve Omen esit gucte. Canlar: " << yoru.gethealth() << endl;
	}

	// clove < yoru testi
	if (clove < yoru) {
		cout << "Clove'un cani su an daha az (" << clove.gethealth() << ")" << endl;
	}

	cout << "\n==== ISLEMLERDEN SONRA ====" << endl;

	yoru = clove;  // Atama operatoru calisir (Deep Copy)
	omen = 150;    // Eger constructor explicit degilse calisir (C++ nesneye cevirir)

	// Yeni durumlari karsilastir
	if (yoru == clove) {
		cout << "Yoru artik Clove'un kopyasi oldu." << endl;
	}

	// Nesne < Sayi testi
	if (yoru < 80) {
		cout << "Yoru hasarli durumda, cani 80'den kucuk!" << endl;
	}

	// Sayi > Nesne testi (Friend fonksiyon)
	if (200 > omen) {
		cout << "200 degeri Omen'in canindan buyuk." << endl;
	}

	return 0;
}
*/







/*	<< ve >> Operatorlerini Overload ettik bunun için istream ve ostream class larýný kullandýk dýþardan olduklarý içinse mecbur friend atadýk 
* friend oldugu için mecbur 2 parametreli oluyor bunlardan 1. ostream veya istream e verdiðimiz isim 2. si nesne sonra isim<< veya >> kullanýyoruz
* son olarak da o verdiðimiz isimi return ediyoruz genelde os ve is kullanýlýr.
	class Agents
	{
		int* health = new int{};	// new varsa üçlemeci kuralý gelir
	public:
		Agents(int _h=0) { *health = _h; }

		~Agents() { delete health; health = nullptr; }

		Agents(const Agents& other)
		{
			health = new int(*other.health);
		}

		Agents& operator=(const Agents& other)
		{
			if (this == &other) { return *this; }

			*health = *other.health;
			return *this;
		}

		friend ostream& operator<<(ostream& os, const Agents& other)	//bizim class elemanlarýmýz olmadýgý için mecbur friend olarak tanýmlamalýyýz.
		{
			os << *(other.health);
			return os;
		}

		friend istream& operator>>(istream& is,  Agents& other)	//cýktý için ostream girdi için istream & ile tanýmlarýz parametre olarak da onlardan birini alýrýz 
		{														// parametre olarak verdiðimiz adla da return ederiz !!girdi alýrken const kullanmayýz cunku girdi alýyoz.
			is >> *other.health;
			return is;
		}
	

	};

	int main()
	{
		Agents yoru(80),clove;
		cout << "Yorunun Cani: " << yoru << endl;
		cout << "Clove un Canini Giriniz:";
		cin >> clove;
		cout << "Clove un Cani: " << clove;

		return 0;
	}
	*/






/*			I/O FÝLE MANAGEMENT
class Agents
{
	int* health {};
public:
	Agents(int _h) { health =new int(_h) ; }	//3 lemeci halledildi...
	~Agents() { delete health; health = nullptr; }
	Agents(const Agents& other)
	{
		health = new int(*other.health);
	}
	Agents operator=(const Agents& other)
	{
		if (this == &other)
		{
			return *this;
		}

		*health = *other.health;
		return *this;
	}

	friend ostream& operator<<(ostream& os, const Agents& other);

};

ostream& operator<<(ostream& os, const Agents& other)
{
	os << *other.health;
	return os;
}


int main()
{
	Agents yoru(80);
	ifstream file("Yoru.txt");
	string line;

	if (!file) { cout << "Bir Seyler Ters Gitti..."; }

	while (getline(file,line))
	{
		cout << line << endl;
		int can = stoi(line);
		Agents YeniAjan(can);
		cout << "Dosyadan Yuklenen Yeni Ajan Cani: " << YeniAjan;
	}
	file.close();

	ofstream dosya("Yoru.txt", ios::app);	//dosyada önceki verilerin silinmesini engeller	

		if (!dosya) { cout << "Bir Seyler Ters Gitti..."; }

		dosya << "\nSelam Ya...";
		dosya.close();
		fstream dosya("Yoru.txt", ios::in);
		dosya.close();
		fstream dosya("Yoru.txt", ios::out);
		dosya.close();

	return 0;

}
*/








/*	VEKTOR KULLANIMI ** POÝNTER KULLANIMI TAM KAVRAMA ITERATOR NEDÝR NE ÝÞE YARAR.

class Agents
{
	int* health {};
public:
	Agents(int _h) { health =new int(_h) ; }	//3 lemeci halledildi...
	~Agents() { delete health; health = nullptr; }
	Agents(const Agents& other)
	{
		health = new int(*other.health);
	}
	Agents operator=(const Agents& other)
	{
		if (this == &other)
		{
			return *this;
		}

		*health = *other.health;
		return *this;
	}

	friend ostream& operator<<(ostream& os, const Agents& other);

};

ostream& operator<<(ostream& os, const Agents& other)
{
	os << *other.health;
	return os;
}


int main()
{
	vector<Agents*> takim;	// takim diye bir vektor olusturduk içerisinde ajanlarýn adreslerini tutuyor.

	takim.push_back(new Agents(80));	//ajanlar olusturduk.
	takim.push_back(new Agents(90));	

	for (Agents* a : takim)
	{
		cout << *a << "\n";
	}

	cout << "----------------------\n";

	vector<Agents*>::iterator it;
	//vector kutucuklarý olusturduk o kutucuklarý iterator olarak tanýmladýgýmýz it ile gezicez *it kutularýn deðerini gosterir ama kutularda agents* yani ajanlarýn adresi var
	//bu yuzden *it ajanlarýn adresini gösterir o adresinde gösterdiði deðeri yani ajanlarý istiyorsak **it kullanýrýz ve o kutucugun içindeki ajan adreslerinin 
	// gösterdiði deðer olan ajan nesnelerine ulaþýrýz. pointer olarak tanýmlamak zorunluydu cunku diðer turlu tum elemanlar nesnenin tipine bakýlmaksýzýn
	//agents class ýna ait nesne olarak olusurdu ama biz yoru veya omen class ýna ait istediðimiz için polymorphism olarak tanýmladýk bunlara eriþmek için de
	//* kullandýk cunku polymýrphism olmasý için new ike runtime da nesne olusturmalýyýz ve bunlara eriþmel için de pointer kullanmak zaten zorunludur.
	

	for (it = takim.begin(); it != takim.end(); ++it)
			
	{
		cout << **it << "\n";
	}
	return 0;
}
*/












