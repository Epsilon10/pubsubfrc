#include "publisher.hh"
#include "drivetrain_generated.h"
#include <iostream>

Publisher::Publisher(std::string name) : name(std::move(name)) { }

void Publisher::init() {
    thread = std::thread(&Publisher::run_periodic, this);
    // because the thread needs a virtual function, we can't have it in the ctor
}

Publisher::~Publisher() {
    is_running = false;
    mailbox.update();
    thread.join();
}

void Publisher::subscribe(Publisher& publisher) {
    auto it =
        std::find(publisher.sub_list.begin(), publisher.sub_list.end(), this);
    if (it == publisher.sub_list.end())
        publisher.sub_list.push_back(this);
}

void Publisher::unsubscribe(Publisher& publisher) {
    auto it =
        std::find(publisher.sub_list.begin(), publisher.sub_list.end(), this);
    if (it != publisher.sub_list.end())
        publisher.sub_list.erase(it);
}

void Publisher::run_periodic() {

    while (is_running) {
        Message m;
        
        if (mailbox.wait_and_pop(m, is_running)) {
            //std::cout << "in RP " << name << std::endl;

            auto x = Robot::Drivetrain::GetDrivetrainStatus(m.get_data());
            // std::cout << "vel heading: " << x->velocity()->heading() << std::endl;
            process_message(std::move(m));
        }

       // std::cout << "Hello from: " << name << std::endl;
        
    }
}

void Publisher::publish(Message&& msg) {
    for (auto sub : sub_list) {
        sub->mailbox.push(msg);
    }
}

void Publisher::disable() { is_running = false; }