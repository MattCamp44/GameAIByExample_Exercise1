//
// Created by mattc on 11/19/2021.
//

#ifndef GAMEAIBYEXAMPLE_EXERCISE1_BANDIT_H
#define GAMEAIBYEXAMPLE_EXERCISE1_BANDIT_H


#include "BaseGameEntity.h"
#include "StateMachine.h"
#include "Locations.h"
#include "BanditOwnedStates.h"

struct Telegram;

//Drunkness level before bandit starts to wander around
const int alcoolResistence = 10;

class Bandit : public BaseGameEntity{

private:

    StateMachine<Bandit>* m_pStateMachine;

    location_type m_Location;

    location_type m_NextLocation;

    bool m_LocationUpdated;

    int m_idrunknessLevel;

    int m_iGoldCarried;

public:

    Bandit(int id): m_Location(saloon),
                    m_idrunknessLevel(0),
                    m_iGoldCarried(20),
                    BaseGameEntity(id),
                    m_LocationUpdated(false)
    {

        m_pStateMachine = new StateMachine<Bandit>(this);

        //TODO: set initial state Bandit
        m_pStateMachine ->SetCurrentState(QuenchThirstBandit::Instance());
        m_pStateMachine->SetGlobalState(BanditGlobalState::Instance());

    }

    ~Bandit(){ delete m_pStateMachine; }

    void Update();

    void UpdateStateAndLocation();

    virtual bool HandleMessage(const Telegram& msg);

    StateMachine<Bandit>* GetFSM()const{return m_pStateMachine;}

    //-------------------------------------------------------------accessors

    location_type Location()const{ return m_Location; }
    void ChangeLocation( location_type loc ){ m_NextLocation = loc; m_LocationUpdated=true; }

    int DrunknessLevel()const{ return m_idrunknessLevel; }

    int GoldCarried()const{ return m_iGoldCarried; }
    void SetGoldCarried(int we){ m_iGoldCarried = we; }
    void AddToGoldCarried( int we ){ m_iGoldCarried += we; }

    void BuyAndDrinkWhiskey(){ m_idrunknessLevel++; m_iGoldCarried -= 2; }

    void DecreaseDrunknessLevel(){ m_idrunknessLevel--; }
    bool IsSober(){ return m_idrunknessLevel<=0; }


};


#endif //GAMEAIBYEXAMPLE_EXERCISE1_BANDIT_H
