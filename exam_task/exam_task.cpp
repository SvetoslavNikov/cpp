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
        return salary;
    }

    virtual void AddSalary(double salary) = 0;

    virtual ~Worker() {
        cout<<"abstract worker destructor";
    };
};

class OnlineWorker : public Worker {
    string platform;
public:
    explicit OnlineWorker(string name, int level, string boss, string platform) :
    Worker(name,level,boss), platform(platform){}

    void AddSalary(double salary) override {
        this->salary = salary;
    }

    bool operator>(const OnlineWorker& worker2) const {
        if (this->getSalary() > worker2.getSalary()) {
            return true;
        }
        return false;
    }

    ~OnlineWorker() {
        cout<<"online worker destructor";
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
        if (this->getSalary() > worker2.getSalary()) {
            return true;
        }
        return false;
    }

    ~OnsiteWorker() {
        cout <<"onsite worker destructor";
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
        OnlineWorker("Dimi",2,"bossName1","shopify"),
        OnlineWorker("Bimi",3,"bossName2","shopify")
    };

    vector<OnsiteWorker> onsite_workers = {
        OnsiteWorker("jimi",1,"bossName","Bahlstal"),
        OnsiteWorker("dimi",2,"bossName2","Bahlstal"),
        OnsiteWorker("bimi",3,"bossName3","Bahlstal")
    };

    Worker* workers[5];
    workers[0] = &online_workers[0];
    workers[1] = &online_workers[1];

    workers[2] = &onsite_workers[0];
    workers[3] = &onsite_workers[1];
    workers[4] = &onsite_workers[2];

    addSalaries(online_workers);
    addSalaries(onsite_workers);

    int max_salary = online_workers[0].getSalary();
    Worker* worker = &online_workers[0];
    for (OnlineWorker& online_worker:online_workers) {
        if (max_salary < online_worker.getSalary()) {
            max_salary = online_worker.getSalary();
            worker = &online_worker;
        }
    }

    cout<<worker->getName();

    int min_salary = onsite_workers[0].getSalary();
    worker = &onsite_workers[0];
    for (OnsiteWorker& onsite_worker:onsite_workers) {
        if (min_salary > onsite_worker.getSalary()) {
            min_salary = onsite_worker.getSalary();
            worker = &onsite_worker;
        }
    }
    cout<<worker->getName();

    string bossTeam = "bossName";
    for (Worker* worker: workers) {
        if (bossTeam == worker->getBoss()) {
            cout << worker->getName();
        }
    }
}
