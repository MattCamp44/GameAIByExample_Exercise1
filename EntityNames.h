//
// Created by mattc on 11/19/2021.
//

#ifndef GAMEAIBYEXAMPLE_EXERCISE1_ENTITYNAMES_H
#define GAMEAIBYEXAMPLE_EXERCISE1_ENTITYNAMES_H

#include <string>

enum
{
    ent_Miner_Bob,

    ent_Elsa
};

inline std::string GetNameOfEntity(int n)
{
    switch(n)
    {
        case ent_Miner_Bob:

            return "Miner Bob";

        case ent_Elsa:

            return "Elsa";

        default:

            return "UNKNOWN!";
    }
}




#endif //GAMEAIBYEXAMPLE_EXERCISE1_ENTITYNAMES_H
