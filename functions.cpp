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
//m - mode


//----------FUNKCJE SETUPU----------//


//----------WPORWADZENIE----------//
void introduce()
{
    cout << "Witaj w grze Schotten-totten v1.5!" << endl;
}

//----------TWORZENIE STOSU SPRAWDZANIA----------//
void startCheck(vector<Card> &stcC, Card *ptrC)
{
    for(int i=0; i<K; i++)
        stcC.push_back(*(ptrC+i));
   // for(int i=0; i<K; i++)        //tester
   //     cout << stcC[i];
}

//----------TASOWANIE KART----------//
void randomCards(Card *ptrC)
{
    srand(time(NULL));                  //generator liczb losowych
    int temp = rand()%10000;
    for(int i=0; i<temp; i++)           //losowa liczba tasowan
        random_shuffle(ptrC, ptrC+K);
}

//----------TWORZENIE STOSU----------//
void stackStart(stack<Card> &stc, Card *ptrC)
{
    for(int i=0; i<K; i++)              //petla do zapelnienia stosu potasowanymi kartami
    {
        stc.push(*ptrC);
        ptrC++;
        //cout << stc.top() << endl;    //tester
    }
}

//----------USTAWIANIE KOLOROW----------//
void color(int x)
{
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOut, x);
}

//----------USTAWIANIE TRYBU ROZGRYWKI----------//
int gameMode()
{
    int c;
    cout << "Wybierz tryb rozgrywki:" << endl
         << "1. Gra dwuosobowa" << endl
         << "2. Gra z komputerem" << endl
         << "3. Koniec programu" << endl
         << "Wybor: ";
    cin >> c;
    while((c != 1) && (c != 2) && (c != 3))
    {
        cin.clear();
        cin.sync();
        cout << "Bledny wybor, wybierz jeszcze raz: " << endl;
        cin >> c;
    }
    return c;
}

//----------FLAME GENERATOR----------//
void flameGenerator()
{
    ; //bonus
}



