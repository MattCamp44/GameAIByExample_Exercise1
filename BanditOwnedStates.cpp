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
#include <memory>
#include<string>

#define DEBUG_BANDIT


using std::cout;
using std::shared_ptr;

QuenchThirstBandit* QuenchThirstBandit::Instance()
{
    static QuenchThirstBandit instance;

    return &instance;
}

void QuenchThirstBandit::Enter(Bandit* pBandit)
{
    if (pBandit->Location() != saloon)
    {
        pBandit->ChangeLocation(saloon);

        cout << "\n" << GetNameOfEntity(pBandit->ID()) << ": " << "Boy, ah sure is thusty! Walking to the saloon";
    }
}


void QuenchThirstBandit::Execute(Bandit *pBandit) {

    if( pBandit->GoldCarried() <= 2 ){

        cout << "\n" << GetNameOfEntity(pBandit->ID()) << ":" << "Damn, out of money!";

        pBandit->GetFSM()->ChangeState(WanderAroundLookingForBob::Instance());

        return ;

    }

    //TODO:Define next state
    if( pBandit->DrunknessLevel() >= alcoolResistence ){

        cout << "\n" << GetNameOfEntity(pBandit->ID()) << ":" << " Well, too drunk to drink some more";

        pBandit->GetFSM()->ChangeState(WanderAroundLookingForBob::Instance());

        return;
    }


    pBandit->BuyAndDrinkWhiskey();

    cout << "\n" << GetNameOfEntity(pBandit->ID()) << ":" << "Yess, nice Whiskey";






}


void QuenchThirstBandit::Exit(Bandit *pBandit) {


    cout << "\n" << GetNameOfEntity(pBandit->ID()) << " Going out of the saloon";


}

bool QuenchThirstBandit::OnMessage(Bandit *agent, const Telegram &msg) {

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

    if( pBandit->IsSober() && pBandit->GoldCarried() >= 2 ){


        cout << "\n"  << GetNameOfEntity(pBandit->ID()) <<  ": Too sober... going back to the saloon!";

        pBandit->GetFSM()->ChangeState(QuenchThirstBandit::Instance());

        return;



    }

    cout << "\n"  << GetNameOfEntity(pBandit->ID()) << " Looking for Bob at the " << GetLocationName(pBandit->Location());

#ifndef DEBUG_BANDIT

    //Go to random location
    pBandit->ChangeLocation(static_cast<location_type>(rand() % (lastElement - 1)));


#endif

#ifdef DEBUG_BANDIT

    pBandit->ChangeLocation(goldmine);

#endif



    shared_ptr<FightRequestData> requestData(new FightRequestData(pBandit->Location(), pBandit->GoldCarried()));

    //TODO:This might not work, smart pointers?
    //Send fight message with current bandit location
    //Sends a message each cycle!
    Dispatch->DispatchMessageA(SEND_MSG_IMMEDIATELY, //time delay
                              pBandit->ID(),        //ID of sender
                              ent_Miner_Bob,            //ID of recipient
                              Msg_FightMe,   //the message
                              (void*) requestData.get());



}

void WanderAroundLookingForBob::Exit(Bandit *pBandit) {

}


bool WanderAroundLookingForBob::OnMessage(Bandit *agent, const Telegram &msg) {

    return false;

}

BanditGlobalState *BanditGlobalState::Instance() {

    static BanditGlobalState instance;

    return &instance;


}

void BanditGlobalState::Enter(Bandit *pBandit) {

}

void BanditGlobalState::Execute(Bandit *pBandit) {

}

void BanditGlobalState::Exit(Bandit *pBandit) {

}

bool BanditGlobalState::OnMessage(Bandit *agent, const Telegram &msg) {

    switch (msg.Msg) {

        cout<< "\n" << "Found you!";

        case Msg_FightOutcome: {

            if( DereferenceToType<FightOutcomeData>(msg.ExtraInfo).outcome == no_money  ){

                cout << "\n" << GetNameOfEntity(agent->ID()) << ": " << " No point in fighting you... you have no money ";

                return true;

            }

            if(DereferenceToType<FightOutcomeData>(msg.ExtraInfo).outcome == miner_wins ){

                cout << "\n" << GetNameOfEntity(agent->ID()) << ": " << " Ouch! I lost all my money! I lost " << agent->GoldCarried();

                agent->SetGoldCarried(0);

            }
            else{

                cout << "\n" << GetNameOfEntity(agent->ID()) << ": " << " Aha! I win! Back to the saloon! I get from you " << DereferenceToType<FightOutcomeData>(msg.ExtraInfo).moneycarried;

                agent->SetGoldCarried( agent->GoldCarried() + DereferenceToType<FightOutcomeData>(msg.ExtraInfo).moneycarried );

                agent->GetFSM()->ChangeState(QuenchThirstBandit::Instance());

            }


            return true;


        }

    return true;


    }


    return false;
}
