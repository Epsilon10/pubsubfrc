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

   const DrivetrainStatus* dt_msg_ptr;
   Message my_m;
   uint8_t* buf_ptr;

   { 
   flatbuffers::FlatBufferBuilder builder{1024};
   auto v = Pose2D(1.0,1.0,0.0);
   auto x = Pose2D(1.0,10.8,1119.3);

    auto obj_ptr = CreateDrivetrainStatus(builder, &v, &x);

    builder.Finish(obj_ptr);

    Message m{"dtstatus"};
    buf_ptr = builder.GetBufferPointer();
    m.set_data(buf_ptr);

    MpscQueue<Message> queue;
    queue.push(std::move(m));

    queue.wait_and_pop(my_m);
    
    dt_msg_ptr = GetDrivetrainStatus(my_m.data);

    std::cout << dt_msg_ptr->velocity()->heading() << std::endl;

    builder.Clear();
    std::cout << dt_msg_ptr->velocity()->heading() << std::endl;
    //free(buf_ptr);
   }
   std::cout << dt_msg_ptr->velocity()->heading() << std::endl;
    auto msg_ptr = GetDrivetrainStatus(buf_ptr);
    std::cout << *buf_ptr << std::endl;
    //delete[] buf_ptr;

    
}