#pragma once
#include <string>
#include <vector>
#include "Room.h"
#include "Booking.h"

namespace Storage {
    bool ensureDataDirectory(const std::string& dir);

    bool saveRoomsCSV(const std::string& path, const std::vector<Room>& rooms, std::string& err);
    bool loadRoomsCSV(const std::string& path, std::vector<Room>& rooms, std::string& err);

    bool saveBookingsCSV(const std::string& path, const std::vector<Booking>& bookings, std::string& err);
    bool loadBookingsCSV(const std::string& path, std::vector<Booking>& bookings, std::string& err);
}

