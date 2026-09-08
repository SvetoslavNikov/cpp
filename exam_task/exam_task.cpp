#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Worker {
    string name;
    int level;
    string boss;
protected:
    int salary = 0;

public:
    explicit Worker(string name, int level, string boss) {
        if (checkString(name) && checkString(boss)) {
            this->name = name;
            this->boss = boss;
            this->level = level;
        } else {
            throw invalid_argument("Pass the right params ffs");
        }
    }

    bool checkString(string& s) const {
        if (s.size() > 3 && s.size() < 50) {
            return true;
        }
        return false;
    }

    string getName() {
        return this->name;
    }

    int getLevel() {
        return this->level;
    }

    string getBoss() {
        return this->boss;
    }

    int getSalary() {
        return salary;
    }

    virtual void AddSalary(double salary) = 0;

    ~Worker();
};

class OnlineWorker : public Worker {
    string platform;
public:
    explicit OnlineWorker(string name, int level, string boss, string platform) :
    Worker(name,level,boss), platform(platform){}

    void AddSalary(double salary) override {
        this->salary = salary;
    }

    bool operator>(const OnlineWorker& worker2) {
        if (worker2.getSalary() > this->getSalary()) {
            return true;
        }
        return false;
    }
};

class OnsiteWorker : public Worker {
    string location;
public:
    explicit OnsiteWorker(string name, int level, string boss, string location) :
    Worker(name, level, boss), location(location){}

    void AddSalary(double salary) override {
        this->salary = salary;
    }

    bool operator>(const OnsiteWorker& worker2) {
        if (worker2.getSalary() > this->getSalary()) {
            return true;
        }
        return false;
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
        OnlineWorker("Jim",1,"bossName","shopify"),
        OnlineWorker("Dim",2,"bossName1","shopify"),
        OnlineWorker("Bim",3,"bossName2","shopify")
    };

    vector<OnsiteWorker> onsite_workers = {
        OnsiteWorker("jim",1,"bossName","Bahlstal"),
        OnsiteWorker("dim",2,"bossName2","Bahlstal"),
        OnsiteWorker("bim",3,"bossName3","Bahlstal")
    };

    Worker* workers[5];
    workers[0] = &online_workers[0];
    workers[1] = &online_workers[1];

    workers[2] = &onsite_workers[0];
    workers[3] = &onsite_workers[1];
    workers[4] = &onsite_workers[2];

    addSalaries(online_workers);
    addSalaries(onsite_workers);

    int max_salary = 0;
    Worker* worker;
    for (OnlineWorker online_worker:online_workers) {
        if (max_salary < online_worker.getSalary()) {
            worker = &online_worker;
        }
    }

    cout<<worker->getName();

    int min_salary = 0;
    for (OnsiteWorker onsite_worker:onsite_workers) {
        if (min_salary > onsite_worker.getSalary()) {
            worker = &onsite_worker;
        }
    }
    cout<<worker->getName();

    string bossTeam = "bossName";
    for (Worker* worker: workers) {
        if (bossTeam = worker->getBoss()) {
            cout>>worker->getName();
        }
    }
}
