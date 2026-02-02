#include "Booking.h"
#include <stdexcept>

Booking::Booking(int bookingId,
    int roomId,
    std::string customerName,
    std::string contactNumber,
    std::string checkInDate,
    std::string checkOutDate)
    : bookingId_(bookingId),
    roomId_(roomId),
    customerName_(std::move(customerName)),
    contactNumber_(std::move(contactNumber)),
    checkInDate_(std::move(checkInDate)),
    checkOutDate_(std::move(checkOutDate)) {

    if (bookingId_ <= 0) throw std::invalid_argument("Booking ID must be positive.");
    if (roomId_ <= 0) throw std::invalid_argument("Room ID must be positive.");
    if (customerName_.empty()) throw std::invalid_argument("Customer name cannot be empty.");
    if (contactNumber_.empty()) throw std::invalid_argument("Contact number cannot be empty.");
}

int Booking::getBookingId() const { return bookingId_; }
int Booking::getRoomId() const { return roomId_; }
const std::string& Booking::getCustomerName() const { return customerName_; }
const std::string& Booking::getContactNumber() const { return contactNumber_; }
const std::string& Booking::getCheckInDate() const { return checkInDate_; }
const std::string& Booking::getCheckOutDate() const { return checkOutDate_; }
