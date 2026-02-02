#pragma once
#include <string>

class Booking {
private:
    int bookingId_{};
    int roomId_{};
    std::string customerName_;
    std::string contactNumber_;
    std::string checkInDate_;
    std::string checkOutDate_;

public:
    Booking() = default;
    Booking(int bookingId,
        int roomId,
        std::string customerName,
        std::string contactNumber,
        std::string checkInDate,
        std::string checkOutDate);

    int getBookingId() const;
    int getRoomId() const;
    const std::string& getCustomerName() const;
    const std::string& getContactNumber() const;
    const std::string& getCheckInDate() const;
    const std::string& getCheckOutDate() const;
};

