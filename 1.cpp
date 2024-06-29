#include <iostream>

class FlipFlop {
protected:
    bool Q;
    bool Q_not;
public:
    FlipFlop() : Q(false), Q_not(true) {}
    virtual void clock(bool set, bool reset, bool clock, bool data) = 0;
    void displayOutput() const {
        std::cout << "Q = " << Q << ", Q' = " << Q_not << std::endl;
    }
};

class DFlipFlop : public FlipFlop {
public:
    void clock(bool set, bool reset, bool clock, bool data) override {
        if (reset) {
            Q = false;
            Q_not = true;
        } else if (set) {
            Q = true;
            Q_not = false;
        } else if (clock) {
            Q = data;
            Q_not = !data;
        }
    }
};

class TFlipFlop : public FlipFlop {
public:
    void clock(bool set, bool reset, bool clock, bool data) override {
        if (reset) {
            Q = false;
            Q_not = true;
        } else if (set) {
            Q = true;
            Q_not = false;
        } else if (clock && data) {
            Q = !Q;
            Q_not = !Q_not;
        }
    }
};

class FlipFlopSimulator {
public:
    void simulate() {
        int choice;
        bool set, reset, clock, data;

        std::cout << "Select Flip-Flop type:\n1. D Flip-Flop\n2. T Flip-Flop\n";
        std::cin >> choice;

        std::cout << "Enter set input (0 or 1): ";
        std::cin >> set;
        std::cout << "Enter reset input (0 or 1): ";
        std::cin >> reset;
        std::cout << "Enter clock input (0 or 1): ";
        std::cin >> clock;
        std::cout << "Enter data input (0 or 1): ";
        std::cin >> data;

        if (choice == 1) {
            DFlipFlop dFlipFlop;
            std::cout << "Simulating D Flip-Flop..." << std::endl;
            dFlipFlop.clock(set, reset, clock, data);
            dFlipFlop.displayOutput();
        } else if (choice == 2) {
            TFlipFlop tFlipFlop;
            std::cout << "Simulating T Flip-Flop..." << std::endl;
            tFlipFlop.clock(set, reset, clock, data);
            tFlipFlop.displayOutput();
        } else {
            std::cout << "Invalid choice!" << std::endl;
        }
    }
};

int main() {
    FlipFlopSimulator simulator;
    simulator.simulate();
    return 0;
}
