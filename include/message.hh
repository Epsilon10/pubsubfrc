#pragma once

#include <string>
#include <memory>


#include "flatbuffers/flatbuffers.h"

class Message {
    public:
    Message() = default;
    Message(std::string const& topic) : topic(topic) { }
    Message(Message&& other) = default;
    Message(Message const& other) = default;
    ~Message() = default;

    Message& operator=(Message&& other) {
        data = std::move(other.data);
        topic = std::move(other.topic);
        return *this;
    }

    void set_topic(std::string const& topic) {
        this->topic = topic;
    }

    void set_data(flatbuffers::DetachedBuffer&& buffer) {
        data = std::move(buffer);
    }

    const uint8_t* get_data() { return data.data(); }

    std::string topic;
    flatbuffers::DetachedBuffer data;
};