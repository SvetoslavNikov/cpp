
#include <iostream>

class FintechCompany;
class AiCompany;
class RnDCompany;

// Forward declaration
class Visitor;

// ==================== Company ====================

class Company {
public:
    virtual void accept(const Visitor& visitor) const = 0;
    virtual ~Company() = default;
};

// ==================== Visitor ====================

class Visitor {
public:
    virtual void visit(const FintechCompany& company) const = 0;
    virtual void visit(const AiCompany& company) const = 0;
    virtual void visit(const RnDCompany& company) const = 0;

    virtual ~Visitor() = default;
};








// ==================== Companies ====================

class FintechCompany : public Company {
public:
    void accept(const Visitor& visitor) const override {
        visitor.visit(*this);
    }
};

class AiCompany : public Company {
public:
    void accept(const Visitor& visitor) const override {
        visitor.visit(*this);
    }
};

class RnDCompany : public Company {
public:
    void accept(const Visitor& visitor) const override {
        visitor.visit(*this);
    }
};


// ==================== Concrete Visitor ====================

class CandidateVisitor : public Visitor {
public:
    void visit(const FintechCompany& company) const override {
        std::cout << "Hey I love MONEY MONEY. "
                     "I would like to protect you from fraud.\n";
    }

    void visit(const AiCompany& company) const override {
        std::cout << "Hey I love AI AI AI. Hire me.\n";
    }

    void visit(const RnDCompany& company) const override {
        std::cout << "Hey I love creating STUFF STUFF STUFF. Hire me.\n";
    }
};

// ==================== Main ====================

int main() {
    FintechCompany fintech;
    AiCompany ai;
    RnDCompany rnd;

    CandidateVisitor candidate;

    Company* companies[] = {
        &fintech,
        &ai,
        &rnd
    };

    for (Company* company : companies) {
        company->accept(candidate);
    }
}