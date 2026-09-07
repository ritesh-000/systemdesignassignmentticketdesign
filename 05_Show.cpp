#include <string>
#include <vector>
#include <iostream>
using namespace std;

// Aggregation: Show borrows a Movie and a Screen - neither is destroyed with the Show
// Composition: Show owns its ShowSeats - they exist only for this one screening
class Show {
private:
    Movie* movie;
    Screen* screen;
    string startTime;
    vector<ShowSeat> showSeats;
public:
    Show(Movie* movie, Screen* screen, string startTime)
        : movie(movie), screen(screen), startTime(startTime) {
        for (Seat& s : screen->getSeats()) {
            showSeats.push_back(ShowSeat(&s));
        }
    }

    // absorbs the rejected "seat layout" noun from the noun-verb analysis - it's a
    // print method on Show, not a class of its own
    void printSeatLayout() {
        cout << "\n  SCREEN-" << screen->getScreenNumber() << "  " << startTime
             << "  |  " << movie->getTitle() << "\n";
        SeatType types[] = { SILVER, GOLD, PLATINUM };
        for (SeatType t : types) {
            cout << "  " << seatTypeToString(t) << "\t";
            for (ShowSeat& ss : showSeats) {
                if (ss.getSeat()->getType() == t) {
                    cout << ss.getSeat()->getSeatNumber() << (ss.isAvailable() ? "[ ] " : "[X] ");
                }
            }
            cout << "\n";
        }
        cout << "  ( [ ] = available   [X] = booked )\n";
    }

    vector<ShowSeat>& getShowSeats() { return showSeats; }
    Movie* getMovie() const { return movie; }
    Screen* getScreen() const { return screen; }
    string getStartTime() const { return startTime; }
};
