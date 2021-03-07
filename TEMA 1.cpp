#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;

class persoana {
private:
    string nume;
    int anul_nasterii;
    char sex;
public:

    ///setteri
    void set_nume(string);
    void set_anul_nasterii(int);
    void set_sex(char);
    ///getteri
    string get_nume() {
        return nume;
    };
    int get_anul_nasterii() {
        return anul_nasterii;
    };
    char get_sex() {
        return sex;
    };
    ///constructori
    ///acesti constructori au fost creati pentru a testa programul inainte de crearea meniului
    persoana(string, int, char); //constructor de initializare cu parametri
    persoana(); //constructor de initializare fara parametri
    void afisare(ostream &out);
    void citire(istream &in);
    friend istream& operator>>(istream &in, persoana& z);
    friend ostream& operator<<(ostream &out, persoana& z);

};
void persoana::citire(istream &in) {
    cout<<"Numele: ";
    in>>nume;
    cout<<"Anul nasterii: ";
    in>>anul_nasterii;
    cout<<"Sexul: ";
    in>>sex;

}
istream& operator>>(istream& in,persoana& z) {
    z.citire(in);
    return in;
}
void persoana::afisare(ostream &out) {
    out<<"Numele persoanei este:"<<nume;
    out<<"\n";
    out<<"Anul nasterii persoanei este:"<<anul_nasterii;
    out<<"\n";
    out<<"Sexul persoanei este: "<<sex;
    out<<"\n";

}
ostream& operator<<(ostream& out, persoana& z) {
    z.afisare(out);
    return out;
}
void persoana::set_nume(string nume) {
    this->nume = nume;
}
void persoana::set_anul_nasterii(int anul_nasterii) {
    this->anul_nasterii = anul_nasterii;
}
void persoana::set_sex(char sex) {
    this->sex = sex;
}

persoana::persoana(string nume="", int anul_nasterii=0, char sex=' ') {
    this->nume = nume;
    this->anul_nasterii = anul_nasterii;
    this->sex = sex;
}
/*persoana::persoana() {
    nume = "n/a";
    anul_nasterii = 0;
    sex = '-';
}*/
/*class baza_de_date {
private:
    persoana *v; //vector de persoane
    persoana *vcpy;
    int n=0;  //nr persoane
public:
    ///constructor de initializare
    baza_de_date();
    ///destructor
    ~baza_de_date();
    void add_pers(string,int,char);
    void eliminare(string);
    void eliminare(int);
    void eliminare(char);
    void sort_nume();
    void sort_varsta();
    void afisare();

};
baza_de_date::baza_de_date() {
    this->v = new persoana;
    v=NULL;
}
baza_de_date::~baza_de_date() {
    delete[] v;
}
///adaugarea este inspirata de aici din "Course.h" :
// https://www.dreamincode.net/forums/topic/195917-delete-elements-from-dynamic-array/
void baza_de_date::add_pers(string nume, int anul_nasterii, char sex) {
    persoana p(nume,anul_nasterii,sex);
    if (n == 0) {
        this->v = new persoana[n + 1];
        v[n] = p;
        this->n = n + 1;
    } else {
        this->vcpy = new persoana[n + 1];
        for (int i = 0; i < n; i++)
            this->vcpy[i] = this->v[i];
        this->v = new persoana[n + 1];
        for (int i = 0; i < n; i++)
            this->v[i] = this->vcpy[i];
        v[n] = p;
        this->n = n + 1;
    }
}

void baza_de_date::eliminare(string nume) {
    for (int i = n - 1; i >= 0; i--)

        if (v[i].get_nume() == nume) {
            for (int k = i; k < n - 1; k++) {
                v[i] = v[i + 1];
                i++;
            }
            n--;
        }

}
void baza_de_date::eliminare(int anul_nasterii) {
    for (int i = n-1; i >= 0; i--)
        if (v[i].get_anul_nasterii() == anul_nasterii) {
            for(int k=i; k<n-1; k++) {
                v[i] = v[i + 1];
                i++;
            }
            n--;
        }

}
void baza_de_date::eliminare(char sex) {
    for (int i = n-1; i >= 0; i--)
        if (v[i].get_sex() == sex) {
            for (int k = i; k < n - 1; k++) {
                v[i] = v[i + 1];
                i++;
            }
            n--;
        }

}
void baza_de_date::sort_nume() {
    int i,j;
    persoana aux;
    for(i=0; i<n-1; i++)
        for(j=i+1; j<n; j++)
            if(v[i].get_nume()>v[j].get_nume()) {
                aux=v[i];
                v[i]=v[j];
                v[j]=aux;
            }
}
void baza_de_date::sort_varsta() {
    int i,j;
    persoana aux;
    for(i=0; i<n-1; i++)
        for(j=i+1; j<n; j++)
            if(v[i].get_anul_nasterii()<v[j].get_anul_nasterii()) {
                aux=v[i];
                v[i]=v[j];
                v[j]=aux;
            }
}

void baza_de_date::afisare() {
    for (int i = 0; i < n; i++)
        cout<<"Numele persoanei este: "<<v[i].get_nume()<<" Anul nasterii= "<<v[i].get_anul_nasterii()<<" Sexul: "<<v[i].get_sex()<<endl;
}

///crearea meniului este luata din codul dat la laboratorul 3 (_charStarDataMember.cpp)
void afisare_meniu() {

    cout<<"\n Nistor Andreea-Cristina Grupa 254 - Proiect 1 - Nume proiect: Tema 13 \n";
    cout<<"\n\t MENIU:";
    cout<<"\n===========================================\n";
    cout<<"\n";
    cout<<"1. Citeste numarul de persoane";
    cout<<"\n";
    cout<<"2. Afiseaza persoanele";
    cout<<"\n";
    cout<<"3. Adaugarea unei noi persoane";
    cout<<"\n";
    cout<<"4. Eliminarea persoanelor in functie de nume";
    cout<<"\n";
    cout<<"5. Eliminarea persoanelor in functie de anul nasterii";
    cout<<"\n";
    cout<<"6. Eliminarea persoanelor in functie de sex";
    cout<<"\n";
    cout<<"7. Sortarea persoanelor in ordinea alfabetica a numelor";
    cout<<"\n";
    cout<<"8. Sortarea persoanelor in ordinea crescatoare a varstei";
    cout<<"\n";
    cout<<"9. Citire cu supraincarcare pe operator obiect persoana";
    cout<<"\n";
    cout<<"10. Afisare cu supraincarcare pe operator obiect persoana";
    cout<<"\n";
    cout<<"0. Iesire.";
    cout<<"\n";
}
void meniu() {
    int optiune;///optiunea aleasa din meniu
    optiune=0;
    int n=0;
    string nume,nume_d,nume_nou;
    int anul_nasterii,an_d,an_nou;
    char sex,sex_d,sex_nou;
    baza_de_date b;
    persoana p;

    do {
        afisare_meniu();

        cout<<"\nIntroduceti numarul actiunii: ";
        cin>>optiune;

        if (optiune==1) {
            cout<<"Dati numarul de persoane: ";
            cin>>n;
            cin.get();
            if (n>0) {

                for (int i=0; i<n; i++) {
                    cout<<"Numele: ";
                    cin>>nume;
                    cout<<"Anul nasterii: ";
                    cin>>anul_nasterii;
                    cout<<"Sexul(F/M): ";
                    cin>>sex;
                    sex=toupper(sex);
                    if(sex!='F'|| sex!='M') {
                        cout<<"Nu ati introdus un caracter potrivit pentru sex (F/M)!";
                        cout<<"\nEXIT!\n";
                        optiune=0;
                    }

                    ///conversia din lowercase in uppercase a numelor (utila pt sortare nume)
                    for(int c=0; c<nume.length(); c++) {
                        if(nume[c]>='a' && nume[c]<='z') {
                            nume[c]-=32;
                        }
                    }
                    b.add_pers(nume,anul_nasterii,sex);
                }

            } else
                cout<<"Valoarea n trebuie sa fie pozitiva!";

        }
        ///se poate face afisarea si dupa fiecare optiune aleasa apasand tasta 2,
        ///dar am facut-o si dupa apelarea adaugarii,eliminarilor si sortarilor ca sa fie vazute direct dupa efectuarea operatiilor
        if (optiune==2) {
            if (n!=0)
                b.afisare();
        }
        if (optiune==3) {
            if(n!=0) {
                cout<<"Cititi datele noii persoane: \n";
                cout<<"Numele: ";
                cin>>nume_nou;
                cout<<"Anul nasterii: ";
                cin>>an_nou;
                cout<<"Sexul: ";
                cin>>sex_nou;
                b.add_pers(nume_nou,an_nou,sex_nou);
                cout<<"\n";
                b.afisare();
            }
        }
        if (optiune==4) {
            cout<<"Introduceti numele dorit pentru a fi eliminat: ";
            cin>>nume_d;
            if(n!=0) {
                b.eliminare(nume_d);
                b.afisare();
            }

        }
        if (optiune==5) {
            cout<<"Introduceti anul dorit pentru a fi eliminat: ";
            cin>>an_d;
            if(n!=0) {
                b.eliminare(an_d);
                b.afisare();
            }
        }
        if (optiune==6) {
            cout<<"Introduceti sexul dorit pentru a fi eliminat: ";
            cin>>sex_d;
            if(n!=0) {
                b.eliminare(sex_d);
                b.afisare();
            }
        }
        if(optiune==7) {
            if(n!=0) {
                b.sort_nume();
                b.afisare();
            }
        }
        if(optiune==8) {
            if(n!=0) {
                b.sort_varsta();
                b.afisare();
            }
        }
        if(optiune==9) {
            cin>>p;
        }
        if(optiune==10) {
            cout<<p<<" ";
        }
        if (optiune==0) {
            cout<<"\nEXIT!\n";
        }
        if (optiune<0||optiune>10) {
            cout<<"\nSelectie invalida\n";
        }
        cout<<"\n";
        system("pause"); ///Pauza - Press any key to continue...
        system("cls");   ///Sterge continutul curent al consolei
    } while(optiune!=0);
}
*/
int main() {
    ///meniul

    //meniu();

    ///testarea functiilor fara meniu


    /*persoana p1,p4;

    cout<<endl;

    baza_de_date b;

    b.add_pers("Andreea",2000,'F');
    b.add_pers("ioana",1998,'F');
    b.add_pers("vali", 1999, 'M');
    b.add_pers("Pavel", 2001, 'M');

    b.afis();
    cout<<endl;

    b.sort_nume();
    b.afis();

    cout<<endl;

    b.eliminare(2001);
    b.afis();
    cout<<endl;

    b.sort_varsta();
    b.afis();
    */
    persoana p1("Andreea",2000,'f');
    cout<<p1;
    return 0;
}
