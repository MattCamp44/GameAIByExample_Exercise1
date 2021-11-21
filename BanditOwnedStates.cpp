//
// Created by mattc on 11/19/2021.
//

#include "BanditOwnedStates.h"
#include <iostream>
#include "Locations.h"
#include "Bandit.h"
#include "EntityNames.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"


using std::cout;

QuenchThirst* QuenchThirst::Instance()
{
    static QuenchThirst instance;

    return &instance;
}

void QuenchThirst::Enter(Bandit* pBandit)
{
    if (pBandit->Location() != saloon)
    {
        pBandit->ChangeLocation(saloon);

        cout << "\n" << GetNameOfEntity(pBandit->ID()) << ": " << "Boy, ah sure is thusty! Walking to the saloon";
    }
}


void QuenchThirst::Execute(Bandit *pBandit) {

    pBandit->BuyAndDrinkWhiskey();

    cout << "\n" << GetNameOfEntity(pBandit->ID()) << ":" << "Yess, nice Whiskey";

    //TODO:Define next state
    if( pBandit->DrunknessLevel() >= alcoolResistence )
        pBandit->GetFSM()->ChangeState(WanderAroundLookingForBob::Instance());



}


void QuenchThirst::Exit(Bandit *pBandit) {


    cout << "\n" << GetNameOfEntity(pBandit->ID()) << "Well, too drunk to drink some more, going out of the saloon";


}

bool QuenchThirst::OnMessage(Bandit *agent, const Telegram &msg) {

    return false;


}



WanderAroundLookingForBob* WanderAroundLookingForBob::Instance() {

    static WanderAroundLookingForBob instance;

    return &instance;


}


void WanderAroundLookingForBob::Enter(Bandit *pBandit) {


    cout << "\n" << GetNameOfEntity(pBandit->ID()) << "Where the hell is Bob? Surely I can \"borrow\" some money from him...";


}

void WanderAroundLookingForBob::Execute(Bandit *pBandit) {

    pBandit->DecreaseDrunknessLevel();

    if( pBandit->IsSober() && pBandit->GoldCarried() > 0 ){

        pBandit->GetFSM()->ChangeState(QuenchThirstBandit::Instance());

        return;



    }

    //Go to random location
    pBandit->ChangeLocation(static_cast<location_type>(rand() % (lastElement - 1)));

    Dispatch->DispatchMessageA(SEND_MSG_IMMEDIATELY, //time delay
                              pBandit->ID(),        //ID of sender
                              ent_Miner_Bob,            //ID of recipient
                              Msg_FightMe,   //the message
                              (void*)pBandit->Location());



}