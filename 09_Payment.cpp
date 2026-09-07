// Abstraction: Payment defines the contract only - it hides HOW each method actually pays
class Payment {
protected:
    double amount;
public:
    virtual bool pay(double amount) = 0;   // pure virtual -> makes this class abstract
    virtual ~Payment() {}
};
