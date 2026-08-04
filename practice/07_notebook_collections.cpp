// ТЕМА 7: Групиране = един обект държи МНОГО други чрез колекция (vector ≈ динамичен масив).
// Итератор = позиция (не int): begin()→първи, end()→СЛЕД последния; ++it, *it / it->, it != end().
// Notebook ИМА vector<Note> (has-a + колекция); main е тънък оркестратор.
#include <iostream>
#include <string>
#include <vector>

class Note {
private:
    std::string title, body;
public:
    Note(const std::string& t, const std::string& b) : title(t), body(b) {}
    void print() const { std::cout << "[" << title << "] " << body << "\n"; }
};

class Notebook {                              // composition + колекция
private:
    std::string name;
    std::vector<Note> notes;
public:
    explicit Notebook(const std::string& n) : name(n) {}
    void add(const Note& n) { notes.push_back(n); }   // const& = без излишно копие при подаване
    void printAll() const {
        std::cout << name << ":\n";
        for (auto it = notes.begin(); it != notes.end(); ++it)  // it = итератор (позиция)
            it->print();                      // it->x  ≡  (*it).x
    }
};

int main() {
    Notebook nb("prep");
    nb.add(Note("T7", "vector + iterators"));
    nb.add(Note("end", "past-the-end, ne element"));
    nb.printAll();
}
