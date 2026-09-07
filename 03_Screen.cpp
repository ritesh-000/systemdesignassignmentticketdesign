#include <vector>
using namespace std;

// Composition: a Screen owns its Seats - they have no meaning outside it
class Screen {
private:
    int screenNumber;
    vector<Seat> seats;
public:
    Screen(int screenNumber) : screenNumber(screenNumber) {}

    void addSeat(Seat s) { seats.push_back(s); }
    vector<Seat>& getSeats() { return seats; }
    int getScreenNumber() const { return screenNumber; }
};
