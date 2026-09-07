#include <string>
using namespace std;

enum SeatType { SILVER, GOLD, PLATINUM };

// Encapsulation: seatNumber and type are private, only reachable via getters
class Seat {
private:
    string seatNumber;
    SeatType type;
public:
    Seat(string seatNumber, SeatType type) {
        this->seatNumber = seatNumber;   // 'this' keyword: disambiguates param from member
        this->type = type;
    }
    string getSeatNumber() const { return seatNumber; }
    SeatType getType() const { return type; }
};

string seatTypeToString(SeatType type) {
    switch (type) {
        case SILVER:   return "SILVER";
        case GOLD:     return "GOLD";
        case PLATINUM: return "PLATINUM";
    }
    return "UNKNOWN";
}
