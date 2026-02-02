#include <iostream>
#include "HotelManager.h"
#include "Storage.h"
#include "utils.h"

static const std::string DATA_DIR = "data";
static const std::string ROOMS_FILE = DATA_DIR + "/rooms.csv";
static const std::string BOOKINGS_FILE = DATA_DIR + "/bookings.csv";

static void printMenu() {
    std::cout << "\n==============================\n";
    std::cout << " Hotel Room Booking System\n";
    std::cout << "==============================\n";
    std::cout << "1. Add Room\n";
    std::cout << "2. List Rooms\n";
    std::cout << "3. Check-In (Book Room)\n";
    std::cout << "4. Check-Out\n";
    std::cout << "5. List Bookings\n";
    std::cout << "6. Save\n";
    std::cout << "7. Load\n";
    std::cout << "0. Exit\n";
}

int main() {
    HotelManager manager;

    if (!Storage::ensureDataDirectory(DATA_DIR)) {
        std::cout << "ERROR: Could not create/find data directory.\n";
        return 1;
    }

    // Auto-load on startup
    {
        std::string err;
        if (!manager.loadFromFiles(ROOMS_FILE, BOOKINGS_FILE, err)) {
            std::cout << "Warning: load failed: " << err << "\n";
        }
    }

    while (true) {
        printMenu();
        int choice = readInt("Select: ");

        if (choice == 0) {
            std::string err;
            if (!manager.saveToFiles(ROOMS_FILE, BOOKINGS_FILE, err)) {
                std::cout << "Warning: save failed on exit: " << err << "\n";
            }
            else {
                std::cout << "Saved. Goodbye!\n";
            }
            break;
        }

        try {
            if (choice == 1) {
                int id = readInt("Room ID: ");
                int typeInput = readInt("Room Type (0=Single, 1=Double): ");
                double price = readDouble("Price per night: ");

                RoomType type = (typeInput == 1) ? RoomType::Double : RoomType::Single;
                std::string err;
                if (!manager.addRoom(id, type, price, err)) {
                    std::cout << "ERROR: " << err << "\n";
                }
                else {
                    std::cout << "Room added.\n";
                }
            }
            else if (choice == 2) {
                manager.listRooms();
            }
            else if (choice == 3) {
                int roomId = readInt("Room ID to book: ");
                std::string name = readLine("Customer Name: ");
                std::string contact = readLine("Contact Number: ");
                std::string inDate = readLine("Check-in Date (e.g., 2026-02-01): ");
                std::string outDate = readLine("Check-out Date (e.g., 2026-02-02): ");

                std::string err;
                if (!manager.checkIn(roomId, name, contact, inDate, outDate, err)) {
                    std::cout << "ERROR: " << err << "\n";
                }
                else {
                    std::cout << "Booked successfully.\n";
                }
            }
            else if (choice == 4) {
                int roomId = readInt("Room ID to check-out: ");
                std::string err;
                if (!manager.checkOut(roomId, err)) {
                    std::cout << "ERROR: " << err << "\n";
                }
                else {
                    std::cout << "Checked out successfully.\n";
                }
            }
            else if (choice == 5) {
                manager.listBookings();
            }
            else if (choice == 6) {
                std::string err;
                if (!manager.saveToFiles(ROOMS_FILE, BOOKINGS_FILE, err)) {
                    std::cout << "ERROR: " << err << "\n";
                }
                else {
                    std::cout << "Saved.\n";
                }
            }
            else if (choice == 7) {
                std::string err;
                if (!manager.loadFromFiles(ROOMS_FILE, BOOKINGS_FILE, err)) {
                    std::cout << "ERROR: " << err << "\n";
                }
                else {
                    std::cout << "Loaded.\n";
                }
            }
            else {
                std::cout << "Invalid selection.\n";
            }
        }
        catch (const std::exception& ex) {
            // This is good for your report: "Exception handling in C++"
            std::cout << "EXCEPTION: " << ex.what() << "\n";
        }
    }

    return 0;
}
