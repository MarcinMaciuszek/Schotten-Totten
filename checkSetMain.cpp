#include "head.h"


//----------AKTUALIZACJA SILY UKLADU----------//
void Player::checkSetMain(vector<Card> &check, int m)
{
    //cout << "Check" << endl;
    for(int j=0; j<S; j++)
        {mayPlay[j].clear(); impAI[j].clear();}

    for(int i=0; i<S; i++)                  //sprawdzanie kamieni po kolei, aktualizacja stanu na koniec tury
    {
        //----------3 KARTY----------//
        if(played[i].size() == 3)     //uklad pelny
        {
            system[i].mayPower = 0;   //znikaja uklady mozliwe
            system[i].mayValue = 0;   //--
            system[i].value = played[i][0].value + played[i][1].value + played[i][2].value;
            //^nowa wartosc ukladu

            system[i].power = checkSet3(played[i][0], played[i][1], played[i][2], check);
            //^wynik funkcji daje moc ukladu
        }

        //----------2 KARTY----------//
        else if(played[i].size() == 2)    //uklad z 2 kart
        {
            system[i].mayPower = checkSet2(played[i][0], played[i][1], i, check);
        }

        //----------1 KARTA----------//
        else if(played[i].size() == 1)
        {
            system[i].mayPower = checkSet1(played[i][0], i, check, m);      //m dla improveAI
        }

        //----------0 KART----------//
        else if(played[i].size() == 0)
        {
            system[i].mayPower = checkSet0(i, check);
        }

    }
}



//----------ZARZADZANIE SPRAWDZANIEM - 3 KARTY----------//
int Player::checkSet3(Card v1, Card v2, Card v3, vector<Card> &check)
{
    //cout << "CheckSet3" << endl;
    int tab[3] {v1.value, v2.value, v3.value};//pomocnicza do ustalenia stosunkow wartosci
    int max = 0;            //max w kartach
    int mid = 0;            //mid w kartach
    int min = 0;            //min w kartach

    for(int j=0; j<3; j++)
    {
        if(tab[j] > max)
            {min = mid; mid = max; max = tab[j];}
        else if(tab[j] > mid)
            {min = mid; mid = tab[j];}
        else
            {min = tab[j];}
    }

    //-----UKLAD O SILE 5-----//
    if(((v1.ch == v2.ch) && (v2.ch == v3.ch)) && ((min+2 == mid+1) && (mid+1 == max)))
        return 5;

    //-----UKLAD O SILE 4-----//
    else if((min == mid) && (mid == max))
        return 4;

    //-----UKLAD O SILE 3-----//
    else if((v1.ch == v2.ch) && (v2.ch == v3.ch))
        return 3;

    //-----UKLAD O SILE 2-----//
    else if((min+2 == mid+1) && (mid+1 == max))
        return 2;

    //-----UKLAD O SILE 1-----//
    else
        return 1;
}


//----------ZARZADZANIE SPRAWDZANIEM - 2 KARTY----------//
int Player::checkSet2(Card v1, Card v2, int st, vector<Card> &check)
{
    //cout << "CheckSet2" << endl;
    int max = 0;        //max w kartach
    int min = 0;        //min w kartach
    int tempV = 0;      //przechowuja wartosc szukanej karty
    char tempC = v1.ch;

    if(v1.value >= v2.value)
        {max = v1.value; min = v2.value;}
    else
        {max = v2.value; min = v1.value;}

    system[st].mayValue = min + max;       //okreslenie poczatkowej sily


    //-----UKLAD O SILE 5-----//
    if((v1.ch == v2.ch) && ((min+1 == max) || (min+2 == max)))
    {
        if(checkSetDeep2(st, max, min, tempC, check))
            return 5;
    }
    //-----UKLAD O SILE 4-----//
    if(min == max)
    {
        tempV = max;
        if(checkSetDeep2(st, tempV, check))
            return 4;

    }
    //-----UKLAD O SILE 3-----//
    if(v1.ch == v2.ch)
    {
        if(checkSetDeep2(st, tempC, check))         //wyszukanie najwiekszej karty w kolorze
            return 3;
    }
    //-----UKLAD O SILE 2-----//
    if((min+1 == max) || (min+2 == max))
    {
        if(checkSetDeep2(st, min, max, check))
            return 2;
    }
    //-----UKLAD O SILE 1-----//
    if(1)
    {
        if(checkSetDeep2(st, check))
            return 1;
    }
}


//----------ZARZADZANIE SPRAWDZANIEM - 1 KARTA----------//
int Player::checkSet1(Card v1, int st, vector<Card> &check, int m)
{
    //cout << "CheckSet1" << endl;
    int tempV = 0;
    char tempC = v1.ch;

    system[st].mayValue = v1.value;            //okrelsenie poczatkowej sily

    //-----UKLAD O SILE 5-----//
    if(checkSetDeep1(st, v1.value, tempC, check))
    {
        if((m == 2) && (order == 2))
            improveAI(st, v1.value, check);
        return 5;
    }


    //-----UKLAD O SILE 4-----//
    if(checkSetDeep1(st, v1.value, check))
        return 4;

    //-----UKLAD O SILE 3-----//
    if(checkSetDeep1(st, tempC, check))
        return 3;

    //-----UKLAD O SILE 2-----//
    char ch = 'x';
    if(checkSetDeep1(st, v1.value, ch, check))
        return 2;

    //-----UKLAD O SILE 1-----//
    if(checkSetDeep1(st, check))
        return 1;

}


//----------ZARZADZANIE SPRAWDZANIEM - 0 KART----------//
int Player::checkSet0(int st, vector<Card> &check)
{
    //cout << "CheckSet0" << endl;
    int v1 = 1;
    int v2 = 2;
    int v3 = 3;
    int v4 = 4;
    int tempV = 0;

    //-----UKLAD O SILE 5-----//
    if(checkSetDeep0(st, v1, v2, v3, v4, check))
        return 5;

    //-----UKLAD O SILE 4-----//
    if(checkSetDeep0(st, v1, v2, v3, check))
        return 4;

    //-----UKLAD O SILE 3-----//
    if(checkSetDeep0(st, v1, v2, check))
        return 3;

    //-----UKLAD O SILE 2-----//
    if(checkSetDeep0(st, v1, check))
        return 2;

    //-----UKLAD O SILE 1-----//
    if(checkSetDeep0(st, check))
        return 1;
}





