#include "head.h"

using namespace std;

//----------ZMIENNE----------//
Card cardSetup[K];              //utworzenie talii kart
Card *ptrCardSetup = cardSetup; //wskaznik do utworzonej talii kart
stack<Card> cardStack;          //pusty stos na karty
vector<Card> cardCheck;         //stos do sprawdzania ukladu
int stoneCondition [9];         //tablica stanu kamieni, pocztakowa wartosc 0-niczyj
int *ptrSC = stoneCondition;    //wskaznik na stan kamieni
Player *ptrPlayer = nullptr;    //wskaznik na gracza, poczatkowo nieuzywany
Player *ptrPlayer2nd = nullptr; //wskaznika na drugiego gracza, poczatkowo nieuzywany
int mode;                       //przechowuje tryb ryzgrywki


int main()
{
    //----------SETUP----------//
    introduce();                            //wstepny tekst
    mode = gameMode();                      //ustawia tryb rozgrywki

    while(mode != 3) //3 == koniec programu
    {
    startCheck(cardCheck, ptrCardSetup);    //tworzenie stosu do sprawdzania
    randomCards(ptrCardSetup);              //tasowanie kart
    stackStart(cardStack, ptrCardSetup);    //tworzenie stosu kart

    Player p1(cardStack, mode);             //utworzenie graczy
    Player p2(cardStack, mode);             //utworzenie drugiego gracz

    ptrPlayer = randomPlayer(p1, p2);       //ustawia pierwszego gracza
    ptrPlayer2nd = secondPlayer(p1, p2);    //ustawia drugiego gracza


    //----------GAME----------//
        while(1)
        {
        check(ptrPlayer, ptrPlayer2nd, stoneCondition);     //sprawdzanie kamieni
        show(p1, p2, ptrSC);                                //pokazanie planszy

        if(ptrPlayer->win(ptrSC))                           //sprawdzanie czy gracz wygral
            break;
        ptrPlayer->showHand();                              //pokazanie reki
      //  showOuts(p1, p2);                                   //pokazaniu outow

        if(mode == 1)                                       //gra dwuosobowa
            ptrPlayer->play(cardCheck, ptrSC);

        else if(mode == 2)                                  //gra z komputerem
            if(ptrPlayer == &p1)
                ptrPlayer->play(cardCheck, ptrSC);
         else
                ptrPlayer->playAI(cardCheck, ptrSC);


        ptrPlayer->draw(cardStack);                         //dobranie karty
        ptrPlayer->checkSetMain(cardCheck, mode);           //aktualizacja sily ukladow

            if(ptrPlayer == &p1)                            //zamiana wsakznikow
                {ptrPlayer = &p2; ptrPlayer2nd = &p1;}

            else if(ptrPlayer == &p2)
                {ptrPlayer = &p1; ptrPlayer2nd = &p2;}
        }

    //przygotowanie do nowej gry
    mode = gameMode();                                          //ustawia tryb rozgrywki
    for(int i=cardStack.size()-1; i>=0; i--) cardStack.pop();   //czyszczenie stosu kart
    cardCheck.clear();                                          //czyszczenie stosu sprawdzania
    for(int i=0; i<S; i++) ptrSC[i] = 0;                        //zerowanie stanow kamienii
    ptrPlayer = nullptr;                                        //ustawienie wskaznikow dla graczy na null
    ptrPlayer2nd = nullptr;                                     //--
    }

    cout << endl << "Koniec programu." << endl;
    getch();        //odpalanie progamu z exe
}

