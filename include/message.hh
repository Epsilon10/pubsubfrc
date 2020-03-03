#pragma once

#include <string>
#include <memory>
#include <iostream>


#include "flatbuffers/flatbuffers.h"

class Message {
    public:
    Message() = default;
    Message(std::string const& topic) : topic(topic) { }
    Message(Message&& other) : topic(std::move(other.topic)), buffer_ptr(std::move(other.buffer_ptr)) {
    }
    Message(Message const& other) : topic(other.topic), buffer_ptr(other.buffer_ptr){
        std::cout << "copy called!" << std::endl;
    }
    ~Message() = default;

    Message& operator=(Message&& other) {
        buffer_ptr = std::move(other.buffer_ptr);
        topic = std::move(other.topic);
        return *this;
    }

    void set_topic(std::string new_topic) {
        this->topic = std::move(new_topic);
    }

    void set_data(flatbuffers::DetachedBuffer&& buffer) {
        buffer_ptr = std::make_shared<flatbuffers::DetachedBuffer>(std::move(buffer));
    }

    uint8_t const* get_data() { return buffer_ptr->data(); }

    std::string topic;
    std::shared_ptr<flatbuffers::DetachedBuffer> buffer_ptr;
};