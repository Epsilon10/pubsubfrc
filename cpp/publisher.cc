#include "publisher.hh"

Publisher::Publisher(std::string name) 
    : name(std::move(name)) { }

void Publisher::subscribe(Publisher* publisher) {
    auto it =
        std::find(publisher->sub_list.begin(), publisher->sub_list.end(), this);
    publisher->sub_list.push_back(publisher);
}

void Publisher::unsubscribe(Publisher* publisher) {
    auto it =
        std::find(publisher->sub_list.begin(), publisher->sub_list.end(), this);
    if (it != publisher->sub_list.end())
        publisher->sub_list.erase(it);
}

void Publisher::run_periodic() {
    Message* m;
    mailbox.wait_and_pop(m);

    process_message(m);
}