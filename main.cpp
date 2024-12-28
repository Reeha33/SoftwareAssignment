#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>
#include <string>
#include <sstream>
#include <ctime>
#include <random>

using namespace std;

// Forward Declarations
class Meadow;
template <typename AntType> class AntFarm;
class Room;  // Declare Room class forward

// Base Class for AntFarm
class AntFarmBase
{
public:
    virtual ~AntFarmBase() = default;
    virtual void tick() = 0;
    virtual void displaySummary() = 0;
    virtual void giveResource(const string& resource, int amount) = 0;
};

//Meadow Class
class Meadow
{
private:
    static Meadow* instance;
    int speciesCount;
    unordered_map<int, shared_ptr<AntFarmBase>> antFarms;

    Meadow(int studentRollNumber)
    {
        speciesCount = 13;  // Fixed species count to 13
    }

public:
    static Meadow* getInstance(int studentRollNumber)
    {
        if (instance == nullptr)
            {
            instance = new Meadow(studentRollNumber);
        }
        return instance;
    }

    template<typename AntType>
    void spawnColony(int x, int y, const string& species)
     {
        int id = antFarms.size() + 1;
        auto newFarm = make_shared<AntFarm<AntType>>(id, x, y, species);  // Instantiate with specific AntType
        antFarms[id] = newFarm;
        cout << "Colony " << id << " created at (" << x << ", " << y << ") with species " << species << ".\n";
    }

    shared_ptr<AntFarmBase> getAntFarm(int id)
    {
        return antFarms.at(id);
    }

    unordered_map<int, shared_ptr<AntFarmBase>> getAntFarms()
    {
        return antFarms;
    }

    int getSpeciesCount() const
     {
        return speciesCount;
    }

    vector<string> getSpeciesNames() const
    {
        return {
            "Warrior", "Drone", "Queen", "Gatherer", "Killer",
            "Pansy", "Worker", "Soldier", "Scout", "Hunter",
            "Protector", "Builder", "Researcher"
        };
    }
};

// Initialize static member of Meadow
Meadow* Meadow::instance = nullptr;

// ----- AntBase Class -----
class Ant {
protected:
    string species;
    int health;
    int strength;
    int foodCost;
    bool isResting;

public:
    Ant(string species, int health, int strength, int foodCost)
        : species(species), health(health), strength(strength), foodCost(foodCost), isResting(false) {}

    virtual void performAction() = 0;

    virtual ~Ant() {}

    string getSpecies() const
    {
        return species;
        }
    int getStrength() const
    {
        return strength;
        }
    int getHealth() const
     {
         return health;
         }
    void reduceHealth(int damage)
     {
         health -= damage;
         }

    bool battle(shared_ptr<Ant> otherAnt)
    {
        if (this->strength > otherAnt->getStrength())
            {
            otherAnt->reduceHealth(this->strength);
            return true;
        }
        return false;
    }

    bool isDead()
    {
        return health <= 0;
    }

    void rest(int food)
     {
        if (food > 0 && !isResting)
            {
            isResting = true;
            cout << species << " is resting and consuming " << foodCost << " food.\n";
        }
    }

    void stopRest()
    {
        isResting = false;
    }

    bool getIsResting() const
    {
        return isResting;
    }
};

// ----- Define 13 Species -----

class Warrior : public Ant
 {
public:
    Warrior(string species)
        : Ant(species, 100, 20, 10) {}

    void performAction() override
    {
        cout << "Warrior is hunting.\n";
    }
};

class Drone : public Ant
{
public:
    Drone(string species)
        : Ant(species, 50, 10, 5) {}

    void performAction() override
    {
        cout << "Drone is foraging.\n";
    }
};

class Queen : public Ant
{
public:
    Queen(string species)
        : Ant(species, 200, 5, 0) {}

    void performAction() override
    {
        cout << "Queen is laying eggs.\n";
    }
};

class Gatherer : public Ant
 {
public:
    Gatherer(string species)
        : Ant(species, 60, 15, 5) {}

    void performAction() override
    {
        cout << "Gatherer is collecting food.\n";
    }
};

class Killer : public Ant
{
public:
    Killer(string species)
        : Ant(species, 80, 25, 12) {}

    void performAction() override
    {
        cout << "Killer is hunting prey.\n";
    }
};

class Pansy : public Ant
{
public:
    Pansy(string species)
        : Ant(species, 50, 8, 5) {}

    void performAction() override
    {
        cout << "Pansy is relaxing.\n";
    }
};

class Worker : public Ant
 {
public:
    Worker(string species)
        : Ant(species, 50, 10, 5) {}

    void performAction() override
    {
        cout << "Worker is gathering resources.\n";
    }
};

class Soldier : public Ant
{
public:
    Soldier(string species)
        : Ant(species, 90, 18, 10) {}

    void performAction() override
    {
        cout << "Soldier is protecting the colony.\n";
    }
};

class Scout : public Ant
{
public:
    Scout(string species)
        : Ant(species, 60, 12, 7) {}

    void performAction() override
    {
        cout << "Scout is exploring the area.\n";
    }
};

class Hunter : public Ant
{
public:
    Hunter(string species)
        : Ant(species, 100, 30, 15) {}

    void performAction() override
    {
        cout << "Hunter is hunting.\n";
    }
};

class Protector : public Ant
{
public:
    Protector(string species)
        : Ant(species, 120, 15, 10) {}

    void performAction() override
    {
        cout << "Protector is defending the colony.\n";
    }
};

class Builder : public Ant
{
public:
    Builder(string species)
        : Ant(species, 70, 10, 8) {}

    void performAction() override
    {
        cout << "Builder is constructing.\n";
    }
};

class Researcher : public Ant
{
public:
    Researcher(string species)
        : Ant(species, 80, 5, 6) {}

    void performAction() override
    {
        cout << "Researcher is analyzing.\n";
    }
};

// ----- Room Class -----
class Room
{
public:
    virtual void build() = 0;  // Every room type should implement its own build method
    virtual ~Room() {}
};

class WorkerRoom : public Room
{
public:
    void build() override
    {
        cout << "Building a worker room...\n";
    }
};

class WarriorRoom : public Room
{
public:
    void build() override
    {
        cout << "Building a warrior room...\n";
    }
};

// ----- AntFactory -----
class AntFactory
{
public:
    static shared_ptr<Ant> createAnt(const string& type, const string& species)
    {
        if (type == "warrior")
            {
            return make_shared<Warrior>(species);
        }
        else if (type == "drone")
            {
            return make_shared<Drone>(species);
        }
        else if (type == "queen")
            {
            return make_shared<Queen>(species);
        }
        else if (type == "gatherer")
            {
            return make_shared<Gatherer>(species);
        }
        else if (type == "killer")
            {
            return make_shared<Killer>(species);
        }
        else if (type == "pansy")
            {
            return make_shared<Pansy>(species);
        }
        else if (type == "worker")
            {
            return make_shared<Worker>(species);
        }
        else if (type == "soldier")
            {
            return make_shared<Soldier>(species);
        }
        else if (type == "scout")
            {
            return make_shared<Scout>(species);
        }
        else if (type == "hunter")
            {
            return make_shared<Hunter>(species);
        }
        else if (type == "protector")
            {
            return make_shared<Protector>(species);
        }
        else if (type == "builder")
            {
            return make_shared<Builder>(species);
        }
        else if (type == "researcher")
            {
            return make_shared<Researcher>(species);
        }
        return nullptr;
    }
};

// ----- AntFarm Class (Template) -----
template<typename AntType>
class AntFarm : public AntFarmBase
{
private:
    int id;
    int x, y;
    string species;
    vector<shared_ptr<Ant>> ants;
    unordered_map<int, shared_ptr<Room>> rooms;
    int warriors, workers, antKills, colonyKills, ticksAlive;
    bool isAlive;
    int killedByColonyId;

public:
    AntFarm(int id, int x, int y, const string& species)
        : id(id), x(x), y(y), species(species), warriors(0), workers(0),
          antKills(0), colonyKills(0), ticksAlive(0), isAlive(true), killedByColonyId(-1) {}

    void addRoom(shared_ptr<Room> room)
    {
        rooms[rooms.size() + 1] = room;
        room->build();
    }

    void spawnAnt(const string& type)
    {
        auto newAnt = AntFactory::createAnt(type, species);
        ants.push_back(newAnt);
        if (type == "warrior") warriors++;
        else if (type == "drone") workers++;
        cout << type << " ant spawned for colony " << id << ".\n";
    }

    void tick() override
    {
        if (!isAlive) return;

        ticksAlive++;
        for (auto& ant : ants)
            {
            if (!ant->getIsResting())
            {
                ant->performAction();
            }
        else
            {
                cout << ant->getSpecies() << " is resting.\n";
            }
        }
    }

    void displaySummary() override
    {
        cout << "Colony ID: " << id << " Summary:\n";
        cout << "Species: " << species << "\n";
        cout << "Workers: " << workers << "\n";
        cout << "Warriors: " << warriors << "\n";
        cout << "Ant Kills: " << antKills << "\n";
        cout << "Colony Kills: " << colonyKills << "\n";
        cout << "Ticks Alive: " << ticksAlive << "\n";
        cout << "Status: " << (isAlive ? "Alive" : "Killed by " + to_string(killedByColonyId)) << "\n";
    }

    void giveResource(const string& resource, int amount) override {
        if (resource == "food")
            {
            // Increase food
            cout << "Colony " << id << " received " << amount << " food.\n";
        }
        else if (resource == "warrior")
            {
            warriors += amount;
            cout << "Colony " << id << " spawned " << amount << " warriors.\n";
            for (int i = 0; i < amount; ++i) {
                spawnAnt("warrior");
            }
        }
    }

    void killColony(int colonyId)
    {
        isAlive = false;
        killedByColonyId = colonyId;
    }

    bool getIsAlive() const
    {
        return isAlive;
    }

    shared_ptr<Ant> getAnt(int index)
    {
        return ants.at(index);
    }
};

// ----- Main Simulation Interface -----
void displayMenu() {
    cout << "\n--- Command Menu ---\n";
    cout << "1. spawn X Y T - Spawn a colony at position (X, Y) with species (T)\n";
    cout << "2. give I R A - Give colony I (resource R) and amount (A)\n";
    cout << "3. tick T - Run T ticks of the simulation\n";
    cout << "4. summary I - Show summary of colony I\n";
    cout << "5. quit - Exit the simulation\n";
}

void executeCommand(const string& command, Meadow* meadow)
 {
    istringstream stream(command);
    string action;
    stream >> action;

    if (action == "spawn")
        {
        int x, y;
        string species;
        stream >> x >> y >> species;
        meadow->spawnColony<Warrior>(x, y, species);  // Add species-specific logic as needed
    }
    else if (action == "give")
        {
        int id, amount;
        string resource;
        stream >> id >> resource >> amount;
        auto farm = meadow->getAntFarm(id);
        farm->giveResource(resource, amount);
    }
    else if (action == "tick")
        {
        int ticks;
        stream >> ticks;
        for (auto& farm : meadow->getAntFarms())
        {
            for (int i = 0; i < ticks; ++i)
            {
                farm.second->tick();
            }
        }
    }
    else if (action == "summary")
    {
        int id;
        stream >> id;
        auto farm = meadow->getAntFarm(id);
        farm->displaySummary();
    }
    else
    {
        cout<<"Invalid command"<<endl;
    }
}

int main()
{
    //srand(time(0));  // Seed for random number generation

    int rollNumber = 9;  // Predefined roll number
    cout << "Predefined roll number: " << rollNumber << endl;

    Meadow* meadow = Meadow::getInstance(rollNumber);

    // Display species count and names
    cout << "Total number of species: " << meadow->getSpeciesCount() << endl;
    cout << "Species: ";
    for (const auto& species : meadow->getSpeciesNames())
        {
        cout << species << " ";
    }
    cout << endl;

    string command;
    do {
        displayMenu();
        cout << "Enter a command: ";
        getline(cin, command);  // Read the input correctly
        executeCommand(command, meadow);
    } while (command != "quit");

    return 0;
}
