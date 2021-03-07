#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <string.h>
#include <string>
using namespace std;
///Programul este adaptat dupa sursa mostenire.cpp din laborator, unele secvente fiind aproape identice in constructori,citire,afisare, functia statica
///Mentiune: am dat un mesaj in destructor ca sa se vada ca functioneaza cand este apelat, dar l-am comentat ca sa nu apara la fiecare afisare
class Persoana
{
protected:
    string nume;
    string cnp;
    static int n; ///variabila statica care numara cate persoane sunt declarate
public:
    Persoana(string, string);
    Persoana(Persoana&);
    virtual ~Persoana(); ///destructor virtual- late binding
    virtual void citire(istream& in);///citire virtuala- late binding
    virtual void afisare(ostream& out);///afisare virtuala- late binding
    friend istream& operator>>(istream& in, Persoana&);
    friend ostream& operator<<(ostream& out, Persoana&);
    Persoana& operator=(Persoana&);
    static void numarPers()   ///metoda statica de afisare a numarului de persoane
    {
        cout << n;
    }
    int varsta_cnp();
    string get_nume()
    {
        return nume;
    }
};

int Persoana::n;
///constructor adaptat din exemplul de la laborator
Persoana::Persoana(string num = "", string cod = "")
{
    n++;
    try
    {
        for (unsigned int i = 0; i < cod.length(); i++)
            if (cod[i]<'0' || cod[i]>'9')
                throw 1;
        nume = num;
        cnp = cod;
    }
    catch (int i)
    {
        cout << "Eroare in constructor! CNP-ul persoanei poate contine doar cifre.\n";
        exit(EXIT_FAILURE);
    }

}
Persoana::Persoana(Persoana &x)
{
    this->nume = x.nume;
    this->cnp = x.cnp;
}
Persoana::~Persoana()
{
    ///cout << "Destructorul persoanei" << nume << endl;
}
void Persoana::citire(istream &in)
{
    try
    {
        string x;
        cout << "CNP: ";
        in >> x;
        for (unsigned int i = 0; i < x.length(); i++)
            if (x[i]<'0' || x[i]>'9')
                throw 1;
        if (x.length() != 13 || !(x[0] == '1' || x[0] == '2' || x[0] == '5' || x[0] == '6'))
            throw 1;
        cnp = x;
        cout << "Nume: ";
        in.get();
        string y;
        getline(in, y);
        nume = y;
    }
    catch (int i)
    {
        cout << "Eroare in constructor! CNP invalid!\n";
        exit(EXIT_FAILURE);
    }
}
void Persoana::afisare(ostream &out)
{
    out << "CNP: " << cnp << endl;
    out << "Nume: " << nume << endl;
}
istream& operator>>(istream& in, Persoana& P)
{
    P.citire(in);
    return in;
}
ostream& operator<<(ostream& out, Persoana& P)
{
    P.afisare(out);
    return out;
}
Persoana& Persoana::operator=(Persoana &x)
{
    nume = x.nume;
    cnp = x.cnp;
    return *this;
}
int Persoana::varsta_cnp()
{
    char v[2];
    int x, an_nastere, an_curent;
    ///aflarea anului actual inspirata de pe https://www.tutorialspoint.com/cplusplus/cpp_date_time.htm
    time_t t = time(0);
    struct tm* now = localtime(&t);
    an_curent = now->tm_year + 1900;
    for (unsigned int i = 0; i < cnp.length(); i++)
    {
        v[0] = cnp[1];
        v[1] = cnp[2];
    }
    x = atoi(v);
    ///persoanele nascute intre 1900 si 1999 inclusiv au sexul in cnp cu cifra 1(B) sau 2(F)
    if (cnp[0] == '1' || cnp[0] == '2')
    {
        if (x == 0)
            an_nastere = 1900;
        else
            an_nastere = 1900 + x;
    }

    ///persoanele nascute dupa 2000 inclusiv au sexul in cnp cu cifra 5(B) sau 6(F)
    if (cnp[0] == '5' || cnp[0] == '6')
    {
        if (x == 0)
            an_nastere = 2000;
        else
            an_nastere = 2000 + x;
    }
    if (an_curent >= an_nastere)
        return an_curent - an_nastere;
    else
        return 0;
}
class Abonat :public Persoana
{
private:
    int nrMaxCarti;
    int nrCartiImprumutate;
    int pretAbonament;
public:
    Abonat(string, string, int, int, int);
    ~Abonat();
    Abonat(Abonat&);
    void citire(istream&);
    void afisare(ostream&);
    friend istream& operator>>(istream&, Abonat&);
    friend ostream& operator<<(ostream&, Abonat&);
    Abonat& operator=(Abonat &);
    int get_nrMaxCarti()
    {
        return nrMaxCarti;
    }
    int get_nrCartiImprumutate()
    {
        return nrCartiImprumutate;
    }
    int get_pretAbonament()
    {
        return pretAbonament;
    }

};
Abonat::Abonat(string cod = "", string num = "", int maxc = 0, int impc = 0, int pa = 0) :Persoana(cod, num)
{
    nrMaxCarti = maxc;
    nrCartiImprumutate = impc;
    pretAbonament = pa;
}
Abonat::~Abonat()
{
    ///cout << "Destructorul abonatului "<< get_nume() << endl;
}
Abonat::Abonat(Abonat& x) :Persoana(x.nume, x.cnp)
{
    this->nrMaxCarti = x.nrMaxCarti;
    this->nrCartiImprumutate = x.nrCartiImprumutate;
    this->pretAbonament = x.pretAbonament;
}

void Abonat::citire(istream &in)
{
    Persoana::citire(in);
    cout << "Numarul maxim de carti: ";
    in >> nrMaxCarti;
    cout << "Numarul cartilor imprumutate: ";
    in >> nrCartiImprumutate;
    if (nrCartiImprumutate > nrMaxCarti)
    {
        cout << "EROARE!!";
        exit(EXIT_FAILURE);
    }
    cout << "Pretul abonamentului: ";
    in >> pretAbonament;
    if (pretAbonament < nrCartiImprumutate)
    {
        cout << "EROARE!!";
        exit(EXIT_FAILURE);
    }
}
void Abonat::afisare(ostream &out)
{
    Persoana::afisare(out);
    out << "Numarul maxim de carti: " << nrMaxCarti << endl;
    out << "Numarul cartilor imprumutate: " << nrCartiImprumutate << endl;
    out << "Pretul abonamentului: " << pretAbonament << endl;
}
istream& operator>>(istream& in, Abonat &A)
{
    A.citire(in);
    return in;
}
ostream& operator<<(ostream& out, Abonat &A)
{
    A.afisare(out);
    return out;
}
Abonat& Abonat::operator=(Abonat &x)
{
    if (this != &x)
    {
        Persoana::operator=(x);
        nrMaxCarti = x.nrMaxCarti;
        nrCartiImprumutate = x.nrCartiImprumutate;
        pretAbonament = x.pretAbonament;
    }
    return *this;
}
class Dosar
{
private:
    Abonat *a;
    int n;
public:
    Dosar();
    Dosar(Abonat*, int);
    Dosar(Dosar&);
    ~Dosar();
    void citire(istream&);
    void afisare(ostream&);
    friend istream& operator>>(istream&, Dosar&);
    friend ostream& operator<<(ostream&, Dosar&);
    Dosar& operator=(Dosar&);
    void varsta_abonati();
};
void Dosar::varsta_abonati()
{
    for (int i = 0; i < n; i++)
    {
        if (a[i].varsta_cnp() < 20 && a[i].varsta_cnp() != 1)
            cout << "Abonatul " << a[i].get_nume() << " are " << a[i].varsta_cnp() << " ani\n";
        else if(a[i].varsta_cnp() >= 20 && a[i].varsta_cnp() != 1)
            cout << "Abonatul " << a[i].get_nume() << " are " << a[i].varsta_cnp() << " de ani\n";
        else if(a[i].varsta_cnp() == 1)
            cout << "Abonatul " << a[i].get_nume() << " are " << a[i].varsta_cnp() << " an\n";
    }

}
Dosar::Dosar()
{
    this->n = 0;
    this->a = NULL;
}
Dosar::Dosar(Abonat* a, int n)
{
    this->n = n;
    for (int i = 0; i < n; i++)
    {
        if (a[i].get_nrCartiImprumutate() > a[i].get_nrMaxCarti() || a[i].get_nrCartiImprumutate() > a[i].get_pretAbonament())
            break;
        this->a = a;
    }

}
Dosar::~Dosar()
{
    ///cout << "Destructorul dosarului ";
}
Dosar::Dosar(Dosar& x)
{
    a = x.a;
    n = x.n;
}
void Dosar::citire(istream &in)
{
    cout << "Numarul abonatilor: ";
    in >> n;
    a = new Abonat[n];
    for (int i = 0; i < n; i++)
    {
        in >> a[i];
    }
}
istream& operator>>(istream& in, Dosar& d)
{
    d.citire(in);
    return in;
}
void Dosar::afisare(ostream &out)
{
    out << "Numarul abonatilor: " << n << endl;
    for (int i = 0; i < n; i++)
    {
        out << a[i];
    }

}
ostream& operator<<(ostream& out, Dosar& d)
{
    d.afisare(out);
    return out;
}

Dosar& Dosar::operator=(Dosar &x)
{
    n = x.n;
    a = x.a;
    return *this;
}
void meniu()
{
    int optiune;
    Dosar d;
    Persoana P;
    Abonat A;

    do
    {
        cout << "\n Nistor Andreea-Cristina Grupa-254 Proiect-2 Tema 11\n";
        cout << "\n MENIU\n";
        cout << "\n ===================================\n";
        cout << " 1.Citirea a n obiecte de tip abonat din dosar\n";
        cout << " 2.Afisarea a n obiecte de tip abonat din dosar\n";
        cout << " 3.Calcularea varstei din CNP a fiecarui abonat din dosar\n";
        cout << " 4.Upcasting\n";
        cout << " 5.Downcasting\n";
        cout << " 6.Apelarea functiei statice\n";
        cout << " 7.Afisarea constructorului din clasa persoana\n";
        cout << " 8.Afisarea constructorului de copiere din clasa persoana\n";
        cout << " 9.Apelarea destructorului din clasa persoana\n";
        cout << "10.Citirea datelor unei persoane\n";
        cout << "11.Afisarea datelor unei persoane\n";
        cout << "12.Afisarea constructorului din clasa abonat\n";
        cout << "13.Afisarea constructorului de copiere din clasa abonat\n";
        cout << "14.Apelarea destructorului din clasa abonat\n";
        cout << "15.Citirea datelor unui abonat\n";
        cout << "16.Afisarea datelor unui abonat\n";
        cout << "17.Apelarea destructorului dosarului\n";
        cout << " 0.Iesire\n";
        cout << "\n";
        cout << "Alegeti optiunea din meniu: ";
        cin >> optiune;
        if (optiune == 1)
        {
            cin >> d;
        }
        if (optiune == 2)
        {
            cout << d;
        }
        if (optiune == 3)
        {
            d.varsta_abonati();
        }
        if (optiune == 4)
        {
            Persoana *v = new Abonat;
            cin >> *v;
            cout << *v;
        }
        if (optiune == 5)
        {
            Abonat *v = (Abonat*)new Persoana;
            cin >> *v;
            cout << *v;
        }
        if (optiune == 6)
        {
            Persoana::numarPers();
        }
        if (optiune == 7)
        {
            Persoana p("Ioana", "2980820100988");
            cout << p;
        }
        if (optiune == 8)
        {
            Persoana p1("Ioana", "2980820100988");
            Persoana p2("Mihai", "5010907100144");
            p1 = p2;
            cout << p1;
        }
        if (optiune == 9)
        {
            Persoana p1("Ioana", "2980820100988");
            Persoana p2("Mihai", "5010907100144");
            cout << p1;
            cout << p2;
        }
        if (optiune == 10)
        {
            cin >> P;
        }
        if (optiune == 11)
        {
            cout << P;
        }
        if (optiune == 12)
        {
            Abonat a("Ioana", "2980820100988", 10, 8, 30);
            cout << a;
        }
        if (optiune == 13)
        {
            Abonat a1("Ioana", "2980820100988", 10, 9, 31);
            Abonat a2("Mihai", "5010907100144", 5, 2, 10);
            a1 = a2;
            cout << a1;
        }
        if (optiune == 14)
        {
            Abonat a1("Ioana", "2980820100988", 10, 9, 31);
            Abonat a2("Mihai", "5010907100144", 5, 2, 10);
            cout << a1;
            cout << a2;
        }
        if (optiune == 15)
        {
            cin >> A;
        }
        if (optiune == 16)
        {
            cout << A;
        }
        if (optiune == 17)
        {
            Abonat a1("Ioana", "2980820100988", 10, 9, 31);
            Abonat a2("Mihai", "5010907100144", 5, 2, 10);
            Abonat *a = new Abonat[2];
            a[0] = a1;
            a[1] = a2;
            Dosar d(a, 2);
            cout << d;
        }
        if (optiune == 0)
        {
            cout << "\nEXIT!\n";
        }
        if (optiune < 0 || optiune>17)
        {
            cout << "\nOptiunea nu este in meniu\n";
        }
        cout << "\n";
        system("pause");
        system("cls");

    }
    while (optiune != 0);
}

int main()
{
    meniu();
    return 0;
}
