//
// Created by mattc on 11/19/2021.
//

#include "MinerOwnedStates.h"
#include "State.h"
#include "Miner.h"
#include "Locations.h"
#include "Telegram.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "CrudeTimer.h"
#include "EntityNames.h"
#include "BanditOwnedStates.h"
#include<memory>

#include <iostream>
using std::cout;
using std::shared_ptr;

#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif


//------------------------------------------------------------------------methods for EnterMineAndDigForNugget
EnterMineAndDigForNugget* EnterMineAndDigForNugget::Instance()
{
    static EnterMineAndDigForNugget instance;

    return &instance;
}


void EnterMineAndDigForNugget::Enter(Miner* pMiner)
{
    //if the miner is not already located at the goldmine, he must
    //change location to the gold mine
    if (pMiner->Location() != goldmine)
    {
        cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Walkin' to the goldmine";

        pMiner->ChangeLocation(goldmine);
    }
}


void EnterMineAndDigForNugget::Execute(Miner* pMiner)
{
    //Now the miner is at the goldmine he digs for gold until he
    //is carrying in excess of MaxNuggets. If he gets thirsty during
    //his digging he packs up work for a while and changes state to
    //gp to the saloon for a whiskey.
    pMiner->AddToGoldCarried(1);

    pMiner->IncreaseFatigue();

    cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Pickin' up a nugget";

    //if enough gold mined, go and put it in the bank
    if (pMiner->PocketsFull())
    {
        pMiner->GetFSM()->ChangeState(VisitBankAndDepositGold::Instance());
    }

    if (pMiner->Thirsty())
    {
        pMiner->GetFSM()->ChangeState(QuenchThirst::Instance());
    }
}


void EnterMineAndDigForNugget::Exit(Miner* pMiner)
{
    cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": "
         << "Ah'm leavin' the goldmine with mah pockets full o' sweet gold";
}


bool EnterMineAndDigForNugget::OnMessage(Miner* pMiner, const Telegram& msg)
{
    //send msg to global message handler
    return false;
}

//------------------------------------------------------------------------methods for VisitBankAndDepositGold

VisitBankAndDepositGold* VisitBankAndDepositGold::Instance()
{
    static VisitBankAndDepositGold instance;

    return &instance;
}

void VisitBankAndDepositGold::Enter(Miner* pMiner)
{
    //on entry the miner makes sure he is located at the bank
    if (pMiner->Location() != bank)
    {
        cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Goin' to the bank. Yes siree";

        pMiner->ChangeLocation(bank);
    }
}


void VisitBankAndDepositGold::Execute(Miner* pMiner)
{
    //deposit the gold
    pMiner->AddToWealth(pMiner->GoldCarried());

    pMiner->SetGoldCarried(0);

    cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": "
         << "Depositing gold. Total savings now: "<< pMiner->Wealth();

    //wealthy enough to have a well earned rest?
    if (pMiner->Wealth() >= ComfortLevel)
    {
        cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": "
             << "WooHoo! Rich enough for now. Back home to mah li'lle lady";

        pMiner->GetFSM()->ChangeState(GoHomeAndSleepTilRested::Instance());
    }

        //otherwise get more gold
    else
    {
        pMiner->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance());
    }
}


void VisitBankAndDepositGold::Exit(Miner* pMiner)
{
    cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Leavin' the bank";
}


bool VisitBankAndDepositGold::OnMessage(Miner* pMiner, const Telegram& msg)
{
    //send msg to global message handler
    return false;
}
//------------------------------------------------------------------------methods for GoHomeAndSleepTilRested

GoHomeAndSleepTilRested* GoHomeAndSleepTilRested::Instance()
{
    static GoHomeAndSleepTilRested instance;

    return &instance;
}

void GoHomeAndSleepTilRested::Enter(Miner* pMiner)
{
    if (pMiner->Location() != shack)
    {
        cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Walkin' home";

        pMiner->ChangeLocation(shack);

        //let the wife know I'm home
        Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, //time delay
                                  pMiner->ID(),        //ID of sender
                                  ent_Elsa,            //ID of recipient
                                  Msg_HiHoneyImHome,   //the message
                                  NO_ADDITIONAL_INFO);
    }
}

void GoHomeAndSleepTilRested::Execute(Miner* pMiner)
{
    //if miner is not fatigued start to dig for nuggets again.
    if (!pMiner->Fatigued())
    {
        cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": "
             << "All mah fatigue has drained away. Time to find more gold!";

        pMiner->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance());
    }

    else
    {
        //sleep
        pMiner->DecreaseFatigue();

        cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "ZZZZ... ";
    }
}

void GoHomeAndSleepTilRested::Exit(Miner* pMiner)
{
}


bool GoHomeAndSleepTilRested::OnMessage(Miner* pMiner, const Telegram& msg)
{
//    SetTextColor(BACKGROUND_RED|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);

    switch(msg.Msg)
    {
        case Msg_StewReady:

            cout << "\nMessage handled by " << GetNameOfEntity(pMiner->ID())
                 << " at time: " << Clock->GetCurrentTimeCrudeTimer();

//            SetTextColor(FOREGROUND_RED|FOREGROUND_INTENSITY);

            cout << "\n" << GetNameOfEntity(pMiner->ID())
                 << ": Okay Hun, ahm a comin'!";

            pMiner->GetFSM()->ChangeState(EatStew::Instance());

            return true;

    }//end switch

    return false; //send message to global message handler
}

//------------------------------------------------------------------------QuenchThirst

QuenchThirst* QuenchThirst::Instance()
{
    static QuenchThirst instance;

    return &instance;
}



void QuenchThirst::Enter(Miner* pMiner)
{
    if (pMiner->Location() != saloon)
    {
        pMiner->ChangeLocation(saloon);

        cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Boy, ah sure is thusty! Walking to the saloon";
    }
}

void QuenchThirst::Execute(Miner* pMiner)
{
    pMiner->BuyAndDrinkAWhiskey();

    cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "That's mighty fine sippin' liquer";

    pMiner->GetFSM()->ChangeState(EnterMineAndDigForNugget::Instance());
}


void QuenchThirst::Exit(Miner* pMiner)
{
    cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Leaving the saloon, feelin' good";
}


bool QuenchThirst::OnMessage(Miner* pMiner, const Telegram& msg)
{
    //send msg to global message handler
    return false;
}

//------------------------------------------------------------------------EatStew

EatStew* EatStew::Instance()
{
    static EatStew instance;

    return &instance;
}


void EatStew::Enter(Miner* pMiner)
{
    cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Smells Reaaal goood Elsa!";
}

void EatStew::Execute(Miner* pMiner)
{
    cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Tastes real good too!";

    pMiner->GetFSM()->RevertToPreviousState();
}

void EatStew::Exit(Miner* pMiner)
{
    cout << "\n" << GetNameOfEntity(pMiner->ID()) << ": " << "Thankya li'lle lady. Ah better get back to whatever ah wuz doin'";
}


bool EatStew::OnMessage(Miner* pMiner, const Telegram& msg)
{
    //send msg to global message handler
    return false;
}


MinerGlobalState *MinerGlobalState::Instance() {

    static MinerGlobalState instance;

    return &instance;


}

void MinerGlobalState::Enter(Miner *miner) {



}

void MinerGlobalState::Execute(Miner *miner) {

}

void MinerGlobalState::Exit(Miner *miner) {

}

bool MinerGlobalState::OnMessage(Miner *agent, const Telegram &msg) {


    //cout << "\n" << GetNameOfEntity(agent->ID()) << ": " << " Message received, My location is " << GetLocationName(agent->Location());

    switch(msg.Msg){

        case Msg_FightMe:
        {

            cout << "\n" << GetNameOfEntity(agent->ID()) << ": " << " Message received, My location is " << GetLocationName(agent->Location());

            //Ignore message if sleeping
            if( agent->GetFSM()->GetCurrentState() == GoHomeAndSleepTilRested::Instance()  ) return true;

            //TODO: This might not work
            //Check if miner and bandit are in the same location
            if( DereferenceToType<FightRequestData>(msg.ExtraInfo).location != agent->Location() ) return true;

            cout << "\nMessage handled by " << GetNameOfEntity(agent->ID()) << " at time: "
                 << Clock->GetCurrentTimeCrudeTimer();


            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

            CONSOLE_SCREEN_BUFFER_INFO csbiInfo;

            GetConsoleScreenBufferInfo(hConsole, &csbiInfo);

            WORD wOldColorAttrs;

            wOldColorAttrs = csbiInfo.wAttributes;

            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN|FOREGROUND_INTENSITY);


            cout << "\n" << GetNameOfEntity(agent->ID()) <<
                 ": Aha! Wanna fight?";

            SetConsoleTextAttribute(hConsole, wOldColorAttrs );


            if( agent->GoldCarried() <= 0 ){

                cout << "\n" << GetNameOfEntity(agent->ID()) << ": " << " Sorry man, no money here ";

                shared_ptr<FightOutcomeData> outcomedata(new FightOutcomeData(no_money,0));

                //TODO:This might not work
                Dispatch->DispatchMessageA(SEND_MSG_IMMEDIATELY, //time delay
                                           agent->ID(),        //ID of sender
                                           ent_Bandit,            //ID of recipient
                                           Msg_FightOutcome,   //the message
                                           (void*) outcomedata.get());

                return true;

            }


            if( agent->FatiguedToFight() ){

                shared_ptr<FightOutcomeData> outcomedata(new FightOutcomeData(bandit_wins,agent->GoldCarried()));

                //TODO:This might not work
                Dispatch->DispatchMessageA(SEND_MSG_IMMEDIATELY, //time delay
                                           agent->ID(),        //ID of sender
                                           ent_Bandit,            //ID of recipient
                                           Msg_FightOutcome,   //the message
                                           (void*) outcomedata.get());

                cout << "\n" << GetNameOfEntity(agent->ID()) << ": " << " Ouch! I lost all my money! I lost " << agent->GoldCarried();


                agent->SetGoldCarried(0);






            }
            else{

                shared_ptr<FightOutcomeData> outcomedata(new FightOutcomeData(miner_wins,0));

                Dispatch->DispatchMessageA(SEND_MSG_IMMEDIATELY, //time delay
                                           agent->ID(),        //ID of sender
                                           ent_Bandit,            //ID of recipient
                                           Msg_FightOutcome,   //the message
                                           (void*)outcomedata.get());


                agent->SetGoldCarried( agent->GoldCarried() + DereferenceToType<FightRequestData>(msg.ExtraInfo).moneycarried );

                cout << "\n" << GetNameOfEntity(agent->ID()) << ": " << " Nice try bandit! Now I get all your money! I got from you: " << DereferenceToType<FightRequestData>(msg.ExtraInfo).moneycarried;
            }


            SetConsoleTextAttribute(hConsole, wOldColorAttrs );

            return true;

        }


        return true;

    }

    return false;




}
