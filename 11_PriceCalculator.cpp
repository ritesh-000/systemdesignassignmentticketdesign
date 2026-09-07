#include <vector>
using namespace std;

// Its ONE responsibility: turn a list of seats into a total - nothing else.
// Must NOT know about Booking, Payment, or printing.
class PriceCalculator {
private:
    static const double SILVER_PRICE;
    static const double GOLD_PRICE;
    static const double PLATINUM_PRICE;
public:
    // Static member function: no PriceCalculator object is ever needed
    static double calculateTotal(const vector<ShowSeat*>& seats) {
        double total = 0;
        for (ShowSeat* s : seats) {
            switch (s->getSeat()->getType()) {
                case SILVER:   total += SILVER_PRICE;   break;
                case GOLD:     total += GOLD_PRICE;     break;
                case PLATINUM: total += PLATINUM_PRICE; break;
            }
        }
        return total;
    }
};

// Static members - constants instead of magic numbers
const double PriceCalculator::SILVER_PRICE = 150;
const double PriceCalculator::GOLD_PRICE = 250;
const double PriceCalculator::PLATINUM_PRICE = 400;
