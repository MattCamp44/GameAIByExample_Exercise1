//
// Created by mattc on 11/19/2021.
//

#ifndef GAMEAIBYEXAMPLE_EXERCISE1_CRUDETIMER_H
#define GAMEAIBYEXAMPLE_EXERCISE1_CRUDETIMER_H


#include <Windows.h>
#include <timeapi.h>

# pragma comment(lib, "secur32.lib")
# pragma comment(lib, "winmm.lib")
# pragma comment(lib, "dmoguids.lib")
# pragma comment(lib, "wmcodecdspuuid.lib")
# pragma comment(lib, "msdmo.lib")
# pragma comment(lib, "Strmiids.lib")


#define Clock CrudeTimer::Instance()

class CrudeTimer
{
private:


    //set to the time (in seconds) when class is instantiated
    double m_dStartTime;

    //set the start time
    CrudeTimer(){m_dStartTime = timeGetTime() * 0.001;}

    //copy ctor and assignment should be private
    CrudeTimer(const CrudeTimer&);
    CrudeTimer& operator=(const CrudeTimer&);

public:

    static CrudeTimer* Instance();

    //returns how much time has elapsed since the timer was started

    double GetCurrentTimeCrudeTimer(){return timeGetTime() * 0.001 - m_dStartTime;}



    //    double GetCurrentTimeCrudeTimer(){
//        MMTIME time;
//
//        timeGetSystemTime(&time,sizeof(time));
//
//        return time.wType * 0.001 - m_dStartTime;}

};





#endif //GAMEAIBYEXAMPLE_EXERCISE1_CRUDETIMER_H
