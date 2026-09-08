#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Part 1 -------------------------------------------------------------

class ConverterAbstract {
public:
    virtual ~ConverterAbstract() = default;

    virtual double convert(double fahrenheit) const = 0;
};

class ConverterImplementation : public ConverterAbstract {
public:
    double convert(double fahrenheit) const override {
        return (5.0 / 9.0) * (fahrenheit - 32.0);
    }
};

// Part 2 -------------------------------------------------------------

class Date {
    int day;
    int month;
    int year;

public:
    Date(int day, int month, int year)
        : day(day), month(month), year(year) {}

    friend ostream& operator<<(ostream& os, const Date& date);
};

ostream& operator<<(ostream& os, const Date& date) {
    os << date.day << "/" << date.month << "/" << date.year;
    return os;
}

class PatientVisit {
    string egn;
    string patient_name;
    string complains;
    Date date;

public:
    PatientVisit(string egn, string patient_name,
                 string complains, Date date)
        : egn(egn),
          patient_name(patient_name),
          complains(complains),
          date(date) {}

    string getComplains() const {
        return complains;
    }

    friend ostream& operator<<(ostream& os, const PatientVisit& patient);
};

ostream& operator<<(ostream& os, const PatientVisit& patient) {
    os << "EGN: " << patient.egn << '\n';
    os << "Patient: " << patient.patient_name << '\n';
    os << "Complains: " << patient.complains << '\n';
    os << "Date: " << patient.date << '\n';
    return os;
}

int main() {
    vector<PatientVisit> patients;

    patients.push_back(
        PatientVisit("1234567890", "John", "Headache", Date(1, 5, 2024)));

    patients.push_back(
        PatientVisit("9876543210", "Alice", "Complains", Date(2, 5, 2024)));

    patients.push_back(
        PatientVisit("1111111111", "Bob", "Fever", Date(3, 5, 2024)));

    patients.push_back(
        PatientVisit("2222222222", "Mary", "Complains", Date(4, 5, 2024)));

    for (const auto& patient : patients) {
        if (patient.getComplains() == "Complains") {
            cout << patient << endl;
        }
    }

    for (const auto& patient : patients) {

    }

    return 0;
}