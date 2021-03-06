#pragma once
#include <string>
#include <vector>
#include <atomic>

#include "mpsc_queue.hh"
#include "message.hh"

#include <thread>


class Publisher {
    public:
    Publisher() = default;
    Publisher(std::string name);
    virtual ~Publisher();
    void subscribe(Publisher& publisher);

    void unsubscribe(Publisher& publisher);

    void publish(Message&& msg);

    void run_periodic();

    void disable();

    void init();

    
    std::string name;
    private:
    std::vector<Publisher*> sub_list;
    
    MpscQueue<Message> mailbox;

    std::thread thread;
    std::atomic<bool> is_running{true};

    virtual void process_message(Message&& message) { std::cout << "virtual: " << name << std::endl; };
};