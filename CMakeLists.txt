cmake_minimum_required(VERSION 3.19)
project(GameAIByExample_Exercise1)

set(CMAKE_CXX_STANDARD 17)

add_executable(GameAIByExample_Exercise1 main.cpp State.h MinerOwnedStates.cpp MinerOwnedStates.h Miner.cpp Miner.h BaseGameEntity.cpp BaseGameEntity.h Telegram.h EntityManager.cpp EntityManager.h EntityNames.h Locations.h MessageDispatcher.cpp MessageDispatcher.h MessageTypes.h MinersWife.cpp MinersWife.h MinersWifeOwnedStates.cpp MinersWifeOwnedStates.h CrudeTimer.cpp CrudeTimer.h StateMachine.h)