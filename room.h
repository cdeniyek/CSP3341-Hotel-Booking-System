#pragma once
#include <string>

enum class RoomType {
    Single = 0,
    Double = 1
};

class Room {
private:
    int id_{};
    RoomType type_{ RoomType::Single };
    double pricePerNight_{ 0.0 };
    bool isAvailable_{ true };

public:
    Room() = default;
    Room(int id, RoomType type, double pricePerNight, bool isAvailable);

    int getId() const;
    RoomType getType() const;
    double getPricePerNight() const;
    bool getIsAvailable() const;

    void setType(RoomType type);
    void setPricePerNight(double pricePerNight);
    void setIsAvailable(bool isAvailable);

    static std::string roomTypeToString(RoomType type);
    static RoomType stringToRoomType(const std::string& s);
};
