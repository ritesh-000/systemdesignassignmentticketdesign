enum SeatStatus { AVAILABLE, BOOKED };

// Encapsulation: status can ONLY change through markBooked()/markAvailable() -
// no public setter, which is what makes FR4 (reject already-booked seats) enforceable
class ShowSeat {
private:
    Seat* seat;           // points at a Seat owned by the Screen - ShowSeat does not own it
    SeatStatus status;
public:
    ShowSeat(Seat* seat) : seat(seat), status(AVAILABLE) {}

    bool isAvailable() const { return status == AVAILABLE; }
    void markBooked() { status = BOOKED; }
    void markAvailable() { status = AVAILABLE; }
    Seat* getSeat() const { return seat; }
};
