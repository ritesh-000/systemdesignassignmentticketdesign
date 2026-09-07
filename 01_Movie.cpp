#include <string>
using namespace std;

// Encapsulation: all fields private, read-only access through getters
class Movie {
private:
    string title;
    string language;
    int durationMinutes;
public:
    // Compile-time polymorphism: two overloaded constructors
    Movie(string title, string language, int durationMinutes) {
        this->title = title;
        this->language = language;
        this->durationMinutes = durationMinutes;
    }
    Movie(string title, string language) : Movie(title, language, 120) {}  // delegates via this()

    string getTitle() const { return title; }
    string getLanguage() const { return language; }
    int getDuration() const { return durationMinutes; }
};
