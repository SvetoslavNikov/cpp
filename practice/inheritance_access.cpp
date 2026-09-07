// ТЕМА: public, protected и private наследяване.
//
// public наследяване: Derived Е Base.
// protected наследяване: public/protected членовете на Base стават protected в Derived.
// private наследяване: public/protected членовете на Base стават private в Derived.
//
// При class наследяването е private по подразбиране.
// Затова обикновено пишем изрично: class Child : public Parent.

#include <iostream>

class Song {
    protected:
    int year;

public:
    explicit Song(int year) : year(year) {}

    int getYear() const {
        return year;
    }
};

class SingleSong : public Song {              // SingleSong Е Song
public:
    explicit SingleSong(int year) : Song(year) {}

    void showYear() const {
        std::cout << year << "\n";            // protected: достъпно в наследника
    }
};

class AlbumSong : Song {                     // private по подразбиране
public:
    explicit AlbumSong(int year) : Song(year) {}

    void showYear() const {
        std::cout << year << "\n";
    }
};

int main() {
    SingleSong single(2024);
    std::cout << single.getYear() << "\n";   // работи: public наследяване
    single.showYear();

    AlbumSong album(2025);
    album.showYear();

    std::vector<Song> songs;
    songs.push_back(album);

    // работи вътре в AlbumSong
    // std::cout << album.getYear();          // ГРЕШКА: private наследяване
}
