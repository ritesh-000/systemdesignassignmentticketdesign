#include <vector>
using namespace std;

enum BookingStatus { PENDING, CONFIRMED, FAILED, CANCELLED };

// Its ONE responsibility: hold booking id, show, seats, amount, status.
// Must NOT calculate price, print tickets, or process payment itself.
class Booking {
private:
    static int nextBookingId;      // Static member: unique id counter shared by every Booking
    int bookingId;
    Customer* customer;            // Association - Booking uses a Customer, doesn't own its lifecycle
    Show* show;                    // Aggregation - references a Show it doesn't own
    vector<ShowSeat*> bookedSeats; // Aggregation - references seats owned by the Show
    double totalAmount;
    BookingStatus status;
public:
    Booking(Customer* customer, Show* show, vector<ShowSeat*> bookedSeats, double totalAmount)
        : customer(customer), show(show), bookedSeats(bookedSeats),
          totalAmount(totalAmount), status(PENDING) {
        bookingId = nextBookingId++;
    }

    void confirm() { status = CONFIRMED; }
    void fail() { status = FAILED; }
    void cancel() { status = CANCELLED; }

    int getBookingId() const { return bookingId; }
    BookingStatus getStatus() const { return status; }
    Show* getShow() const { return show; }
    vector<ShowSeat*> getBookedSeats() const { return bookedSeats; }
    double getTotalAmount() const { return totalAmount; }
    Customer* getCustomer() const { return customer; }
};

int Booking::nextBookingId = 1001;
