#include "head.h"


//----------KONSTRUKTOR----------//
Player::Player(stack<Card> &stc, int m)
{
    if((m == 2) && (player == 2))
        name = "KOMPUTER";
    else
    {
        cout << "Podaj imie gracza nr " << player << ": ";
        cin >> name;
    }

    startHand(stc);                     //dobieranie pierwszej reki
    vector<vector<Card>> karty(S);      //dwuwymairowa tabela vector do kart zagranych
    played = karty;                     //
    mayPlay = karty;                    //do mozliwych do zagrania
    impAI = karty;
    order = player;                     //p1-1, p2-2
    player++;

    for(int i=0; i<S; i++)              //uklady kart
    {
        Set temp;
        system.push_back(temp);
    }
}


//----------DOBRANIE STARTOWEJ REKI----------//
void Player::startHand(stack<Card> & s)
{
    for(int i=0; i<H; i++)              //petla do dobierania startwej reki
    {
        hand.push_back(s.top());        //wartosc karty idzie do reki
        s.pop();                        //wierzchnia karta (dobrana przed chwila) schodzi ze stosu
    }

}


//----------ZAGRANIE KARTY----------//
void Player::play(vector<Card> &check, int *sc)

{
    int pickStone;  //wybor kamienia
    int pickCard;   //wybor karty
    char ch;        //pomocnicza do potwierdzenia
    int mis = 11;        //kolor bledu
    int play = 0;


    for(int i=0; i<S; i++)      //sprawdzanie czy jest gdzie dograc karte
        if((sc[i] == 0) && (played[i].size() < 3))
            play++;

    if(play > 0)    //jezeli mozna dograc
    {

        while(1)        //petla wyboru kamienia i karty
        {

            cout << "Wybierz kamien do ktorego kamienia chcesz dograc karte (podaj nr od 1 do 9): ";

            while(1)        //obsluga bledow wyboru kamienia
            {
                if(!(cin>>pickStone))
                    {cout << "Blad, "; color(mis); cout << "nie wybrales cyfry"; color(7); cout << ", wybierz jeszcze raz: ";}
                else if((pickStone < 1) || (pickStone > 9))
                    {cout << "Blad, "; color(mis); cout << "wybrales cyfre spoza zakresu"; color(7); cout << ", wybierz jeszcze raz: ";}
                else if(sc[pickStone-1] !=  0)
                    {cout << "Blad, "; color(mis); cout << "wybrales juz zdobyty kamien"; color(7); cout <<", wybierz jeszcze raz: ";}
                else if(played[pickStone-1].size() == 3)
                    {cout << "Blad, "; color(mis); cout << "masz juz przy kamieniu 3 karty"; color(7); cout << ", wybierz jeszcze raz: ";}
                else
                    break;

                cin.clear();            //kasowanie bledu strumienia
                cin.sync();             //kasowanie znakow z bufora
            }

            cout << "Wybierz karte ktora chcesz zagrac (podaj nr od 1 do 6): ";

            while(1)            //obsluga bledow wyboru karty
            {
                if(!(cin>>pickCard))
                    {cout << "Blad, "; color(mis); cout << "nie wybrales cyfry"; color(7); cout << ", wybierz jeszcze raz: ";}
                else if((pickCard < 1) || (pickCard > hand.size()))
                    {cout << "Blad, "; color(mis); cout << "wybrales cyfre spoza zakresu"; color(7); cout << ", wybierz jeszcze raz: ";}
                else
                    break;

                cin.clear();            //kasowanie bledu strumienia
                cin.sync();             //kasowanie znakow z bufora
            }

            while(1)
            {
                cout << "Czy na pewno chcesz zagrac karte" << hand[pickCard-1] << " do kamienia ";
                color(8);
                cout << "*" << pickStone << "*";
                color(7);
                cout << " (t-tak, n-nie): ";

                cin >> ch;
                if((ch == 'n') || (ch == 't'))
                    break;
                else
                {
                    cout << "Blad, wybierz jeszcze raz!" << endl;
                    cin.clear();            //kasowanie bledu strumienia
                    cin.sync();             //kasowanie znakow z bufora
                }

            }
            if(ch == 't')
                break;                  //opuszczenie petli
            else if(ch == 'n')
                continue;               //jeszcze raz wybor zagrania
        }

        cin.clear();            //kasowanie bledu strumienia
        cin.sync();             //kasowanie znakow z bufora

        Card tempC = hand[pickCard-1];              //zapis wartosci zagranej karty
        hand.erase(hand.begin()+pickCard-1);        //usuniecie zagranej karty z reki

        for(int i=0; i<check.size(); i++)           //usuniecie karty ze stosu sprawdzania
        {
            if(check[i] == tempC)
                check.erase(check.begin()+i);
        }
        //cout << "Usuwam karte: " << karta << endl;          //tester

        tempC.current = 1;                          //pokazuje ostatnio zagrana karte
        played[pickStone-1].push_back(tempC);         //dokladanie karty do kamienia

    }
}


//----------LOSOWANIE KARTY DO ZAGRANIA----------//
void Player::playRandom(vector<Card> &check, int *sc)
{
    srand(time(NULL));
    int pickCard = rand()%hand.size();      //losowanie karty moze byc mniej niz 6 kart
    int pickStone = rand()%9;               //losowanie kamienia
    vector<int> temp;
    int play = 0;


    for(int i=0; i<S; i++)      //jest gdzie dograc karte
        if((sc[i] == 0) && (played[i].size() < 3))
            play++;

    if(play > 0)
    {


    for(int i=0; i<S; i++)
    {
        if((played[i].size() == 0) && (sc[i] == 0))
            temp.push_back(i);
    }

    if(temp.size() > 0)
        pickStone = temp[rand()%temp.size()];


    while(1)                        //losowanie dopoki nie zostany wylosowany kamien do ktorego mozna dograc karte
    {
        if((sc[pickStone] != 0) || (played[pickStone].size() == 3))
            pickStone = rand()%9;
        else
            break;
    }

    Card tempC = hand[pickCard];          //zapis wartosci zagranej karty
    hand.erase(hand.begin()+pickCard);    //usuniecie zagranej karty z reki

    for(int i=0; i<check.size(); i++)     //usuniecie karty ze stosu sprawdzania
    {
        if(check[i] == tempC)
            check.erase(check.begin()+i);
    }

   // cout << "Usuwam karte: " << karta << endl;          //tester

    tempC.current = 1;                          //pokazuje ostatnio zagrana karte
    played[pickStone].push_back(tempC);         //dokladanie karty do kamienia
    }
}


//----------ZAGRANIE KARTY AI----------//
void Player::playAI(vector<Card> &check, int *sc)
{
    int play = 0;           //brak zagrania

    for(int s=0; s<S; s++)  //petla wokol kamieni
    {
        if(sc[s] != 0)      //nie mozna dogrywac do kamieni juz przejetych
            continue;

        if(play == 1)       //jezeli bylo zagranie to przerwij
            break;

        for(int i=0; i<mayPlay[s].size(); i++)
        {
            if(play == 1)
                break;

            for(int k=0; k<H; k++)
            {
                if(play == 1)
                    break;

                if(hand[k] == mayPlay[s][i])
                {
                    play = 1;

                    Card tempC = hand[k];
                    hand.erase(hand.begin()+k);

                    for(int w=0; w<check.size(); w++)
                    {
                        if(check[w] == tempC)
                            check.erase(check.begin()+w);
                    }
                    tempC.current = 1;                          //pokazuje ostatnio zagrana karte
                    played[s].push_back(tempC);
                    break;
                }
            }

        }
        //AI improve
        for(int i=0; i<impAI[s].size(); i++)
        {
            if(play == 1)
                break;

            for(int k=0; k<H; k++)
            {
                if(play == 1)
                    break;

                if(hand[k] == impAI[s][i])
                {
                    play = 1;

                    Card tempC = hand[k];
                    hand.erase(hand.begin()+k);

                    for(int w=0; w<check.size(); w++)
                    {
                        if(check[w] == tempC)
                            check.erase(check.begin()+w);
                    }
                    tempC.current = 1;                          //pokazuje ostatnio zagrana karte
                    played[s].push_back(tempC);
                    break;
                }
            }

        }


    }

    if(play == 0)                   //jezeli nie bylo zagrania losuj karte
        playRandom(check, sc);
}


//----------DOBIERANIE KARTY----------//
void Player::draw(stack<Card> &stc)
{
    if(stc.size() > 0)                        //jezlei nie ma kart to juz nie dobierasz
    {
        cout << "Dobrales: " << stc.top() << endl;
        hand.push_back(stc.top());
        stc.pop();
    }
    //cout << "Reka: ";
    //for(int i=0; i<H; i++)
    //    cout << hand[i] << " ";
}


//----------POKAZANIE REKI----------//
void Player::showHand()
{
    cout << "Teraz gra: " << name << endl;
    cout << "Reka: ";
    for(int i=0; i<hand.size(); i++)
        cout << hand[i] << " ";
    cout << endl << endl;
}


//----------SPRAWDZANIE ZWYCIESTWA----------//
int Player::win(int *sc)
{
    int tempCount = 0;          //liczy kamienie zdobyte przez gracza
    int tempLine = 0;

    for(int i=0; i<S; i++)
    {
        if(sc[i] == order)
        {
            tempCount++;        //zawsze kamien liczony do sumy
            tempLine++;         //jezeli w ciagu to liczy sie do linii
        }
        else
            tempLine = 0;       //jezeli jest przerwa to linia sie lamie

        if((tempCount == 5) || (tempLine == 3))
        {
            cin.clear();    //usuwanie bledow
            cin.sync();     //czyszczenie bufora
            counterC = 0;   //ustawianie danych statycznych na startowe
            num = 1;        //--
            mark = 'a';     //--
            player = 1;     //--

            cout << "\n\n\nGratuluje zwyciezyl " << name << "!!!" << endl << endl;
            return 1;
        }
    }
    return 0;
}
