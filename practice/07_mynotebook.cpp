#include <iostream>
#include <string>
#include <vector>


using namespace std;

class Note{
private:
    string title;
    string text;
public:
    Note(string text, string title) : title (title), text (text) {}

    void print() const {
        cout << title << '\n' << text << '\n\n';
    }

    string getTitle() const {
        return title;
    }

    string getText() const {
        return text;
    }
};


class NoteBook {
private:
    string title;
    vector<Note> notes;

public:
    NoteBook(const string& title) : title (title){};

    void addNote(Note note) {
        notes.push_back(note);
    }

    void printNotes() const {
        cout << "Notebook title: " << title << "\n";

        for (auto iterator = notes.begin(); iterator != notes.end(); iterator++) {
            const Note& note = *iterator;
            cout << "Note title: " << note.getTitle() << "\n";
            cout << "Note text: " << note.getText() << "\n";
        }
    }

};


int main() {
    Note n1("text1", "note1");
    Note n2("text2", "note2");
    Note n3("text3", "note3");

    NoteBook nb("humtty dumpty");

    nb.addNote(n1);
    nb.addNote(n2);
    nb.addNote(n3);

    nb.printNotes();


}
