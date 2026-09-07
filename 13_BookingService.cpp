#include <vector>
#include <list>
#include <iostream>
using namespace std;

// The orchestrator: runs the booking flow end to end.
// Dependency Inversion: depends on the Payment ABSTRACTION, not concrete payment
// classes. Open/Closed: adding NetBanking needs only a new Payment subclass -
// nothing in this file has to change.
class BookingService {
private:
    list<Booking> allBookings;   // list, not vector: keeps every Booking's address
                                  // stable when new bookings are added later
public:
    // Read-only pre-check so the console layer can avoid prompting for a payment
    // method when the booking is going to be rejected anyway (FR4 still re-checks
    // this itself before touching any state - this is purely a UX shortcut).
    bool areSeatsAvailable(Show* show, const vector<string>& seatNumbers) {
        for (const string& num : seatNumbers) {
            ShowSeat* found = nullptr;
            for (ShowSeat& ss : show->getShowSeats()) {
                if (ss.getSeat()->getSeatNumber() == num) { found = &ss; break; }
            }
            if (!found) {
                cout << "  Invalid seat number: " << num << ".\n";
                return false;
            }
            if (!found->isAvailable()) {
                cout << "  Seat " << num << " is already booked.\n";
                return false;
            }
        }
        return true;
    }

    Booking* bookSeats(Customer* customer, Show* show, vector<string> seatNumbers, Payment* payment) {
        vector<ShowSeat*> selected;

        // FR4: validate every seat FIRST - if any is invalid or already booked,
        // reject the whole booking and change nothing (all-or-nothing)
        for (string& num : seatNumbers) {
            ShowSeat* found = nullptr;
            for (ShowSeat& ss : show->getShowSeats()) {
                if (ss.getSeat()->getSeatNumber() == num) { found = &ss; break; }
            }
            if (!found) {
                cout << "  Invalid seat number: " << num << ". Booking cancelled.\n";
                return nullptr;
            }
            if (!found->isAvailable()) {
                cout << "  Seat " << num << " is already booked. Booking rejected, nothing changed.\n";
                return nullptr;
            }
            selected.push_back(found);
        }

        double total = PriceCalculator::calculateTotal(selected);
        allBookings.push_back(Booking(customer, show, selected, total));
        Booking* booking = &allBookings.back();

        cout << "\n";
        for (ShowSeat* s : selected) {
            cout << "  " << s->getSeat()->getSeatNumber() << " " << seatTypeToString(s->getSeat()->getType()) << "\n";
        }
        cout << "  TOTAL          Rs." << total << "\n\n";

        // Runtime polymorphism: which pay() runs depends on payment's real type
        bool paid = payment->pay(total);

        // FR6: a failed payment must NOT confirm the booking, and seats are released
        if (!paid) {
            booking->fail();
            cout << "  Payment failed. Booking NOT confirmed. Seats remain AVAILABLE.\n";
            return booking;
        }

        for (ShowSeat* s : selected) s->markBooked();
        booking->confirm();
        TicketPrinter::printTicket(*booking);
        return booking;
    }

    bool cancelBooking(int bookingId) {
        for (Booking& b : allBookings) {
            if (b.getBookingId() == bookingId) {
                if (b.getStatus() == CANCELLED) {
                    cout << "  Booking BK" << bookingId << " is already cancelled.\n";
                    return false;
                }
                if (b.getStatus() != CONFIRMED) {
                    cout << "  Only confirmed bookings can be cancelled.\n";
                    return false;
                }
                for (ShowSeat* s : b.getBookedSeats()) s->markAvailable();
                b.cancel();
                cout << "  Booking BK" << bookingId << " cancelled. Seats are now AVAILABLE.\n";
                return true;
            }
        }
        cout << "  No booking found with ID BK" << bookingId << ".\n";
        return false;
    }

    list<Booking>& getAllBookings() { return allBookings; }
};
