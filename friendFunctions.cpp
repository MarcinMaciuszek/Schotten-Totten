#include "head.h"

//----------LEGENDA----------//
//*ptrC - wskaznik na karty
//&stc - referencja na stos
//&p1, &p1 - referencje do graczy
//*sc - wskaznik do tablicy stanow kamienii
//*ptrP - wskaznika na aktywnego gracza
//*ptrP2 - wskaznik na drugiego gracza
//s - kamien do ktorego dograno karte
//v - wartosc karty
//c - kolor karty
//&check - referencja na stos do sprawdzenia
//s - set przeciwnika
//o - order
//st - numer kamienia

//----------FUNKCJE ZAPRZYJAZNIONE----------//


//----------LOSOWANIE PIERWSZEGO GRACZA----------//
Player * randomPlayer(Player &p1, Player &p2)
{
    cout << endl << "Losowanie pierwszego gracza..." << endl;

    srand(time(NULL));  //generator liczb losowych

    string temp;
    Player * tempPtr;

    if(rand()%2+1 == 1)
    {
        tempPtr = &p1;
        temp = p1.name;
    }
    else
    {
        tempPtr = &p2;
        temp = p2.name;
    }

    cout << "Gre zaczyna gracz o imieniu " << temp << "." << endl;
    Sleep(2000);

    return tempPtr;
}


//----------USTAWIANIE DRUGIEGO GRACZA----------//
Player * secondPlayer(Player &p1, Player &p2)
{
    Player * tempPtr;

    if(tempPtr == &p1)
        tempPtr = &p2;
    else if(tempPtr == &p2)
        tempPtr = &p1;

    return tempPtr;
}


//----------POKAZYWANIE PLANSZY----------//
void show(Player &p1, Player &p2, int *sc)
{
    system("cls");          //czyszczenie ekranu

    cout << "\t\t\t\t\t" << p2.name;
    cout << "\n\n\t";

    //-----kamienie zdobyte przez gracza 2-----//
    color(8);//szary
    for(int i=0; i<S; i++)
    {
        if(sc[i] == 2)
            cout << "*K" << i+1 << '*';
        else if(p2.system[i].power == 0)                                    //teseter do funkcji sprawdzania
            cout << p2.system[i].mayPower << " " << p2.system[i].mayValue;
           // for(int j=0; j<p2.mayPlay[i].size(); j++)
           //     cout << p2.mayPlay[i][j];
        else
            cout << p2.system[i].power << " " << p2.system[i].value;
        cout << "\t";
    }
    color(7);//bialy
    cout << "\n\n\t";

    //-----karty zagrane przez gracza nr 2-----//
    for(int j=M; j>0; j--)
    {
        for(int i=0; i<S; i++)
        {
        if(p2.played[i].size() >= j)
            cout << p2.played[i][j-1];
        cout << "\t";
        }
        cout << "\n\n\t";
    }

    //-----kamienie niezdobyte-----//
    color(8);//szary
    for(int i=0; i<S; i++)
    {
        if(sc[i] == 0)
            cout << "*K" << i+1 << '*';
        cout << "\t";
    }
    color(7);//bialy
    cout << "\n\n\t";

    //-----karty zagrane przez gracza nr 1-----//
    for(int j=0; j<M; j++)
    {
        for(int i=0; i<S; i++)
        {
        if(p1.played[i].size() >= j+1)
            cout << p1.played[i][j];
        cout << "\t";
        }
        cout << "\n\n\t";
    }

    //-----kamienie zdobyte przez gracza 1-----//
    color(8);//szary
    for(int i=0; i<S; i++)
    {
        if(sc[i] == 1)
            cout << "*K" << i+1 << '*';
        else if(p1.system[i].power == 0)                                    //teseter do funkcji sprawdzania
            cout << p1.system[i].mayPower << " " << p1.system[i].mayValue;
        else
            cout << p1.system[i].power << " " << p1.system[i].value;
        cout << "\t";
    }
    color(7);//bialy

    cout << "\n\n\t\t\t\t\t" << p1.name;
    cout << "\n\n";
}


//----------SPRAWDZANIE KAMIENI----------//

void check(Player *ptrP, Player *ptrP2, int *sc)
{
    for(int i=0; i<S; i++)
    {
        if(sc[i] == 0)                          //sprawdzanie tylko dla niezdobytych kamieni
        {
            if(ptrP->played[i].size() == 3)             //jezeli gracz ma 3 karty przy kamieniu
            {
                if(ptrP->system[i] >= ptrP2->system[i]) //jezeli gracz ma sielniejszy uklad
                {
                    if(ptrP->order == 1)                //jezeli to gracz nr 1
                        sc[i] = 1;
                    else
                        sc[i] = 2;
                }
            }
        }
    }
}

//----------POKAZUJE OUTY----------//
void showOuts(Player &p1, Player &p2)
{
    int W = 8;

    cout << endl << "Outy " << p1.name;
    cout.width(40-p1.name.size());
    cout << "Outy " << p2.name;
    cout << endl << endl;
    cout << "K";
    cout.width(W);
    cout << "Sila";
    cout.width(W);
    cout << "Wartosc";
    cout.width(W);
    cout << "Outy*";
    cout.width(2*W);
    cout << "K";
    cout.width(W);
    cout << "Sila";
    cout.width(W);
    cout << "Wartosc";
    cout.width(W);
    cout << "Outy*";
    cout << endl;

    for(int i=0; i<S; i++)
    {
        cout << i+1;

        if(p1.system[i].power == 0)
        {
            cout.width(W);
            cout << p1.system[i].mayPower;
            cout.width(W);
            cout << p1.system[i].mayValue;
        }

        else
        {
            cout.width(W);
            cout << p1.system[i].power;
            cout.width(W);
            cout << p1.system[i].value;
        }

        cout << "    ";
        for(int j=0; j<p1.mayPlay[i].size(); j++)
        {
            cout << p1.mayPlay[i][j];
        }

        int P = 2*W - 2*(p1.mayPlay[i].size());
        cout.width(P+4);

        cout << i+1;

        if(p2.system[i].power == 0)
        {
            cout.width(W);
            cout << p2.system[i].mayPower;
            cout.width(W);
            cout << p2.system[i].mayValue;
        }

        else
        {
            cout.width(W);
            cout << p2.system[i].power;
            cout.width(W);
            cout << p2.system[i].value;
        }

        cout << "     ";
        for(int j=0; j<p2.mayPlay[i].size(); j++)
        {
            cout << p2.mayPlay[i][j];
        }

        cout << endl;

    }
    cout << "*Outy dla najlepszego ukladu wyswietlane gdy zagranie zostanie chociaz jedna karta." << endl << endl;
}
