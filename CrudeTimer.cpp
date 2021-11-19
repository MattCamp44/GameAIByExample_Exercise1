//
// Created by mattc on 11/19/2021.
//

#include "CrudeTimer.h"

CrudeTimer* CrudeTimer::Instance()
{
    static CrudeTimer instance;

    return &instance;
}