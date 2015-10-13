#include <iostream>
#include <stack>    //stack
#include <cstdlib>  //rand, srand
#include <time.h>   //time
#include <algorithm>//random_shuffle
#include <vector>   //vector
#include <windows.h>//kolory
#include <conio.h>  //getch

using namespace std;


//----------DEKLARACJE WYPRZEDZAJACE----------//
class Card;
class Player;
class Set;


//----------STALE----------//
const int H = 6;    //rozmiar reki
const int S = 9;    //ilosc kamieni
const int K = 54;   //ilosc kart
const int M = 3;    //maksymalna liczba kart przy jednym kamieniu na gracza





//----------ZMIENNE DO TWORZENIA KART----------//
static int counterC = 0;
static int num = 1;
static char mark = 'a';
const int colStart[6] = {2,4,6,9,12,13};


//----------ZMIENNE DO TWORZENIA GRACZY----------//
static int player = 1;


//----------FUNKCJE----------//
void introduce();                               //wprowadzenie
void startCheck(vector<Card> &stcC, Card *ptrC);//tworzenie kontenera do sprawdzania
void randomCards(Card *ptrC);                   //tasowanie kart
void stackStart(stack<Card> &stc, Card *ptrC);  //tworzenie stosu kart dobierania
void color(int x);                              //ustawianie kolorow
int gameMode();                                 //ustawia zmienna mode
void flameGenerator();      //bonus!!


//----------KLASA KARTA----------//
class Card
{
private:
    int value;          //wartosc karty miedzy 1-9
    char ch;            //symbol karty miedzy a-f
    int col;            //kolor 1-nieieski, 2-zielony, 4-brazowy, 5-fioletowy, 6-zolty, 12-czerwony
    int current;        //pozakuje ostatnio zagrana karte
public:
//konstruktory
    Card();
    Card(int v, char c);
//przeciazone operatory
    friend ostream & operator<<(ostream & os, Card &k);
    friend bool operator==(Card &k, Card & k2);
//klasa zaprzyjazniona
    friend class Player;
    friend class PlayerAI;
//metody
    void set(int v, char c);
};


//----------KLASA GRACZ----------//
class Player
{
private:
    string name;                    //imie gracza
    vector<Card> hand;              //reka gracza
    vector<vector<Card> > played;   //karty zagrane przez gracza przy poszczegolnych kamieniach
    vector<Set> system;             //sety gracza dla kazdego kamienia
    vector<vector<Card> > mayPlay;  //outy do kamieni
    vector<vector<Card> > impAI;    //dodatkowe outy dla AI
    int order;                      //znacznik gracza: 1-p1, 2-p2;
public:
//konstruktor
    Player(stack<Card> &s, int m);
//metody
    void startHand(stack<Card> & stc);              //dobiera startowa reke
    void play(vector<Card> &check, int *sc);        //wybiera zagranie
    void playRandom(vector<Card> &check, int *sc);  //niecalkowicie losowe wybranie zagrania
    void playAI(vector<Card> &check, int *sc);      //algorytm zagrywania AI
    void draw(stack<Card> &stc);                    //dobiera karte
    void showHand();                                //pokazuje reke
    int win(int *sc);                               //sprawdza warunek zwyciestwa
//funkcje zaprzyjaznione
    friend Player * randomPlayer(Player &p1, Player &p2);       //losuje pierwszego gracza
    friend Player * secondPlayer(Player &p1, Player &p2);       //ustawia drugiego gracza
    friend void show(Player &p1, Player &p2, int *sc);          //pokazuje obszar gry
    friend void check(Player *ptrP, Player *ptrP2, int *sc);    //sprawdza czy aktywny gracz ma uklad pozwalajacy zabrac kamien
    friend void showOuts(Player &p1, Player &p2);               //pokazuje outy
//metody sprawdzania
    //szef do sprawdzania ukladow
    void checkSetMain(vector<Card> &check, int m);
    //rozdzielnia do sprawdzania ukladow
    int checkSet3(Card v1, Card v2, Card v3, vector<Card> &check);
    int checkSet2(Card v1, Card v2, int i, vector<Card> &check);
    int checkSet1(Card v1, int i, vector<Card> &check, int m);
    int checkSet0(int i, vector<Card> &check);
    //2 karty
    int checkSetDeep2(int st, int tempVmax, int tempVmin, char c, vector<Card> &check);
    int checkSetDeep2(int st, int v, vector<Card> &check);
    int checkSetDeep2(int st, char c, vector<Card> &check);
    int checkSetDeep2(int st, int tempVmax, int tempVmin, vector<Card> &check);
    int checkSetDeep2(int st, vector<Card> &check);
    //1 karta
    int checkSetDeep1(int st, int v, char ch, vector<Card> &check);
    int checkSetDeep1(int st, int v, vector<Card> &check);
    int checkSetDeep1(int st, char c, vector<Card> &check);
    int checkSetDeep1(int st, vector<Card> &check);
    //0 kart
    int checkSetDeep0(int st, int v1, int v2, int v3, int v4, vector<Card> check);
    int checkSetDeep0(int st, int v1, int v2, int v3, vector<Card> check);
    int checkSetDeep0(int st, int v1, int v2, vector<Card> check);
    int checkSetDeep0(int st, int v1, vector<Card> check);
    int checkSetDeep0(int st, vector<Card> check);

    int improveAI(int st, int v, vector<Card> &check);
};


//----------KLASA UKLAD----------//
class Set
{
private:
    int power;      //typ ukladu: 5-najlepszy (strit w kolorze), 1-najgorszy (byle co)
    int value;      //suma wartosci kart
    int mayPower;   //mozliwy typ ukladu z obecnej sytuacji
    int mayValue;   //mozliwa wartosc ukladu z obecnej sytuacji
public:
//konstruktor
    Set();
//przeciazony operator
    bool operator>=(Set s);
//funkcja zaprzyjazniona
    friend void show(Player &p1, Player &p2, int *sc);
    friend void showOuts(Player &p1, Player &p2);
//klasa zaprzyjazniona
    friend class Player;
    friend class PlayerAI;
};

