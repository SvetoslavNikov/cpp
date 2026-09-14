#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

// На изпита класът Server е предефиниран и не се имплементира от студента.
class Server {
    string hostname;

public:
    explicit Server(const string& hostname) : hostname(hostname) {}

    string getHostname() const {
        return hostname;
    }
};

class DataCenter {
    string name;
    double power;
    string admin;
    static int instanceCount;

protected:
    vector<Server> servers;

public:
    DataCenter(const string& name, double power, const string& admin)
        : name(name), power(power), admin(admin) {
        if (!stringIsCorrect(name) || !stringIsCorrect(admin) || power <= 0) {
            throw invalid_argument("Invalid data center data");
        }
        ++instanceCount;
    }

    DataCenter(const DataCenter& other)
        : name(other.name),
          power(other.power),
          admin(other.admin),
          servers(other.servers) {
        ++instanceCount;
    }

    virtual ~DataCenter() {
        --instanceCount;
    }

    static bool stringIsCorrect(const string& s) {
        return s.size() >= 3 && s.size() <= 50;
    }

    static int dataCentersNumber() {
        return instanceCount;
    }

    virtual void addServers(const Server& server) = 0;

    DataCenter& operator+(DataCenter& other) {
        for (const Server& server : other.servers) {
            addServers(server);
        }
        other.servers.clear();
        return *this;
    }

    string getName() const {
        return name;
    }

    double getPower() const {
        return power;
    }

    string getAdmin() const {
        return admin;
    }

    int getServerCount() const {
        return static_cast<int>(servers.size());
    }

    const vector<Server>& getServers() const {
        return servers;
    }
};

int DataCenter::instanceCount = 0;

class CloudDataCenter : public DataCenter {
    string provider;

public:
    CloudDataCenter(const string& name, double power, const string& admin,
                    const string& provider)
        : DataCenter(name, power, admin), provider(provider) {
        if (!stringIsCorrect(provider)) {
            throw invalid_argument("Invalid provider");
        }
    }

    string getProvider() const {
        return provider;
    }

    void addServers(const Server& server) override {
        servers.push_back(server);
    }
};

class LocalDataCenter : public DataCenter {
    string building;

public:
    LocalDataCenter(const string& name, double power, const string& admin,
                    const string& building)
        : DataCenter(name, power, admin), building(building) {
        if (!stringIsCorrect(building)) {
            throw invalid_argument("Invalid building");
        }
    }

    string getBuilding() const {
        return building;
    }

    void addServers(const Server& server) override {
        servers.push_back(server);
    }
};

int main() {
    vector<CloudDataCenter> cloudCenters = {
        CloudDataCenter("Sofia", 120.5, "Ivan", "Amazon"),
        CloudDataCenter("Varna", 80.0, "Maria", "Azure"),
        CloudDataCenter("Burgas", 95.5, "Georgi", "Google")
    };

    vector<LocalDataCenter> localCenters = {
        LocalDataCenter("Plovdiv", 60.0, "Petar", "Alpha"),
        LocalDataCenter("Ruse", 45.5, "Elena", "Beta"),
        LocalDataCenter("Pleven", 55.0, "Nikolai", "Gamma")
    };

    DataCenter* network[5];
    network[0] = &cloudCenters[0];
    network[1] = &cloudCenters[1];
    network[2] = &localCenters[0];
    network[3] = &localCenters[1];
    network[4] = &localCenters[2];

    network[0]->addServers(Server("web01"));
    network[0]->addServers(Server("web02"));
    network[1]->addServers(Server("db01"));
    network[2]->addServers(Server("app01"));
    network[3]->addServers(Server("app02"));
    network[3]->addServers(Server("app03"));
    network[4]->addServers(Server("app04"));

    cout << "Before cloud +: " << cloudCenters[0].getName() << " has "
         << cloudCenters[0].getServerCount() << " servers, "
         << cloudCenters[1].getName() << " has "
         << cloudCenters[1].getServerCount() << " servers\n";

    cloudCenters[0] + cloudCenters[1];

    cout << "After cloud +: " << cloudCenters[0].getName() << " has "
         << cloudCenters[0].getServerCount() << " servers, "
         << cloudCenters[1].getName() << " has "
         << cloudCenters[1].getServerCount() << " servers\n";

    cout << "Before local +: " << localCenters[0].getName() << " has "
         << localCenters[0].getServerCount() << " servers, "
         << localCenters[1].getName() << " has "
         << localCenters[1].getServerCount() << " servers\n";

    localCenters[0] + localCenters[1];

    cout << "After local +: " << localCenters[0].getName() << " has "
         << localCenters[0].getServerCount() << " servers, "
         << localCenters[1].getName() << " has "
         << localCenters[1].getServerCount() << " servers\n";

    cout << "Data centers in the network: "
         << DataCenter::dataCentersNumber() << "\n";

    cout << "Local data center buildings:\n";
    for (DataCenter* center : network) {
        LocalDataCenter* local = dynamic_cast<LocalDataCenter*>(center);
        if (local != nullptr) {
            cout << local->getName() << " -> " << local->getBuilding() << "\n";
        }
    }
}
