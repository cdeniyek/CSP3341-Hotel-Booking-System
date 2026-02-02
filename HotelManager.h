#pragma once
#include <vector>
#include <string>
#include "Room.h"
#include "Booking.h"

class HotelManager {
private:
    std::vector<Room> rooms_;
    std::vector<Booking> bookings_;
    int nextBookingId_{ 1 };

public:
    // Load/save
    bool loadFromFiles(const std::string& roomsPath, const std::string& bookingsPath, std::string& err);
    bool saveToFiles(const std::string& roomsPath, const std::string& bookingsPath, std::string& err) const;

    // Rooms
    bool addRoom(int id, RoomType type, double pricePerNight, std::string& err);
    void listRooms() const;
    Room* findRoomById(int id);
    const Room* findRoomById(int id) const;

    // Bookings
    bool checkIn(int roomId,
        const std::string& customerName,
        const std::string& contactNumber,
        const std::string& checkInDate,
        const std::string& checkOutDate,
        std::string& err);

    bool checkOut(int roomId, std::string& err);
    void listBookings() const;

    int getNextBookingId() const;
};

