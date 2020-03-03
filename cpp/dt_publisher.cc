#include "dt_publisher.hh"
#include <iostream>
DrivetrainPublisher::DrivetrainPublisher(std::string name) : Publisher(name), msg_builder(1024) {}

void DrivetrainPublisher::process_message(Message&& message) {
    if (message.topic == "Drivetrain/DrivetrainStatus") {
        auto drivetrain_status_msg = GetDrivetrainStatus(message.get_data());
        std::cout << "Drivetrain " << name << " Recieved message with x velocity: " 
            << drivetrain_status_msg->velocity()->x() << std::endl;
    }

    // lets send some messages too (in practice this wont be the case)
    // messages will be sent from a seperate loop

    auto pos = Pose2D(1.0,3.0,4.8);
    auto vel = Pose2D(1.0,2.0,3.0);

    auto msg = CreateDrivetrainStatus(msg_builder, &pos, &vel);
    msg_builder.Finish(msg);

    Message msg_obj{"Drivetrain/DrivetrainStatus"};
    msg_obj.set_data(msg_builder.Release());
    msg_builder.Clear(); 

    // publish(std::move(msg_obj));
    
}