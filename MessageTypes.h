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
    bandit_wins

};


inline std::string MsgToStr(int msg)
{
    switch (msg)
    {
        case 1:

            return "HiHoneyImHome";

        case 2:

            return "StewReady";

        default:

            return "Not recognized!";
    }
}

#endif //GAMEAIBYEXAMPLE_EXERCISE1_MESSAGETYPES_H
