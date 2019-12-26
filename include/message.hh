#pragma once

#include <string>

class Message {
    public:
    Message() = default;
    Message(Message&&) = delete;

    void set_topic(std::string const& topic) {
        this->topic = topic;
    }

    void set_data(uint8_t* buf) {
        data = buf;
    }

    std::string topic;
    uint8_t* data;
};