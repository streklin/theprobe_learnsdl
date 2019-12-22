#ifndef PLAYERRESOURCES
#define PLAYERRESOURCES

class PlayerResources final {
public:
    PlayerResources();

    int Credits();
    void UpdateCredits(const int diff);

    int Energy();
    void UpdateEnergy(const int diff);
    
    int EnergyMax();
    void UpdateEnergyMax(const int diff);
    
    int Reputation();
    void UpdateReputation(const int diff);

private:
    int credits_;
    int energy_;
    int energy_max_;
    int reputation_;
};

#endif