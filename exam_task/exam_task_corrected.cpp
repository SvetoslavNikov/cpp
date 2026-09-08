#include <iostream>
#include <stdexcept>
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
    explicit Worker(const string& name, int level, const string& boss) :
        name(name), level(level), boss(boss) {
        if (!stringIsCorrect(name) || !stringIsCorrect(boss) || level < 0) {
            throw invalid_argument("Invalid worker data");
        }
    }

    static bool stringIsCorrect(const string& s) {
        if (s.size() < 3 || s.size() > 50) {
            return false;
        }

        for (char character : s) {
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

    double getSalary() const {
        double total = 0;
        for (double salary : salaries) {
            total += salary;
        }
        return total;
    }

    virtual void AddSalary(double salary) = 0;

    virtual ~Worker() = default;
};

class OnlineWorker : public Worker {
    string platform;
public:
    explicit OnlineWorker(const string& name, int level, const string& boss,
                          const string& platform) :
        Worker(name, level, boss), platform(platform) {
        if (!stringIsCorrect(platform)) {
            throw invalid_argument("Invalid platform");
        }
    }

    void AddSalary(double salary) override {
        if (salary < 0) {
            throw invalid_argument("Salary cannot be negative");
        }
        salaries.push_back(salary);
    }

    bool operator>(const OnlineWorker& worker2) const {
        if (this->getSalary() > worker2.getSalary()) {
            return true;
        }
        return false;
    }

};

class OnsiteWorker : public Worker {
    string location;
public:
    explicit OnsiteWorker(const string& name, int level, const string& boss,
                          const string& location) :
        Worker(name, level, boss), location(location) {
        if (!stringIsCorrect(location)) {
            throw invalid_argument("Invalid location");
        }
    }

    void AddSalary(double salary) override {
        if (salary < 0) {
            throw invalid_argument("Salary cannot be negative");
        }
        salaries.push_back(salary);
    }

    bool operator>(const OnsiteWorker& worker2) const {
        return this->getSalary() > worker2.getSalary();
    }
};

void addSalaries(vector<OnlineWorker>& workers) {
    for (OnlineWorker& worker:workers) {
        worker.AddSalary(500.50);
    }
}

void addSalaries(vector<OnsiteWorker>& workers) {
    for (OnsiteWorker& worker:workers) {
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
