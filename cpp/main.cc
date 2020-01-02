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

using Clock = std::chrono::high_resolution_clock;

int main() {
    
    //delete[] buf_ptr;
    DrivetrainPublisher dt_1;
    DrivetrainPublisher dt_2;
    DrivetrainPublisher dt_3;

    dt_1.init();
    dt_2.init();
    dt_3.init();

    dt_1.subscribe(dt_2);
    dt_2.subscribe(dt_3);
    dt_3.subscribe(dt_1);
    dt_3.subscribe(dt_2);

    Message m{"Hoesmade"};
    flatbuffers::FlatBufferBuilder b{1024};
    auto pos = Pose2D(1.0,2.0,3.0);
    auto vel = Pose2D(1.0,3.0,28213.1);

    auto x = CreateDrivetrainStatus(b, &pos, &vel);
    b.Finish(x);
    m.set_data(b.Release());

    dt_1.publish(std::move(m));
    std::cout << "thot\n";


}