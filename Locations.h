//
// Created by mattc on 11/19/2021.
//

#ifndef GAMEAIBYEXAMPLE_EXERCISE1_LOCATIONS_H
#define GAMEAIBYEXAMPLE_EXERCISE1_LOCATIONS_H




enum location_type
{
    shack,
    goldmine,
    bank,
    saloon,
    lastElement
};

//Get the number of defined locations
constexpr int numberOfLocations = static_cast<int>(location_type::lastElement);


//uncomment this to send the output to a text file
//#define TEXTOUTPUT




#endif //GAMEAIBYEXAMPLE_EXERCISE1_LOCATIONS_H
