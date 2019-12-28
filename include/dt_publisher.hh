#pragma once

#include "drivetrain_generated.h"

#include "message.hh"

#include "publisher.hh"

using namespace Robot::Drivetrain;

class DrivetrainPublisher : public Publisher {
    public:
    DrivetrainPublisher();
    private:
    flatbuffers::FlatBufferBuilder msg_builder;
    void process_message(Message&& message) override;
};