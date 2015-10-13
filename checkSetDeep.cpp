#include "head.h"

//---------------AI IMPROVE----------------//
int Player::improveAI(int st, int v, vector<Card> &check)           //zwraca sume wartosci 2 kart o tej samej wartosci
{
    //cout << "s4" << endl;
    vector<Card> temp;                    //liczy karty spelniajace warunek
    for(int i=0; i<check.size(); i++)
    {
        if(v == check[i].value)
        {
            temp.push_back(check[i]);
        }
    }

    if(temp.size() > 1)
    {
        for(int j=0; j<temp.size(); j++)
            impAI[st].push_back(temp[j]);
    }

    return 1;
}

//*****---------- FUNKCJA checkSetDeep2 ----------*****//

//---------------SILA 5---------------//do zrobienia
int Player::checkSetDeep2(int st, int tempVmax, int tempVmin, char c, vector<Card> &check)   //zwraca jedyna mozliwa karte
{
    //cout << "s5" << endl;
    Card c1;
    Card c2;

    if(tempVmin+1 == tempVmax)  //karty kolo siebie
    {
        c1.set(tempVmax+1, c); //utworzenie szukanych kart
        c2.set(tempVmin-1, c); //--
    }

    else if(tempVmin+2 == tempVmax) //karty rozdzielone przerwa
    {
        c1.set(tempVmin+1, c); //
        c2.set(10, 'z');       //utworzenie karty nie do zanlezienia
    }

    //c1.show();
    //c2.show();

    for(int i=check.size()-1; i>=0; i--)    //pierwsza napotkana karta bedzie o najwzyszej wartosci ze wzgledu na ulozenie
    {
        if((c1 == check[i]) || (c2 == check[i]))
            mayPlay[st].push_back(check[i]);
    }

    if(mayPlay[st].size() > 0)                      //jezeli zostala znaleziona jakas karta to ustala sie sile ukladu
    {
        system[st].mayValue += mayPlay[st][0].value;
        return 1;
    }

    else
        return 0;
}

//---------------SILA 4---------------//
int Player::checkSetDeep2(int st, int v, vector<Card> &check)           //zwraca karte o okreslonej wartosci
{
    //cout << "s4" << endl;
    for(int i=0; i<check.size(); i++)
    {
        if(v == check[i].value)
            mayPlay[st].push_back(check[i]);        //ladowanie kontenera spelniajacymi warunki kartami
    }

    if(mayPlay[st].size() > 0)                      //jezeli zostala znaleziona jakas karta to ustala sie sile ukladu
    {
        system[st].mayValue += mayPlay[st][0].value;
        return 1;
    }

    else
        return 0;
}

//---------------SILA 3---------------//
int Player::checkSetDeep2(int st, char c, vector<Card> &check)                        //zwraca najwyzsza karte w danym kolorze
{
    //cout << "s3" << endl;
    for(int i=check.size()-1; i>=0; i--)
    {
        if(c == check[i].ch)               //pierwsza napotkana karta bedzie o najwzyszej wartosci ze wzgledu na ulozenie
            mayPlay[st].push_back(check[i]);
    }

    if(mayPlay[st].size() > 0)
    {
        system[st].mayValue += mayPlay[st][0].value;
        return 1;
    }

    else
        return 0;
}

//---------------SILA 2---------------//
int Player::checkSetDeep2(int st, int tempVmax, int tempVmin, vector<Card> &check)
{
    //cout << "s2" << endl;
    int c1;
    int *ptr1 = &c1;
    int c2;
    int *ptr2 = &c2;

    if(tempVmin+1 == tempVmax)  //karty kolo siebie
    {
        *ptr1 = tempVmax+1; //utworzenie szukanych kart
        *ptr1 = tempVmin-1; //--
    }

    else if(tempVmin+2 == tempVmax) //karty rozdzielone przerwa
    {
        *ptr1 = tempVmin+1; //
        *ptr1 = 10;       //utworzenie karty nie do zanlezienia
    }

    //c1.show();
    //c2.show();

    for(int i=check.size()-1; i>=0; i--)    //pierwsza napotkana karta bedzie o najwzyszej wartosci ze wzgledu na ulozenie
    {
        if((c1 == check[i].value) || (c2 == check[i].value))
            mayPlay[st].push_back(check[i]);
    }

    if(mayPlay[st].size() > 0)                      //jezeli zostala znaleziona jakas karta to ustala sie sile ukladu
    {
        system[st].mayValue += mayPlay[st][0].value;
        return 1;
    }

    else
        return 0;
}




//---------------SILA 1---------------//
int Player::checkSetDeep2(int st, vector<Card> &check)
{
    //cout << "s1" << endl;
    int val = 0;                       //utworzenie pomocniczej do przechowywania wartosci
    for(int i=0; i<check.size(); i++)
    {
        if(check[i].value > val)
            val = check[i].value;
    }
    system[st].mayValue += val;
    return val;
}


//*****---------- FUNKCJA checkSetDeep1 ----------*****//

//---------------SILA 5 ORAZ 2---------------//
int Player::checkSetDeep1(int st, int v, char c, vector<Card> &check)       //zwraca sume wartosci kart do strita w kolorze lub bez koloru dla c= 'x'
{
    //cout << "s5 v s2" << endl;
    Card tempPlus1 (0,'y');
    Card tempPlus2 (0,'y');
    Card tempMinus1 (0,'y');
    Card tempMinus2 (0,'y');

    if(c != 'x')                //strit w kolorze
    {
        for(int i=0; i<check.size(); i++)       //ustalanie kart sasiednich
        {
            if(check[i].ch == c)
            {
                if(check[i].value == v-2)
                    tempMinus2 = check[i];
                else if(check[i].value == v-1)
                    tempMinus1 = check[i];
                else if(check[i].value == v+1)
                    tempPlus1 = check[i];
                else if(check[i].value == v+2)
                    tempPlus2 = check[i];
            }
        }
    }

    else if(c == 'x')       //strit bez koloru
    {
        for(int i=0; i<check.size(); i++)       //ustalanie kart sasiednich
        {
            if(check[i].value == v-2)
                tempMinus2 = check[i];
            else if(check[i].value == v-1)
                tempMinus1 = check[i];
            else if(check[i].value == v+1)
                tempPlus1 = check[i];
            else if(check[i].value == v+2)
                tempPlus2 = check[i];
        }
    }

    //ustalanie ukladu od nasilniejszego do najslabszego
    if((tempPlus2.value != 0) && (tempPlus1.value != 0))
    {
       // system[st].mayValue += tempPlus2.value + tempPlus1.value;
        mayPlay[st].push_back(tempPlus2);
        mayPlay[st].push_back(tempPlus1);
        //cout << mayPlay[st][0] << " " << mayPlay[st][1];      //tester
    }

    if((tempPlus1.value != 0) && (tempMinus1.value != 0))
    {
      //  system[st].mayValue += tempPlus1.value + tempMinus1.value;
        mayPlay[st].push_back(tempPlus1);
        mayPlay[st].push_back(tempMinus1);
    }

    if((tempMinus1.value != 0) && (tempMinus2.value != 0))
    {
      //  system[st].mayValue += tempMinus1.value + tempMinus2.value;
        mayPlay[st].push_back(tempMinus1);
        mayPlay[st].push_back(tempMinus2);
    }

    vector<Card>::iterator a = unique(mayPlay[st].begin(), mayPlay[st].end());       //scala te same wartosci
    mayPlay[st].erase(a, mayPlay[st].end());                                         //zmniejsza wielkosc kontenera ze wzgledu na powtowki


    if(mayPlay[st].size() > 1)
    {
        system[st].mayValue += mayPlay[st][0].value + mayPlay[st][1].value;
        return 1;
    }

    else
        return 0;
}



//---------------SILA 4----------------//
int Player::checkSetDeep1(int st, int v, vector<Card> &check)           //zwraca sume wartosci 2 kart o tej samej wartosci
{
    //cout << "s4" << endl;
    vector<Card> temp;                    //liczy karty spelniajace warunek
    for(int i=0; i<check.size(); i++)
    {
        if(v == check[i].value)
        {
            temp.push_back(check[i]);
        }
    }

    if(temp.size() > 1)
    {
        for(int j=0; j<temp.size(); j++)
            mayPlay[st].push_back(temp[j]);
        system[st].mayValue += mayPlay[st][0].value + mayPlay[st][1].value;
        return 1;
    }

    else
        return 0;
}

//---------------SILA 3----------------//
int Player::checkSetDeep1(int st, char c, vector<Card> &check)
{
    //cout << "s3" << endl;
    int temp = 0;                           //zwraca kart o najwyzszej wartosci z tego samego koloru
    for(int i=check.size()-1; i>=1; i--)
    {
        if((c == check[i].ch) && (c == check[i-1].ch))  //dwie kolejne beda najwysze ze wzgledu na uloznie sprawdzania
        {
            mayPlay[st].push_back(check[i]);
            mayPlay[st].push_back(check[i-1]);
        }
    }

    vector<Card>::iterator a = unique(mayPlay[st].begin(), mayPlay[st].end());       //scala te same wartosci
    mayPlay[st].erase(a, mayPlay[st].end());                                         //zmniejsza wielkosc kontenera ze wzgledu na powtowki

    if(mayPlay[st].size() > 1)
    {
        system[st].mayValue += mayPlay[st][0].value + mayPlay[st][1].value;
        return 1;
    }

    else
        return 0;
}

//---------------SILA 1----------------//
int Player::checkSetDeep1(int st, vector<Card> &check)
{
    //cout << "s1" << endl;
    int tempA = check[0].value;//poczatkowa inicjalizacja zeby bylo do czego porownywac
    int tempB = check[1].value;//--

    for(int i=2; i<check.size(); i++)
    {
        if(check[i].value > tempA)
            tempA = check[i].value;
        else if(check[i].value > tempB)
            tempB = check[i].value;
    }
    system[st].mayValue += tempA + tempB;
    return 1;
}



//*****---------- FUNKCJA checkSetDeep0 ----------*****//

//---------------SILA 5---------------//
int Player::checkSetDeep0(int st, int v1, int v2, int v3, int v4, vector<Card> check)
{
    //cout << "s5" << endl;
    int tempV = 0;

    for(int j=check.size()-1; j>=2; j--)
    {
        if((((check[j].value) == (check[j-1].value+1)) && ((check[j-1].value+1) == (check[j-2].value+2))) &&
          (((check[j].value) + (check[j-1].value) + (check[j-2].value)) > tempV) &&
          (((check[j].ch) == (check[j-1].ch)) && ((check[j-1].ch) == (check[j-2].ch))))
            tempV = check[j].value + (check[j-1].value) + (check[j-2].value);
    }
    if(tempV > 0)
    {
        system[st].mayValue = tempV;
        return 1;
    }
    else
        return 0;
}

//---------------SILA 4---------------//
int Player::checkSetDeep0(int st, int v1, int v2, int v3, vector<Card> check)
{
    //cout << "s4" << endl;
    int max = 9;
    int counter = 0;

    for(int j=0; j<check.size(); j++)
    {
        if(check[j].value == max)
            counter++;
    }

    if(counter >= 3)      //jak jest set
    {
        system[st].mayValue = 3*max;
        return 1;
    }

    if(max == 1)
        return 0;

    max--;              //jezeli nie ma seta i sa nizsze karty to kolejna petla
}

//---------------SILA 3---------------//
int Player::checkSetDeep0(int st, int v1, int v2, vector<Card> check)
{
    //cout << "s3" << endl;
    int tempV = 0;

    for(int j=check.size()-1; j>=2; j--)
    {
        if((((check[j].value) + (check[j-1].value) + (check[j-2].value)) > tempV) &&
          ((check[j].ch) == (check[j-1].ch) == (check[j-2].ch)))
            tempV = check[j].value + (check[j-1].value) + (check[j-2].value);
    }

    if(tempV > 0)
    {
        system[st].mayValue = tempV;
        return 1;
    }

    else
        return 0;
}

//---------------SILA 2---------------//
int Player::checkSetDeep0(int st, int v1, vector<Card> check)
{
    //cout << "s2" << endl;
    int temp[9] = {0,0,0,0,0,0,0,0,0};

    for(int j=0; j<check.size(); j++)               //zapelnienie roznych wartosci w tabeli
        temp[check[j].value-1] = check[j].value;

    for(int j=8; j>=2; j--)
    {
        if((temp[j] > 0) && (temp[j-1] > 0) && (temp[j-2] > 0))
        {
            system[st].mayValue = temp[j]+temp[j-1]+temp[j-2];
            return 1;
        }
    }
    return 0;
}

//---------------SILA 1---------------//
int Player::checkSetDeep0(int st, vector<Card> check)
{
    //cout << "s1" << endl;
    int tempA = 0;
    int tempB = 0;
    int tempC = 0;

    for(int j=0; j<check.size(); j++)
    {
        if(check[j].value > tempA)
        {
            tempC = tempB;
            tempB = tempA;
            tempA = check[j].value;
        }
    }

    system[st].mayValue = tempA+tempB+tempC;
    return 1;
}
