#include "head.h"

//----------KONSTRUKTOR DOMYSLNY----------//
Card::Card()
{
    value = num;
    ch = mark;
    col = colStart[counterC];
    current = 0;

    num++;
    if(num == 10)
    {
        num = 1;        //od nowa wartosci
        mark++;         //nowy symbol
        counterC++;     //nowy kolor
    }
}


//----------KONSTRUKTOR----------//
Card::Card(int v, char c)
{
    value = v;
    ch = c;
    col = 7;
    current = 0;
}


//----------OPERATOR <<----------//
ostream & operator<<(ostream & os, Card &k)
{
    if(k.current == 1)
        cout << "-";        //znacznik zagranej ostatnio karty
    else
        cout << " ";

    color(k.col);
    os << k.value; //<< k.ch;
    color(7);//bialy

    if(k.current == 1)
        cout << "-";

    k.current = 0;
    return os;
}


//----------OPERATOR ==----------//
bool operator==(Card &k, Card &k2)
{
    if((k.value == k2.value) && (k.ch == k2.ch))
        return 1;
    else
        return 0;
}


//----------METODA USTAW----------//
void Card::set(int v, char c)
{
    value = v;
    ch = c;
}
