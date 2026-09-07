#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

// No header files (course rule) -> classes are included as .cpp text in
// dependency order instead. This is why the include order below does NOT
// match the numeric filename order: 06_ShowSeat.cpp must come before
// 05_Show.cpp because Show is built out of ShowSeats.
#include "02_Seat.cpp"
#include "01_Movie.cpp"
#include "03_Screen.cpp"
#include "04_Cinema.cpp"
#include "06_ShowSeat.cpp"
#include "05_Show.cpp"
#include "07_Customer.cpp"
#include "09_Payment.cpp"
#include "10_PaymentTypes.cpp"
#include "11_PriceCalculator.cpp"
#include "08_Booking.cpp"
#include "12_TicketPrinter.cpp"
#include "13_BookingService.cpp"

vector<string> splitSeats(const string& line) {
    vector<string> result;
    stringstream ss(line);
    string item;
    while (getline(ss, item, ',')) {
        while (!item.empty() && item.front() == ' ') item.erase(item.begin());
        while (!item.empty() && item.back() == ' ') item.pop_back();
        if (!item.empty()) result.push_back(item);
    }
    return result;
}

int readIntChoice() {
    int choice;
    while (!(cin >> choice)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "  Invalid input. Enter a number: ";
    }
    return choice;
}

int main() {
    // ----- One-time setup. Nothing is added to Cinema/Screen after this
    // point, which is what keeps every Screen*/Seat* pointer handed out
    // below valid without needing smart pointers (see submission notes). -----
    Cinema cinema("PVR");

    Screen screen1(1);
    screen1.addSeat(Seat("A1", SILVER));
    screen1.addSeat(Seat("A2", SILVER));
    screen1.addSeat(Seat("A3", SILVER));
    screen1.addSeat(Seat("A4", SILVER));
    screen1.addSeat(Seat("B1", GOLD));
    screen1.addSeat(Seat("B2", GOLD));
    screen1.addSeat(Seat("B3", GOLD));
    screen1.addSeat(Seat("C1", PLATINUM));
    screen1.addSeat(Seat("C2", PLATINUM));
    cinema.addScreen(screen1);

    Screen screen2(2);
    screen2.addSeat(Seat("A1", SILVER));
    screen2.addSeat(Seat("A2", SILVER));
    screen2.addSeat(Seat("B1", GOLD));
    screen2.addSeat(Seat("B2", GOLD));
    cinema.addScreen(screen2);

    Movie movie1("3 Idiots", "Hindi", 170);
    Movie movie2("Interstellar", "English", 169);
    vector<Movie*> movies = { &movie1, &movie2 };

    Show show1(&movie1, &cinema.getScreens()[0], "06:00 PM");
    Show show2(&movie1, &cinema.getScreens()[1], "09:00 PM");
    Show show3(&movie2, &cinema.getScreens()[1], "10:00 PM");

    vector<vector<Show*>> showsByMovie = {
        { &show1, &show2 },
        { &show3 }
    };

    BookingService bookingService;
    Customer customer("Marut", "9999999999");

    cout << "===== MOVIE TICKET BOOKING =====\n";

    bool running = true;
    while (running) {
        cout << "\n1. Movies  2. Book  3. Cancel  4. My tickets   0. Exit\n";
        cout << "Choose: ";
        int choice = readIntChoice();

        if (choice == 1) {
            for (size_t i = 0; i < movies.size(); i++) {
                cout << "  [" << (i + 1) << "] " << movies[i]->getTitle()
                     << "\t" << movies[i]->getLanguage()
                     << "\t" << movies[i]->getDuration() << " min\n";
            }
        }
        else if (choice == 2) {
            for (size_t i = 0; i < movies.size(); i++) {
                cout << "  [" << (i + 1) << "] " << movies[i]->getTitle() << "\n";
            }
            cout << "Choose movie: ";
            int m = readIntChoice();
            if (m < 1 || m > (int)movies.size()) {
                cout << "  Invalid movie choice.\n";
                continue;
            }
            vector<Show*>& shows = showsByMovie[m - 1];
            for (size_t i = 0; i < shows.size(); i++) {
                cout << "  [" << (i + 1) << "] Screen-" << shows[i]->getScreen()->getScreenNumber()
                     << "  " << shows[i]->getStartTime() << "\n";
            }
            cout << "Choose show: ";
            int s = readIntChoice();
            if (s < 1 || s > (int)shows.size()) {
                cout << "  Invalid show choice.\n";
                continue;
            }
            Show* show = shows[s - 1];
            show->printSeatLayout();

            cout << "Seats (e.g. A1,B2): ";
            cin.ignore();
            string line;
            getline(cin, line);
            vector<string> seatNumbers = splitSeats(line);
            if (seatNumbers.empty()) {
                cout << "  No seats entered.\n";
                continue;
            }
            if (!bookingService.areSeatsAvailable(show, seatNumbers)) {
                cout << "  Booking rejected, nothing changed.\n";
                continue;
            }

            cout << "Pay by: 1.UPI  2.Card  3.Cash > ";
            int payChoice = readIntChoice();
            Payment* payment = nullptr;
            if (payChoice == 1) payment = new UpiPayment();
            else if (payChoice == 2) payment = new CardPayment();
            else if (payChoice == 3) payment = new CashPayment();
            else {
                cout << "  Invalid payment method.\n";
                continue;
            }

            bookingService.bookSeats(&customer, show, seatNumbers, payment);
            delete payment;
        }
        else if (choice == 3) {
            cout << "Enter booking ID to cancel (e.g. 1001): ";
            int id = readIntChoice();
            bookingService.cancelBooking(id);
        }
        else if (choice == 4) {
            bool any = false;
            for (Booking& b : bookingService.getAllBookings()) {
                if (b.getCustomer() == &customer) {
                    string statusStr = b.getStatus() == CONFIRMED ? "CONFIRMED" :
                                        b.getStatus() == CANCELLED ? "CANCELLED" :
                                        b.getStatus() == FAILED ? "FAILED" : "PENDING";
                    cout << "  BK" << b.getBookingId() << "  " << b.getShow()->getMovie()->getTitle()
                         << "  Rs." << b.getTotalAmount() << "  [" << statusStr << "]\n";
                    any = true;
                }
            }
            if (!any) cout << "  No tickets yet.\n";
        }
        else if (choice == 0) {
            running = false;
            cout << "Goodbye!\n";
        }
        else {
            cout << "  Invalid menu choice. Try again.\n";
        }
    }

    return 0;
}
