#include <string>
#include <vector>
using namespace std;

// Composition: a Cinema owns its Screens - destroy the Cinema, the Screens go with it
class Cinema {
private:
    string name;
    vector<Screen> screens;
public:
    Cinema(string name) : name(name) {}

    void addScreen(Screen s) { screens.push_back(s); }
    vector<Screen>& getScreens() { return screens; }
    string getName() const { return name; }
};
