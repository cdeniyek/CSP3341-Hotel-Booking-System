#include "Room.h"
#include <stdexcept>

Room::Room(int id, RoomType type, double pricePerNight, bool isAvailable)
    : id_(id), type_(type), pricePerNight_(pricePerNight), isAvailable_(isAvailable) {
    if (id_ <= 0) throw std::invalid_argument("Room ID must be positive.");
    if (pricePerNight_ < 0.0) throw std::invalid_argument("Price cannot be negative.");
}

int Room::getId() const { return id_; }
RoomType Room::getType() const { return type_; }
double Room::getPricePerNight() const { return pricePerNight_; }
bool Room::getIsAvailable() const { return isAvailable_; }

void Room::setType(RoomType type) { type_ = type; }
void Room::setPricePerNight(double pricePerNight) {
    if (pricePerNight < 0.0) throw std::invalid_argument("Price cannot be negative.");
    pricePerNight_ = pricePerNight;
}
void Room::setIsAvailable(bool isAvailable) { isAvailable_ = isAvailable; }

std::string Room::roomTypeToString(RoomType type) {
    return (type == RoomType::Single) ? "Single" : "Double";
}

RoomType Room::stringToRoomType(const std::string& s) {
    if (s == "Single") return RoomType::Single;
    if (s == "Double") return RoomType::Double;
    throw std::invalid_argument("Invalid room type string: " + s);
}
