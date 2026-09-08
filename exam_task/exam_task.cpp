#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Worker {
    string name;
    int level;
    string boss;

protected:
    vector<double> salaries;

public:
    explicit Worker(const string& name, int level, const string& boss) : name(name), level(level), boss(boss) {
        if (!(checkString(name) && checkString(boss) && level < 0)) {
            throw invalid_argument("Pass the right params ffs");
        }
    }

    static bool checkString(const string &s) {
        if (s.size() < 3 || s.size() > 50) {
            return false;
        }

        for (char character: s) {
            if (!((character >= 'A' && character <= 'Z') ||
                  (character >= 'a' && character <= 'z'))) {
                return false;
            }
        }
        return true;
    }


    string getName() const {
        return this->name;
    }

    int getLevel() const {
        return this->level;
    }

    string getBoss() const {
        return this->boss;
    }

    int getSalary() const {
        double total;
        for (double salary : salaries) {
            total += salary;
        }
        return total;
    }

    virtual void AddSalary(double salary) = 0;

    virtual ~Worker() {
        cout << "abstract worker destructor";
    };
};

class OnlineWorker : public Worker {
    string platform;

public:
    explicit OnlineWorker(string name, int level, string boss, string platform) : Worker(name, level, boss),
        platform(platform) {
        if (!checkString(platform)) {
            throw invalid_argument("Invalid platform");
        }
    }

    void AddSalary(double salary) override {
        if (salary < 0) {
            throw invalid_argument("salary cannot be negative");
        }
        salaries.push_back(salary);
    }

    bool operator>(const OnlineWorker& worker2) const {
        if (this->getSalary() > worker2.getSalary()) {
            return true;
        }
        return false;
    }

    ~OnlineWorker() {
        cout << "online worker destructor";
    }
};

class OnsiteWorker : public Worker {
    string location;

public:
    explicit OnsiteWorker(string name, int level, string boss, string location) : Worker(name, level, boss),
        location(location) {
        if (!checkString(location)) {
            throw invalid_argument("invalid location bro");
        }
    }

    void AddSalary(double salary) override {
        if (salary < 0) {
            throw invalid_argument("salary cannot be negative");
        }
        salaries.push_back(salary);
    }

    bool operator>(const OnsiteWorker& worker2) {
        if (this->getSalary() > worker2.getSalary()) {
            return true;
        }
        return false;
    }

    ~OnsiteWorker() {
        cout << "onsite worker destructor";
    }
};

void addSalaries(vector<OnlineWorker>& workers) {
    for (OnlineWorker &worker: workers) {
        worker.AddSalary(500.50);
    }
}

void addSalaries(vector<OnsiteWorker>& workers) {
    for (OnsiteWorker &worker: workers) {
        worker.AddSalary(600.50);
    }
}

int main() {
    vector<OnlineWorker> online_workers = {
        OnlineWorker("Jimi",1,"bossName","shopify"),
        OnlineWorker("Dimi",2,"bossOne","shopify"),
        OnlineWorker("Bimi",3,"bossTwo","shopify")
    };

    vector<OnsiteWorker> onsite_workers = {
        OnsiteWorker("jimi",1,"bossName","Bahlstal"),
        OnsiteWorker("dimi",2,"bossTwo","Bahlstal"),
        OnsiteWorker("bimi",3,"bossThree","Bahlstal")
    };

    Worker* workers[5];
    workers[0] = &online_workers[0];
    workers[1] = &online_workers[1];

    workers[2] = &onsite_workers[0];
    workers[3] = &onsite_workers[1];
    workers[4] = &onsite_workers[2];

    addSalaries(online_workers);
    addSalaries(onsite_workers);

    OnlineWorker* highest_online = &online_workers[0];
    for (OnlineWorker& online_worker : online_workers) {
        if (online_worker > *highest_online) {
            highest_online = &online_worker;
        }
    }

    cout << "Highest online salary: " << highest_online->getName()
         << " (" << highest_online->getSalary() << ")\n";

    OnsiteWorker* lowest_onsite = &onsite_workers[0];
    for (OnsiteWorker& onsite_worker : onsite_workers) {
        if (*lowest_onsite > onsite_worker) {
            lowest_onsite = &onsite_worker;
        }
    }
    cout << "Lowest onsite salary: " << lowest_onsite->getName()
         << " (" << lowest_onsite->getSalary() << ")\n";

    string bossTeam = "bossName";
    cout << "Workers with boss " << bossTeam << ":\n";
    for (Worker* worker : workers) {
        if (bossTeam == worker->getBoss()) {
            cout << worker->getName() << "\n";
        }
    }
}
