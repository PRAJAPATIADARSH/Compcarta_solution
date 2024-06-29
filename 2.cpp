#include <iostream>
#include <vector>

class FlipFlop {
protected:
    bool Q;
    bool Q_not;
public:
    FlipFlop() : Q(false), Q_not(true) {}
    virtual void clock(bool set, bool reset, bool clock, bool data) = 0;
    bool getQ() const { return Q; }
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

class SequentialCircuitSimulator {
private:
    std::vector<DFlipFlop> flipFlops;
public:
    SequentialCircuitSimulator(int numberOfFlipFlops) {
        flipFlops.resize(numberOfFlipFlops);
    }

    void simulateShiftRegister(int clockCycles, const std::vector<bool>& dataInputs) {
        int dataIndex = 0;
        for (int cycle = 0; cycle < clockCycles; ++cycle) {
            bool input = dataIndex < dataInputs.size() ? dataInputs[dataIndex++] : false;
            bool previousQ = input;
            
            for (auto& flipFlop : flipFlops) {
                bool currentQ = flipFlop.getQ();
                flipFlop.clock(false, false, true, previousQ);
                previousQ = currentQ;
            }

            std::cout << "After clock cycle " << cycle + 1 << ":" << std::endl;
            displayShiftRegisterState();
        }
    }

    void displayShiftRegisterState() const {
        for (size_t i = 0; i < flipFlops.size(); ++i) {
            std::cout << "Flip-Flop " << i + 1 << ": ";
            flipFlops[i].displayOutput();
        }
    }
};

int main() {
    int numberOfFlipFlops;
    int clockCycles;
    std::vector<bool> dataInputs;
    int input;

    std::cout << "Enter the number of D Flip-Flops in the shift register: ";
    std::cin >> numberOfFlipFlops;

    std::cout << "Enter the number of clock cycles to simulate: ";
    std::cin >> clockCycles;

    std::cout << "Enter the data inputs (0 or 1) for each clock cycle (enter -1 to stop): ";
    while (std::cin >> input && input != -1) {
        dataInputs.push_back(input);
    }

    SequentialCircuitSimulator simulator(numberOfFlipFlops);
    simulator.simulateShiftRegister(clockCycles, dataInputs);

    return 0;
}
