#include "Storage.h"
#include <filesystem>
#include <fstream>
#include <sstream>

namespace fs = std::filesystem;

static std::vector<std::string> splitCSVLine(const std::string& line) {
    // Simple CSV splitter (no quoted commas) — enough for this assignment.
    std::vector<std::string> out;
    std::stringstream ss(line);
    std::string item;
    while (std::getline(ss, item, ',')) out.push_back(item);
    return out;
}

namespace Storage {

    bool ensureDataDirectory(const std::string& dir) {
        try {
            if (!fs::exists(dir)) fs::create_directories(dir);
            return true;
        }
        catch (...) {
            return false;
        }
    }

    bool saveRoomsCSV(const std::string& path, const std::vector<Room>& rooms, std::string& err) {
        std::ofstream file(path, std::ios::trunc);
        if (!file) { err = "Failed to open rooms file for writing: " + path; return false; }

        file << "id,type,pricePerNight,isAvailable\n";
        for (const auto& r : rooms) {
            file << r.getId() << ","
                << Room::roomTypeToString(r.getType()) << ","
                << r.getPricePerNight() << ","
                << (r.getIsAvailable() ? "1" : "0") << "\n";
        }
        return true;
    }

    bool loadRoomsCSV(const std::string& path, std::vector<Room>& rooms, std::string& err) {
        rooms.clear();
        std::ifstream file(path);
        if (!file) {
            // Not an error if file doesn't exist yet
            return true;
        }

        std::string line;
        if (!std::getline(file, line)) return true; // header missing or empty file

        while (std::getline(file, line)) {
            if (line.empty()) continue;
            auto cols = splitCSVLine(line);
            if (cols.size() != 4) { err = "Invalid rooms.csv row: " + line; return false; }

            int id = std::stoi(cols[0]);
            RoomType type = Room::stringToRoomType(cols[1]);
            double price = std::stod(cols[2]);
            bool avail = (cols[3] == "1");

            rooms.emplace_back(id, type, price, avail);
        }
        return true;
    }

    bool saveBookingsCSV(const std::string& path, const std::vector<Booking>& bookings, std::string& err) {
        std::ofstream file(path, std::ios::trunc);
        if (!file) { err = "Failed to open bookings file for writing: " + path; return false; }

        file << "bookingId,roomId,customerName,contactNumber,checkInDate,checkOutDate\n";
        for (const auto& b : bookings) {
            file << b.getBookingId() << ","
                << b.getRoomId() << ","
                << b.getCustomerName() << ","
                << b.getContactNumber() << ","
                << b.getCheckInDate() << ","
                << b.getCheckOutDate() << "\n";
        }
        return true;
    }

    bool loadBookingsCSV(const std::string& path, std::vector<Booking>& bookings, std::string& err) {
        bookings.clear();
        std::ifstream file(path);
        if (!file) {
            // Not an error if file doesn't exist yet
            return true;
        }

        std::string line;
        if (!std::getline(file, line)) return true; // header missing or empty file

        while (std::getline(file, line)) {
            if (line.empty()) continue;
            auto cols = splitCSVLine(line);
            if (cols.size() != 6) { err = "Invalid bookings.csv row: " + line; return false; }

            int bookingId = std::stoi(cols[0]);
            int roomId = std::stoi(cols[1]);

            bookings.emplace_back(
                bookingId,
                roomId,
                cols[2],
                cols[3],
                cols[4],
                cols[5]
            );
        }
        return true;
    }

} // namespace Storage
