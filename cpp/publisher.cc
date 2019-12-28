#include "publisher.hh"

Publisher::Publisher(std::string name) : name(std::move(name)),
    thread(&Publisher::run_periodic, this) { }

void Publisher::subscribe(Publisher* publisher) {
    auto it =
        std::find(publisher->sub_list.begin(), publisher->sub_list.end(), this);
    if (it == publisher->sub_list.end())
        publisher->sub_list.push_back(publisher);
}

void Publisher::unsubscribe(Publisher* publisher) {
    auto it =
        std::find(publisher->sub_list.begin(), publisher->sub_list.end(), this);
    if (it != publisher->sub_list.end())
        publisher->sub_list.erase(it);
}

void Publisher::run_periodic() {
    Message m;
    mailbox.wait_and_pop(m);

    process_message(std::move(m));
}

void Publisher::publish(Message&& msg) {
    for (auto sub : sub_list) {
        sub->mailbox.push(std::move(msg));
    }
}