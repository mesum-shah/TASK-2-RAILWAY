#include <iostream>
#include <unordered_map>

// Initialize data structures to track available tickets, passengers, and earnings
std::unordered_map<std::string, int> availableTickets = {
    {"09:00_up", 6 * 80},
    {"11:00_up", 6 * 80},
    {"13:00_up", 6 * 80},
    {"15:00_up", 6 * 80},
    {"10:00_down", 6 * 80},
    {"12:00_down", 6 * 80},
    {"14:00_down", 6 * 80},
    {"16:00_down", 6 * 80 + 2 * 80}  // Extra coaches on the last train down
};

std::unordered_map<std::string, int> passengersCount = {
    {"09:00_up", 0},
    {"11:00_up", 0},
    {"13:00_up", 0},
    {"15:00_up", 0},
    {"10:00_down", 0},
    {"12:00_down", 0},
    {"14:00_down", 0},
    {"16:00_down", 0}
};

std::unordered_map<std::string, int> earnings = passengersCount;

// Function prototypes
void displayScreen();
std::string purchaseTickets(std::string journey, int numTickets);
void endOfDaySummary();

// Task 1 - Start of the day
void displayScreen() {
    std::cout << "Train Schedule & Available Tickets" << std::endl;
    for (const auto &ticket : availableTickets) {
        if (ticket.second > 0) {
            std::cout << ticket.first << ": " << ticket.second << " tickets available" << std::endl;
        } else {
            std::cout << ticket.first << ": Closed" << std::endl;
        }
    }
}

// Task 2 - Purchasing tickets
std::string purchaseTickets(std::string journey, int numTickets) {
    if (availableTickets[journey] >= numTickets) {
        availableTickets[journey] -= numTickets;
        int price = numTickets * 25;
        if (numTickets >= 10 && numTickets <= 80) {
            int freeTickets = numTickets / 10;
            price -= freeTickets * 25;
        }
        earnings[journey] += price;
        passengersCount[journey] += numTickets;
        return "Tickets purchased successfully.";
    } else {
        return "Not enough tickets available for this journey.";
    }
}

// Task 3 - End of the day
void endOfDaySummary() {
    int totalPassengers = 0;
    int totalEarnings = 0;

    std::cout << "\nEnd of the day summary:" << std::endl;
    for (const auto &passenger : passengersCount) {
        std::cout << passenger.first << ": " << passenger.second << " passengers, Total earnings: $" << earnings[passenger.first] << std::endl;
        totalPassengers += passenger.second;
        totalEarnings += earnings[passenger.first];
    }

    std::cout << "\nTotal Passengers for the day: " << totalPassengers << std::endl;
    std::cout << "Total Earnings for the day: $" << totalEarnings << std::endl;

    std::string maxPassengersJourney;
    int maxPassengers = 0;
    for (const auto &passenger : passengersCount) {
        if (passenger.second > maxPassengers) {
            maxPassengers = passenger.second;
            maxPassengersJourney = passenger.first;
        }
    }
    std::cout << "Journey with the most passengers: " << maxPassengersJourney << " - " << maxPassengers << " passengers" << std::endl;
}

int main() {
    displayScreen();

    // Test purchasing tickets
    std::cout << purchaseTickets("09:00_up", 5) << std::endl;
    std::cout << purchaseTickets("09:00_up", 15) << std::endl;
    std::cout << purchaseTickets("09:00_up", 25) << std::endl;

    // Test end of the day summary
    endOfDaySummary();

    return 0;
}
