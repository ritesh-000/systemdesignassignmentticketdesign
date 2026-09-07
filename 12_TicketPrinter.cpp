#include <iostream>
#include <vector>
using namespace std;

// Its ONE responsibility: format and print a ticket. Must NOT modify Booking or
// ShowSeat state, calculate price, or process payment - display only, no side effects.
class TicketPrinter {
public:
    static void printTicket(Booking& booking) {
        cout << "\n  ================ TICKET ================\n";
        cout << "   Booking ID : BK" << booking.getBookingId() << "\n";
        cout << "   Movie      : " << booking.getShow()->getMovie()->getTitle() << "\n";
        cout << "   Screen     : Screen-" << booking.getShow()->getScreen()->getScreenNumber()
             << "    " << booking.getShow()->getStartTime() << "\n";
        cout << "   Seats      : ";
        vector<ShowSeat*> seats = booking.getBookedSeats();
        for (size_t i = 0; i < seats.size(); i++) {
            cout << seats[i]->getSeat()->getSeatNumber();
            if (i + 1 < seats.size()) cout << ", ";
        }
        cout << "\n";
        cout << "   Amount     : Rs." << booking.getTotalAmount() << "        Status: CONFIRMED\n";
        cout << "  =========================================\n";
    }
};
