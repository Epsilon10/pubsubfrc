#pragma once

#include <string>
#include <memory>


class Message {
    public:
    Message() = default;
    Message(std::string const& topic) : topic(topic) { }
    Message(Message&& other) = default;
    Message(Message const& other) = default;
    ~Message() = default;

    Message& operator=(Message&& other) {
        data = std::move(other.data);
        data = other.data;
        other.data = nullptr;

        return *this;
    }

    void set_topic(std::string const& topic) {
        this->topic = topic;
    }

    void set_data(uint8_t* buf) {
        data = buf;
    }

    std::string topic;
    uint8_t* data;
};