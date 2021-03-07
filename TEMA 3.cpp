#include <iostream>
#include <list>
#include <stdlib.h>
#include <string.h>
#include <typeinfo>
using namespace std;
///am utilizat notiuni de la laborator pentru realizarea template-ului, pentru utilizarea structurii de date list<Animal*>

class Animal
{
protected:
    string denumire;
    char sex;
    string mediu;
    static int nr;
public:
    Animal(string,char,string);
    Animal(const Animal&);
    virtual ~Animal();
    virtual void citire(istream &in);
    virtual void afisare(ostream &out);
    friend istream& operator>>(istream&,Animal&);
    friend ostream& operator<<(ostream&,Animal&);
    Animal& operator=(const Animal &a);
    static void nrAnimale()
    {
        cout<<nr;
    }
    string get_den()const
    {
        return denumire;
    }
};
int Animal::nr;
Animal::Animal(string den=" ",char s=' ',string med=" ")
{
    nr++;
    denumire=den;
    sex=s;
    mediu=med;
}
Animal::Animal(const Animal& x)
{
    denumire=x.denumire;
    sex=x.sex;
    mediu=x.mediu;
}
Animal::~Animal()
{

}
void Animal::citire(istream& in)
{
    cout<<"Denumire: ";
    in>>denumire;
    cout<<"Sex(F/M):  ";
    int ok;
    do
    {
        try
        {
            in>>sex;
            if(!(sex=='M'||sex=='F'))
            {
                throw 1;
                ok=0;
            }
            else
                ok=1;
        }
        catch(int i)
        {
            cout<<"Introduceti un caracter valid pentru sex. Alegeti M sau F: ";
            ok=0;
        }
    }
    while(ok==0);

    cout<<"Mediu de provenienta: ";
    in>>mediu;
}
istream& operator>>(istream& in, Animal& a)
{
    a.citire(in);
    return in;
}
void Animal::afisare(ostream& out)
{
    out<<"Animalul este: "<<denumire<<", de sex "<<sex<<" si traieste in "<<mediu<<"\n";
}
ostream& operator<<(ostream& out, Animal& a)
{
    a.afisare(out);
    return out;
}
Animal& Animal::operator=(const Animal& x)
{
    denumire=x.denumire;
    sex=x.sex;
    mediu=x.mediu;
    return *this;

}
class Nevertebrat:public Animal
{
private:
    string specie;
public:
    Nevertebrat(string,string,char,string);
    Nevertebrat(const Nevertebrat&);
    ~Nevertebrat();
    void citire(istream& in);
    void afisare(ostream& out);
    Nevertebrat& operator=(const Nevertebrat&);
};
Nevertebrat::Nevertebrat(string spec=" ",string den=" ", char s=' ', string med=" "):Animal(den,s,med)
{
    specie=spec;
}
Nevertebrat::Nevertebrat(const Nevertebrat& x):Animal(x.denumire,x.sex,x.mediu)
{
    specie=x.specie;
}
Nevertebrat::~Nevertebrat()
{

}
void Nevertebrat::citire(istream& in)
{
    Animal::citire(in);
    cout<<"Animalul nevertebrat face parte din specia: ";
    in>>specie;
}
void Nevertebrat::afisare(ostream& out)
{
    Animal::afisare(out);
    out<<"Animalul nevertebrat face parte din specia: "<<specie<<"\n";
}
Nevertebrat& Nevertebrat::operator=(const Nevertebrat& x)
{
    if(this!=&x)
    {
        Animal::operator=(x);
        specie=x.specie;
    }
    return *this;
}
class Vertebrat:public Animal
{
protected:
    string specie;
public:
    Vertebrat(string,string,char,string);
    Vertebrat(const Vertebrat&);
    virtual ~Vertebrat();
    virtual void citire(istream& in);
    virtual void afisare(ostream& out);
    Vertebrat& operator=(const Vertebrat&);

};
Vertebrat::Vertebrat(string spec=" ",string den=" ", char s=' ', string med=" "):Animal(den,s,med)
{
    specie=spec;
}
Vertebrat::Vertebrat(const Vertebrat& x):Animal(x.denumire,x.sex,x.mediu)
{
    specie=x.specie;
}
Vertebrat::~Vertebrat()
{

}
void Vertebrat::citire(istream& in)
{
    Animal::citire(in);
    cout<<"Animalul vertebrat face parte din specia: ";
    in>>specie;
}
void Vertebrat::afisare(ostream& out)
{
    Animal::afisare(out);
    out<<"Animalul vertebrat face parte din specia: "<<specie<<"\n";
}
Vertebrat& Vertebrat::operator=(const Vertebrat& x)
{
    if(this!=&x)
    {
        Animal::operator=(x);
        specie=x.specie;
    }
    return *this;
}
class Peste:public Vertebrat
{
private:
    string tip;
    float lungime;
public:
    Peste(string,float,string,string,char,string);
    Peste(const Peste&);
    ~Peste();
    string get_tip()
    {
        return tip;
    }
    float get_lungime()
    {
        return lungime;
    }
    void citire(istream& in);
    void afisare(ostream& out);
    Peste& operator=(Peste&);

};
Peste::Peste(string t=" ",float l=0,string spec=" ",string den=" ",char s=' ',string med=" "):Vertebrat(spec,den,s,med)
{
    tip=t;
    lungime=l;
}
Peste::Peste(const Peste& x):Vertebrat(x.specie)
{
    tip=x.tip;
    lungime=x.lungime;
}
Peste::~Peste()
{

}
void Peste::citire(istream& in)
{
    Vertebrat::citire(in);
    cout<<"Lungimea pestelui: ";
    in>>lungime;

    cout<<"Tipul pestelui(rapitor/nerapitor): ";
    int ok;
    do
    {
        try
        {
            in>>tip;
            if(!(tip=="rapitor" || tip=="nerapitor"))
            {
                throw 1;
                ok=0;
            }
            else
                ok=1;
        }
        catch(int i)
        {
            cout<<"Nu ati introdus un tip valid. Incercati rapitor sau nerapitor: ";
            ok=0;
        }

    }
    while(ok==0);
}
void Peste::afisare(ostream& out)
{
    Vertebrat::afisare(out);
    out<<"Tipul pestelui: "<<tip<<", lungimea pestelui: "<<lungime<<" m\n";
}
Peste& Peste::operator=(Peste& x)
{
    if(this!=&x)
    {
        Vertebrat::operator=(x);
        tip=x.tip;
        lungime=x.lungime;
    }
    return *this;
}
class Pasare:public Vertebrat
{
private:
    string culoare;
public:
    Pasare(string,string,string,char,string);
    Pasare(const Pasare&);
    ~Pasare();
    void citire(istream& in);
    void afisare(ostream& out);
    Pasare& operator=(Pasare&);
};
Pasare::Pasare(string cul=" ",string spec=" ",string den=" ",char s=' ',string med=" "):Vertebrat(spec,den,s,med)
{
    culoare=cul;
}
Pasare::Pasare(const Pasare& x):Vertebrat(x.specie)
{
    culoare=x.culoare;
}
Pasare::~Pasare()
{

}
void Pasare::citire(istream& in)
{
    Vertebrat::citire(in);
    cout<<"Culoarea pasarei: ";
    in>>culoare;
}
void Pasare::afisare(ostream& out)
{
    Vertebrat::afisare(out);
    out<<"Culoarea pasarei: "<<culoare<<"\n";
}
Pasare& Pasare::operator=(Pasare& x)
{
    if(this!=&x)
    {
        Vertebrat::operator=(x);
        culoare=x.culoare;
    }
    return *this;
}
class Mamifer:public Vertebrat
{
private:
    string tip_hrana;
public:
    Mamifer(string,string,string,char,string);
    Mamifer(const Mamifer&);
    ~Mamifer();
    void citire(istream& in);
    void afisare(ostream& out);
    Mamifer& operator=(Mamifer&);

};
Mamifer::Mamifer(string hr=" ",string spec=" ",string den=" ",char s=' ',string med=" "):Vertebrat(spec,den,s,med)
{
    tip_hrana=hr;
}
Mamifer::Mamifer(const Mamifer& x):Vertebrat(x.specie)
{
    tip_hrana=x.tip_hrana;
}
Mamifer::~Mamifer()
{

}
void Mamifer::citire(istream& in)
{
    Vertebrat::citire(in);
    cout<<"Tipul hranei mamiferului este(omnivor/carnivor/erbivor): ";
    int ok;
    do
    {
        try
        {
            in>>tip_hrana;
            if(!(tip_hrana=="omnivor" || tip_hrana=="carnivor" || tip_hrana=="erbivor"))
            {
                throw 1;
                ok=0;
            }
            else
                ok=1;
        }
        catch(int i)
        {
            cout<<"Nu ati introdus un tip valid. Incercati omnivor,carnivor sau erbivor: ";
            ok=0;
        }

    }
    while(ok==0);

}
void Mamifer::afisare(ostream& out)
{
    Vertebrat::afisare(out);
    out<<"Mamiferul este: "<<tip_hrana<<"\n";
}
Mamifer& Mamifer::operator=(Mamifer& x)
{
    if(this!=&x)
    {
        Vertebrat::operator=(x);
        tip_hrana=x.tip_hrana;
    }
    return *this;
}
class Reptila:public Vertebrat
{
private:
    string tip_venin;
public:
    Reptila(string,string,string,char,string);
    Reptila(const Reptila&);
    ~Reptila();
    void citire(istream& in);
    void afisare(ostream& out);
    Reptila& operator=(Reptila&);

};
Reptila::Reptila(string tv=" ",string spec=" ",string den=" ",char s=' ',string med=" "):Vertebrat(spec,den,s,med)
{
    tip_venin=tv;
}
Reptila::Reptila(const Reptila& x):Vertebrat(x.specie)
{
    tip_venin=x.tip_venin;
}
Reptila::~Reptila()
{

}
void Reptila::citire(istream& in)
{
    Vertebrat::citire(in);
    cout<<"Reptila este(veninoasa/neveninoasa): ";
    int ok;
    do
    {
        try
        {
            in>>tip_venin;
            if(!(tip_venin=="veninoasa" || tip_venin=="neveninoasa"))
            {
                throw 1;
                ok=0;
            }
            else
                ok=1;
        }
        catch(int i)
        {
            cout<<"Nu ati introdus un tip valid. Incercati veninoasa sau neveninoasa: ";
            ok=0;
        }

    }
    while(ok==0);

}
void Reptila::afisare(ostream& out)
{
    Vertebrat::afisare(out);
    out<<"Reptila este: "<<tip_venin<<"\n";
}
Reptila& Reptila::operator=(Reptila& x)
{
    if(this!=&x)
    {
        Vertebrat::operator=(x);
        tip_venin=x.tip_venin;
    }
    return *this;
}


template <class t> class AtlasZoologic
{
    int n;
    t *v;
    t *vcpy;
public:
    AtlasZoologic(t *p=NULL,int nr=0)
    {
        n=nr;
        v=new t[n];
        for(int i=0; i<n; i++)
        {
            v[i]=p[i];
        }
    }
    AtlasZoologic(AtlasZoologic& a)
    {
        n=a.n;
        v=new t[n];
        for(int i=0; i<n; i++)
        {
            v[i]=a.v[i];
        }
    }
    ~AtlasZoologic()
    {
        delete[] v;
    }
    int get_n()
    {
        return n;
    }
    t get_v(int i)
    {
        return v[i];
    }
    friend istream& operator>>(istream& in, AtlasZoologic <t> &g)
    {
        if(typeid(t)==typeid(Nevertebrat))
            cout<<"Numarul animalelor nevertebrate este: ";
        if(typeid(t)==typeid(Pasare))
            cout<<"Numarul de pasari este: ";
        if(typeid(t)==typeid(Mamifer))
            cout<<"Numarul de mamifere este: ";
        if(typeid(t)==typeid(Reptila))
            cout<<"Numarul de reptile este: ";
        in>>g.n;
        g.v=new t[g.n];
        cout<<"Introduceti obiectele:\n";
        for(int i=0; i<g.n; i++)
        {
            in>>g.v[i];

        }
        return in;
    }
    friend ostream& operator<<(ostream& out, AtlasZoologic <t> &g)
    {
        if(typeid(t)==typeid(Nevertebrat))
            cout<<"\nIn atlas sunt "<<g.n<<" nevertebrate\n";
        if(typeid(t)==typeid(Pasare))
            out<<"\nIn atlas sunt "<<g.n<<" pasari\n";
        if(typeid(t)==typeid(Mamifer))
            out<<"\nIn atlas sunt "<<g.n<<" mamifere\n";
        if(typeid(t)==typeid(Reptila))
            out<<"\nIn atlas sunt "<<g.n<<" reptile\n";
        cout<<"--------------------------\n";
        for(int i=0; i<g.n; i++)
            out<<g.v[i]<<"\n";
        return out;
    }
    AtlasZoologic& operator+=(const AtlasZoologic <t>& a)
    {
        t fisa;
        if(typeid(t)==typeid(Nevertebrat))
            cout<<"\nCitire fisa de observatie a unui nevertebrat nou:\n";
        if(typeid(t)==typeid(Pasare))
            cout<<"\nCitire fisa de observatie a unei pasari noi:\n";
        if(typeid(t)==typeid(Mamifer))
            cout<<"\nCitire fisa de observatie a unui mamifer nou:\n";
        if(typeid(t)==typeid(Reptila))
            cout<<"\nCitire fisa de observatie a unei reptile noi:\n";

        cin>>fisa;

        if(n==0)
        {
            this->v=new t[n+1];
            v[n]=fisa;
            this->n=n+1;
        }
        else
        {
            this->vcpy=new t[n+1];
            for(int i=0; i<n; i++)
                this->vcpy[i]=this->v[i];
            this->v=new t[n+1];
            for(int i=0; i<n; i++)
                this->v[i]=this->vcpy[i];
            v[n]=fisa;
            this->n=n+1;
        }
        return *this;
    }


};
template <> class AtlasZoologic <Peste>
{
    int n;
    Peste *v;
    Peste *vcpy;
public:
    AtlasZoologic(Peste *p=NULL,int nr=0)
    {
        n=nr;
        v=new Peste[n];
        for(int i=0; i<n; i++)
        {
            v[i]=p[i];
        }
    }
    AtlasZoologic(AtlasZoologic& a)
    {
        n=a.n;
        v=new Peste[n];
        for(int i=0; i<n; i++)
        {
            v[i]=a.v[i];
        }
    }
    ~AtlasZoologic()
    {
        delete[] v;
    }
    int get_n()
    {
        return n;
    }
    Peste get_v(int i)
    {
        return v[i];
    }

    friend istream& operator>>(istream& in, AtlasZoologic <Peste> &g)
    {
        cout<<"Numarul de pesti este: ";
        in>>g.n;
        g.v=new Peste[g.n];
        cout<<"Introduceti obiectele:\n";
        for(int i=0; i<g.n; i++)
        {
            in>>g.v[i];
        }
        return in;
    }
    friend ostream& operator<<(ostream& out, AtlasZoologic <Peste> &g)
    {
        int nr_rap=0;
        out<<"\nIn atlas sunt "<<g.n<<" pesti\n";
        cout<<"---------------------------------------------------------------\n";
        for(int i=0; i<g.n; i++)
            out<<g.v[i]<<"\n";
        for(int i=0; i<g.n; i++)
            if(g.v[i].get_lungime()>1 && g.v[i].get_tip()=="rapitor")
                nr_rap++;
        cout<<"---------------------------------------------------------------\n";
        out<<"\nNr pestilor rapitori cu lungimea mai mare de 1m este: "<<nr_rap<<"\n";
        return out;
    }
    AtlasZoologic& operator+=(const AtlasZoologic <Peste>& a)
    {
        Peste fisa;
        cout<<"\nCitire fisa de observatie a unui peste nou:\n";
        cin>>fisa;

        if(n==0)
        {
            this->v=new Peste[n+1];
            v[n]=fisa;
            this->n=n+1;
        }
        else
        {
            this->vcpy=new Peste[n+1];
            for(int i=0; i<n; i++)
                this->vcpy[i]=this->v[i];
            this->v=new Peste[n+1];
            for(int i=0; i<n; i++)
                this->v[i]=this->vcpy[i];
            v[n]=fisa;
            this->n=n+1;
        }
        return *this;
    }


};
void tip_list(Animal *&p, int &i, list<Animal*> &l)
{
    string s;
    cout<<"Introduceti tipul animalului: (animal/nevertebrat/vertebrat/peste/pasare/mamifer/reptila) "<<i+1<<": ";
    cin>>s;
    try
    {
        if(s=="animal")
        {
            p=new Animal;
            cin>>*p;
            l.push_back(*&p);
            i++;
        }
        else if(s=="nevertebrat")
        {
            p=new Nevertebrat;
            cin>>*p;
            l.push_back(*&p);
            i++;
        }
        else if(s=="vertebrat")
        {
            p=new Vertebrat;
            cin>>*p;
            l.push_back(*&p);
            i++;
        }
        else if(s=="peste")
        {
            p=new Peste;
            cin>>*p;
            l.push_back(*&p);
            i++;
        }
        else if(s=="pasare")
        {
            p=new Pasare;
            cin>>*p;
            l.push_back(*&p);
            i++;
        }
        else if(s=="mamifer")
        {
            p=new Mamifer;
            cin>>*p;
            l.push_back(*&p);
            i++;
        }
        else if(s=="reptila")
        {
            p=new Reptila;
            cin>>*p;
            l.push_back(*&p);
            i++;
        }
        else
            throw 10;

    }
    catch(bad_alloc var)
    {
        cout<<"Allocation Failure\n";
        exit(EXIT_FAILURE);
    }
    catch(int j)
    {
        cout<<"Nu ati introdus un tip valid!\n";
    }


}
void tip(Animal *&p, int &i)
{
    string s;
    cout<<"\n";
    cout<<"Tipul "<<i+1<<": ";
    cin>>s;
    try
    {
        if(s=="nevertebrat")
        {
            p=new Nevertebrat;
            cin>>*p;
            i++;
        }
        if(s=="peste")
        {
            p=new Peste;
            cin>>*p;
            i++;
        }
        else if(s=="pasare")
        {
            p=new Pasare;
            cin>>*p;
            i++;
        }
        else if(s=="mamifer")
        {
            p=new Mamifer;
            cin>>*p;
            i++;
        }
        else if(s=="reptila")
        {
            p=new Reptila;
            cin>>*p;
            i++;
        }
        else
            throw 10;
    }
    catch(bad_alloc var)
    {
        cout<<"Allocation Failure\n";
        exit(EXIT_FAILURE);
    }
    catch(int j)
    {
        cout<<"Nu ati introdus un tip de animal valid. Incercati nevertebrat, peste, pasare, mamifer sau reptila\n";
    }
}
void meniu()
{
    int optiune;
    Animal** v;
    int n;
    do
    {
        cout<<"\n Nistor Andreea-Cristina Grupa-254 Proiect-3 Tema 2\n";
        cout<<"\n MENIU\n";
        cout<<"\n ===================================\n";
        cout<<" 1.Citirea informatiilor complete a n animale,memorarea si afisarea acestora---UPCAST & LATE BINDIG\n";
        cout<<" 2.Contorizare --- DYNAMIC CAST\n";
        cout<<" 3.Atlas Zoologic --- TEMPLATE(Pasare)\n";
        cout<<" 4.Atlas Zoologic --- TEMPLATE(Mamifer)\n";
        cout<<" 5.Atlas Zoologic --- TEMPLATE(Reptila)\n";
        cout<<" 6.Atlas Zoologic --- TEMPLATE(Peste-specializare)\n";
        cout<<" 7.Folosirea structurii de date list <Animal*>\n";
        cout<<" 8.Citirea unor tipuri de animale si adaugarea unei noi fise de observatie in atlas\n";
        cout<<" 9.Apelarea functiei statice\n";
        cout<<"10.Apelarea functiei const\n";
        cout<<" 0.Iesire\n";
        cout<<"\n";
        cout<<"Alegeti optiunea din meniu: ";

        cin>>optiune;

        if(optiune==1)
        {
            cout<<"Introduceti numarul de animale: ";
            cin>>n;
            v=new Animal*[n];
            if(n>0)
            {
                for(int i=0; i<n; tip(v[i],i))
                    cout<<"\nAlegeti tipul de animal dorit dintre: nevertebrat, peste, pasare, mamifer sau reptila\n";
                for(int i=0; i<n; i++)
                {
                    cout<<"\n"<<*v[i];
                    cout<<"---------------------------------------------------------------\n";
                }

            }
            else
                cout<<"Numarul introdus trebuie sa fie pozitiv\n";
        }
        if(optiune==2)
        {
            int pes=0,pas=0,mam=0,rep=0;
            if(n>0)
            {
                for(int i=0; i<n; i++)
                {
                    Peste *p1=dynamic_cast<Peste*>(v[i]);
                    Pasare *p2=dynamic_cast<Pasare*>(v[i]);
                    Mamifer *p3=dynamic_cast<Mamifer*>(v[i]);
                    Reptila *p4=dynamic_cast<Reptila*>(v[i]);
                    if(p1)
                        pes++;
                    if(p2)
                        pas++;
                    if(p3)
                        mam++;
                    if(p4)
                        rep++;

                }
                cout<<"Nr de pesti: "<<pes<<"\n";
                cout<<"Nr de pasari: "<<pas<<"\n";
                cout<<"Nr de mamifere: "<<mam<<"\n";
                cout<<"Nr de reptile: "<<rep<<"\n";
            }
            else
            {
                cout<<"Nu s-au citit animale. Reveniti la actiunea 1\n";
            }
        }
        if(optiune==3)
        {
            AtlasZoologic <Pasare> k;
            cin>>k;
            cout<<k;
        }
        if(optiune==4)
        {
            AtlasZoologic <Mamifer> z;
            cin>>z;
            cout<<z;
        }
        if(optiune==5)
        {
            AtlasZoologic <Reptila> y;
            cin>>y;
            cout<<y;
        }
        if(optiune==6)
        {
            AtlasZoologic <Peste> x;
            cin>>x;
            cout<<x;
        }
        if(optiune==7)
        {
            list <Animal*> padure;
            int n;
            cout<<"Numarul de animale este: ";
            cin>>n;
            Animal **a=new Animal*[n];
            for(int i=0; i<n;)
                tip_list(a[i],i,padure);

            list<Animal*>::iterator i;
            cout<<"---------------------------------------------------------------\n";
            for (i=padure.begin(); i!=padure.end(); ++i)
            {
                cout<<(**i);
            }
        }
        if(optiune==8)
        {

            string s;
            cout<<"\n";
            cout<<"Alegeti tipul de animal dorit dintre: nevertebrat, peste, pasare, mamifer sau reptila:\n";
            cin>>s;
            try
            {
                if(s=="nevertebrat")
                {
                    AtlasZoologic <Nevertebrat> z,x;
                    cin>>z;
                    z+=x;
                    cout<<z;
                }
                else if(s=="peste")
                {
                    AtlasZoologic <Peste> z,x;
                    cin>>z;
                    z+=x;
                    cout<<z;
                }
                else if(s=="pasare")
                {
                    AtlasZoologic <Pasare> z,x;
                    cin>>z;
                    z+=x;
                    cout<<z;
                }
                else if(s=="mamifer")
                {
                    AtlasZoologic <Mamifer> z,x;
                    cin>>z;
                    z+=x;
                    cout<<z;
                }
                else if(s=="reptila")
                {
                    AtlasZoologic <Reptila> z,x;
                    cin>>z;
                    z+=x;
                    cout<<z;
                }
                else
                    throw 10;
            }
            catch(bad_alloc var)
            {
                cout<<"Allocation Failure\n";
                exit(EXIT_FAILURE);
            }
            catch(int j)
            {
                cout<<"Nu ati introdus un tip de animal valid. Incercati nevertebrat, peste,pasare,mamifer sau reptila\n";
            }

        }
        if(optiune==9)
        {
            Animal::nrAnimale();
        }
        if(optiune==10)
        {
            Animal a("URS",'M',"PADURE");
            cout<<a.get_den();
        }
        if(optiune==0)
        {
            cout<<"\nEXIT!\n";
        }
        if(optiune<0||optiune>10)
        {
            cout<<"\nOptiunea nu este in meniu\n";
        }
        cout<<"\n";
        system("pause");
        system("cls");

    }
    while(optiune!=0);
}

int main()
{
    meniu();

    return 0;
}
