#include "flatbuffers/flatbuffers.h"
#include <iostream>
#include <vector>

#include "drivetrain_generated.h"

using namespace Robot::Drivetrain;

#include "mpsc_queue.hh"

#include "message.hh"
#include "publisher.hh"
#include "dt_publisher.hh"

#include <chrono>

#include <thread>

using Clock = std::chrono::high_resolution_clock;

int main() {
    
    //delete[] buf_ptr;
    DrivetrainPublisher dt_1{"uno"};
    DrivetrainPublisher dt_2{"dos"};
    DrivetrainPublisher dt_3{"tres"};

    dt_1.init();
    dt_3.init();

    dt_2.init();

    //dt_3.subscribe(dt_1);
    dt_2.subscribe(dt_1);

    dt_1.subscribe(dt_2);
    dt_3.subscribe(dt_2);

    dt_3.subscribe(dt_1);
    flatbuffers::FlatBufferBuilder b{1024};

    Message m{"Drivetrain/DrivetrainStatus"};
    auto pos = Pose2D(1.0,2.0,3.0);
    auto vel = Pose2D(9999999.0,3.0,28213.1);

    auto x = CreateDrivetrainStatus(b, &pos, &vel);
    b.Finish(x);
    
    m.set_data(b.Release());
    
    dt_1.publish(std::move(m));
    b.Clear();


    Message m1{"Drivetrain/DrivetrainStatus"};
    auto pos1 = Pose2D(1.0,2.0,3.0);
    auto vel1 = Pose2D(424242.0,3.0,28213.1);

    auto x1 = CreateDrivetrainStatus(b, &pos1, &vel1);
    b.Finish(x1);
    
    m1.set_data(b.Release());

    dt_2.publish(std::move(m1));
    b.Clear();
    
    std::this_thread::sleep_for(std::chrono::seconds(4));

    return 0;
}