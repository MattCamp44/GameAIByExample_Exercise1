//
// Created by mattc on 11/19/2021.
//

#ifndef GAMEAIBYEXAMPLE_EXERCISE1_BANDITOWNEDSTATES_H
#define GAMEAIBYEXAMPLE_EXERCISE1_BANDITOWNEDSTATES_H

#include "State.h"


class Bandit;
struct Telegram;


class QuenchThirstBandit : public State<Bandit>{

private:

    QuenchThirstBandit(){}

    QuenchThirstBandit(const QuenchThirstBandit&);
    QuenchThirstBandit& operator=(const QuenchThirstBandit&);

public:

    static QuenchThirstBandit* Instance();

    virtual void Enter(Bandit* pBandit);

    virtual void Execute(Bandit* pBandit);

    virtual void Exit(Bandit* pBandit);

    virtual bool OnMessage(Bandit* agent, const Telegram& msg);




};



class WanderAroundLookingForBob: public State<Bandit>{

private:

    WanderAroundLookingForBob() = default;

    WanderAroundLookingForBob(const WanderAroundLookingForBob&);
    WanderAroundLookingForBob& operator=(const WanderAroundLookingForBob&);

public:

    static WanderAroundLookingForBob* Instance();

    virtual void Enter(Bandit* pBandit);

    virtual void Execute(Bandit* pBandit);

    virtual void Exit(Bandit* pBandit);

    virtual bool OnMessage(Bandit* agent, const Telegram& msg);




};



class BanditGlobalState: public State<Bandit>{

private:

    BanditGlobalState(){};

    BanditGlobalState(const BanditGlobalState&);
    BanditGlobalState& operator=(const BanditGlobalState&);

public:

    static BanditGlobalState* Instance();

    virtual void Enter(Bandit* pBandit);

    virtual void Execute(Bandit* pBandit);

    virtual void Exit(Bandit* pBandit);

    virtual bool OnMessage(Bandit* agent, const Telegram& msg);


};


#endif //GAMEAIBYEXAMPLE_EXERCISE1_BANDITOWNEDSTATES_H
