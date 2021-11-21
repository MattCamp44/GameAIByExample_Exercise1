//
// Created by mattc on 11/19/2021.
//

#include "Bandit.h"

bool Bandit::HandleMessage(const Telegram &msg) {
    return m_pStateMachine->HandleMessage(msg);
}

void Bandit::Update() {

    m_pStateMachine->Update();

}

void Bandit::UpdateStateAndLocation() {

    if(m_LocationUpdated) m_Location = m_NextLocation;

    m_LocationUpdated = false;

}


