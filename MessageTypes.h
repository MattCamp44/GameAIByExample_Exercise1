//
// Created by mattc on 11/19/2021.
//

#ifndef GAMEAIBYEXAMPLE_EXERCISE1_MESSAGETYPES_H
#define GAMEAIBYEXAMPLE_EXERCISE1_MESSAGETYPES_H


#include <string>





enum message_type
{
    Msg_HiHoneyImHome,
    Msg_StewReady,
    Msg_FightMe,
    Msg_FightOutcome,
};


enum fight_outcome{

    miner_wins,
    bandit_wins,
    no_money

};

struct FightOutcomeData {

    fight_outcome outcome;
    int moneycarried;

    FightOutcomeData( fight_outcome o , int m ): outcome(o),
                                                moneycarried(m)
    {}


};


struct FightRequestData{

    location_type location;
    int moneycarried;

    FightRequestData(location_type l, int m): location(l),
                                            moneycarried(m)
    {}


};


inline std::string MsgToStr(int msg)
{
    switch (msg)
    {
        case Msg_HiHoneyImHome:

            return "HiHoneyImHome";

        case Msg_StewReady:

            return "StewReady";

        case Msg_FightMe:

            return "FightMe";

        case Msg_FightOutcome:

            return "FightOutcome";

        default:

            return "Not recognized!";
    }
}

#endif //GAMEAIBYEXAMPLE_EXERCISE1_MESSAGETYPES_H
