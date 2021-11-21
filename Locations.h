//
// Created by mattc on 11/19/2021.
//

#ifndef GAMEAIBYEXAMPLE_EXERCISE1_LOCATIONS_H
#define GAMEAIBYEXAMPLE_EXERCISE1_LOCATIONS_H

#include<string>

using std::string;


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


inline string GetLocationName(int l){

    switch( l ){

        case shack: return "Shack";
        case goldmine: return "Goldmine";
        case bank: return "Bank";
        case saloon: return "Saloon";
        default: return "Location not recognized";



    }


}



//uncomment this to send the output to a text file
//#define TEXTOUTPUT




#endif //GAMEAIBYEXAMPLE_EXERCISE1_LOCATIONS_H
