#include "HotelManager.h"
#include "Storage.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

bool HotelManager::loadFromFiles(const std::string& roomsPath, const std::string& bookingsPath, std::string& err) {
    if (!Storage::loadRoomsCSV(roomsPath, rooms_, err)) return false;
    if (!Storage::loadBookingsCSV(bookingsPath, bookings_, err)) return false;

    // Compute nextBookingId based on existing bookings
    int maxId = 0;
    for (const auto& b : bookings_) {
        maxId = std::max(maxId, b.getBookingId());
    }
    nextBookingId_ = maxId + 1;
    return true;
}

bool HotelManager::saveToFiles(const std::string& roomsPath, const std::string& bookingsPath, std::string& err) const {
    if (!Storage::saveRoomsCSV(roomsPath, rooms_, err)) return false;
    if (!Storage::saveBookingsCSV(bookingsPath, bookings_, err)) return false;
    return true;
}

bool HotelManager::addRoom(int id, RoomType type, double pricePerNight, std::string& err) {
    if (id <= 0) { err = "Room ID must be positive."; return false; }
    if (pricePerNight < 0.0) { err = "Price cannot be negative."; return false; }
    if (findRoomById(id) != nullptr) { err = "Room ID already exists."; return false; }

    rooms_.emplace_back(id, type, pricePerNight, true);
    return true;
}

void HotelManager::listRooms() const {
    std::cout << "\n--- Rooms ---\n";
    if (rooms_.empty()) {
        std::cout << "No rooms available.\n";
        return;
    }

    std::cout << std::left
        << std::setw(8) << "ID"
        << std::setw(10) << "Type"
        << std::setw(12) << "Price"
        << "Available\n";

    for (const auto& r : rooms_) {
        std::cout << std::left
            << std::setw(8) << r.getId()
            << std::setw(10) << Room::roomTypeToString(r.getType())
            << std::setw(12) << r.getPricePerNight()
            << (r.getIsAvailable() ? "Yes" : "No") << "\n";
    }
}

Room* HotelManager::findRoomById(int id) {
    for (auto& r : rooms_) {
        if (r.getId() == id) return &r;
    }
    return nullptr;
}

const Room* HotelManager::findRoomById(int id) const {
    for (const auto& r : rooms_) {
        if (r.getId() == id) return &r;
    }
    return nullptr;
}

bool HotelManager::checkIn(int roomId,
    const std::string& customerName,
    const std::string& contactNumber,
    const std::string& checkInDate,
    const std::string& checkOutDate,
    std::string& err) {
    Room* room = findRoomById(roomId);
    if (!room) { err = "Room not found."; return false; }
    if (!room->getIsAvailable()) { err = "Room is not available (already booked)."; return false; }
    if (customerName.empty() || contactNumber.empty()) { err = "Customer name/contact cannot be empty."; return false; }

    bookings_.emplace_back(nextBookingId_, roomId, customerName, contactNumber, checkInDate, checkOutDate);
    nextBookingId_++;

    room->setIsAvailable(false);
    return true;
}

bool HotelManager::checkOut(int roomId, std::string& err) {
    Room* room = findRoomById(roomId);
    if (!room) { err = "Room not found."; return false; }
    if (room->getIsAvailable()) { err = "Room is already available (not checked in)."; return false; }

    room->setIsAvailable(true);
    return true;
}

void HotelManager::listBookings() const {
    std::cout << "\n--- Bookings ---\n";
    if (bookings_.empty()) {
        std::cout << "No bookings yet.\n";
        return;
    }

    std::cout << std::left
        << std::setw(10) << "BookingID"
        << std::setw(8) << "RoomID"
        << std::setw(18) << "Customer"
        << std::setw(14) << "Contact"
        << std::setw(12) << "CheckIn"
        << "CheckOut\n";

    for (const auto& b : bookings_) {
        std::cout << std::left
            << std::setw(10) << b.getBookingId()
            << std::setw(8) << b.getRoomId()
            << std::setw(18) << b.getCustomerName()
            << std::setw(14) << b.getContactNumber()
            << std::setw(12) << b.getCheckInDate()
            << b.getCheckOutDate() << "\n";
    }
}

int HotelManager::getNextBookingId() const {
    return nextBookingId_;
}
