#include "PlayerResources.h"

PlayerResources::PlayerResources() {}

int PlayerResources::Credits() { 
    return credits_; 
}

void PlayerResources::UpdateCredits(const int diff) {
    credits_ += diff;
}

int PlayerResources::Energy() { 
    return energy_; 
}

void PlayerResources::UpdateEnergy(const int diff) {
    energy_ += diff;
}
    
int PlayerResources::EnergyMax() { 
    return energy_max_; 
}

void PlayerResources::UpdateEnergyMax(const int diff) {
    energy_max_ += diff;
}
    
int PlayerResources::Reputation() { 
    return reputation_; 
}

void PlayerResources::UpdateReputation(const int diff) {
    reputation_ += diff;
}