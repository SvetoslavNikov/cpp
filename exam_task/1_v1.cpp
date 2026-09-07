#include <iostream>
#include <string>
#include <vector>

class Song {
private:
    std::string title;
    std::string genre;
    std::vector<std::string> artists;

public:
    Song(const std::string& title,
         const std::string& genre,
         const std::vector<std::string>& artists)
        : title(title), genre(genre), artists(artists) {
    }

    const std::string& getTitle() const {
        return title;
    }

    const std::string& getGenre() const {
        return genre;
    }

    const std::vector<std::string>& getArtists() const {
        return artists;
    }

    virtual ~Song() {
        std::cout << "Song destroyed" << std::endl;
    }
};

class SingleSong : public Song {
private:
    std::string releaseDate;

public:
    SingleSong(const std::string& title,
               const std::string& genre,
               const std::vector<std::string>& artists,
               const std::string& releaseDate)
        : Song(title, genre, artists), releaseDate(releaseDate) {
    }

    const std::string& getReleaseDate() const {
        return releaseDate;
    }

    ~SingleSong() override {
        std::cout << "Single song destroyed" << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os,
                                    const SingleSong& song);
};

std::ostream& operator<<(std::ostream& os, const SingleSong& song) {
    os << "Title: " << song.getTitle() << '\n'
       << "Genre: " << song.getGenre() << '\n'
       << "Release date: " << song.getReleaseDate() << '\n'
       << "Artists:\n";

    for (const std::string& artist : song.getArtists()) {
        os << "- " << artist << '\n';
    }

    return os;
}

class AlbumSong : public Song {
private:
    std::string albumName;

public:
    AlbumSong(const std::string& title,
              const std::string& genre,
              const std::vector<std::string>& artists,
              const std::string& albumName)
        : Song(title, genre, artists), albumName(albumName) {
    }

    const std::string& getAlbumName() const {
        return albumName;
    }

    ~AlbumSong() override {
        std::cout << "Album song destroyed" << std::endl;
    }

    friend std::ostream& operator<<(std::ostream& os,
                                    const AlbumSong& song);
};

std::ostream& operator<<(std::ostream& os, const AlbumSong& song) {
    os << "Title: " << song.getTitle() << '\n'
       << "Genre: " << song.getGenre() << '\n'
       << "Album: " << song.getAlbumName() << '\n'
       << "Artists:\n";

    for (std::size_t i = 0; i < song.getArtists().size(); ++i) {
        os << "- " << song.getArtists()[i] << '\n';
    }

    return os;
}

void searchAlbum(const std::vector<Song*>& songs,
                 const std::string& albumName) {
    for (Song* song : songs) {
        const AlbumSong* albumSong = dynamic_cast<const AlbumSong*>(song);

        if (albumSong != nullptr && albumSong->getAlbumName() == albumName) {
            std::cout << "Album song found:\n" << *albumSong << std::endl;
            return;
        }
    }

    std::cout << "No album song found.\n";
}

void searchSingle(const std::vector<Song*>& songs,
                  const std::string& releaseDate) {
    for (Song* song : songs) {
        const SingleSong* singleSong = dynamic_cast<const SingleSong*>(song);

        if (singleSong != nullptr &&
            singleSong->getReleaseDate() == releaseDate) {
            std::cout << "Single song found:\n" << *singleSong << std::endl;
            return;
        }
    }

    std::cout << "No single song found.\n";
}

int main() {
    AlbumSong albumSong(
        "songTitle",
        "jazz",
        {"jim", "bim", "dim"},
        "albumName");

    SingleSong singleSong(
        "songTitle",
        "hip-hop",
        {"jazz", "bim", "dim"},
        "22/01/2002");

    std::vector<Song*> songs{&singleSong, &albumSong};

    std::cout << "What type of song do you want to search? "
                 "albumsong or singlesong: ";

    std::string songType;
    if (!(std::cin >> songType)) {
        return 0;
    }

    if (songType == "albumsong") {
        std::cout << "Enter the album name: ";
        std::string albumName;
        std::cin >> albumName;
        searchAlbum(songs, albumName);
    } else if (songType == "singlesong") {
        std::cout << "Enter the release date: ";
        std::string releaseDate;
        std::cin >> releaseDate;
        searchSingle(songs, releaseDate);
    } else {
        std::cout << "Invalid song type.\n";
    }

    return 0;
}
