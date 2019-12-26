#include "flatbuffers/flatbuffers.h"
#include <iostream>
#include <vector>

#include "drivetrain_generated.h"

using namespace Robot::Drivetrain;

#include "mpsc_queue.hh"

#include "message.hh"


int main() {
    /*

    auto const weapon_one_name = builder.CreateString("Chad");
    short weapon_one_dmg = 3;

    auto const sword = CreateWeapon(builder, weapon_one_name, weapon_one_dmg);
    
    std::cout << "success" << std::endl;

    auto const name = builder.CreateString("Orc");

    uint8_t treasure[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto const inventory = builder.CreateVector(treasure, 10);

    std::vector<flatbuffers::Offset<Weapon>> weapons_vector;
    weapons_vector.push_back(sword);

    auto const weapons = builder.CreateVector(weapons_vector);

    Vec3 points[] = { Vec3(1.0f, 2.0f, 3.0f), Vec3(4.0f, 5.0f, 6.0f) };
    auto const path = builder.CreateVectorOfStructs(points, 2);
    */
   flatbuffers::FlatBufferBuilder builder{1024};

   DrivetrainStatusBuilder dt_status_builder{builder};

    auto pos = Pose2D(1.0,3.0,0.0);
    auto velocity = Pose2D(10.0, 3.7, 4.42);
    dt_status_builder.add_pos(&pos);
    dt_status_builder.add_velocity(&velocity);

    auto dt_status_msg = dt_status_builder.Finish();
    builder.Finish(dt_status_msg);

    uint8_t* buf = builder.GetBufferPointer();

    auto msg_ptr = GetDrivetrainStatus(buf);

    auto x_pos = msg_ptr->velocity()->x();
    std::cout << "X Pos: " << x_pos << std::endl;

    Message m;
    m.set_topic("DrivetrainStatus");
    m.set_data(buf);

    MpscQueue<Message*> queue;

    queue.push(&m);

    Message* pop_m;
    queue.wait_and_pop(pop_m);

    auto pop_msg_ptr = GetDrivetrainStatus(pop_m->data);

    auto x_pos_p = pop_msg_ptr->velocity()->x();
    std::cout << "X vel: " << x_pos_p << std::endl;
}