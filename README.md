# GameAIByExample_Exercise1

This is my extension for the second chapter’s project of the book “Game AI by extension” by Mat Buckland.

## Overview

The goal of the project is to practise with state-driven agent design. Basically we have some autonomous agents that are composed of a state object, 
and behave according to the value that this object takes.

Each agent ( Miner, MiersWife and Bandit ) owns a stateMachine that is composed of a global state, a current state and a previous state, to keep track of the 
latest state if the logic requires so.

The original code includes the Miner and the MinersWife agent. I’ve added the Bandit agent and all its related logic ( BanditOwnedStates )

