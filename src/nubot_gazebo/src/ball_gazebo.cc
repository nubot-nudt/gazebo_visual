#include "ball_gazebo.hh"

#define idx_X 1
#define idx_Y 0
#define idx_w 3

#define Button_A    0
#define Button_B    1
#define Button_X    2
#define Button_Y    3

#define Button_Up   5
#define Button_Down 4

using namespace gazebo;
GZ_REGISTER_MODEL_PLUGIN(BallGazebo)

BallGazebo::BallGazebo()
{}

BallGazebo::~BallGazebo()
{}

void BallGazebo::Load(physics::ModelPtr _parent, sdf::ElementPtr /*_sdf*/)
{
    world_ = _parent->GetWorld();
    ball_model_ = _parent;
    rosnode_ = new ros::NodeHandle();

    joy_sub_ =rosnode_->subscribe<sensor_msgs::Joy>("joy", 2, &BallGazebo::joyCallback, this);

    update_connection_ = event::Events::ConnectWorldUpdateBegin(
        boost::bind(&BallGazebo::UpdateChild, this));
}

void BallGazebo::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
    /*速度指令*/
    vel_y_ = joy->axes[idx_X]*5;
    vel_x_ = -joy->axes[idx_Y]*5;
}

void BallGazebo::UpdateChild()
{
    static math::Vector3 ball_vel(0, 0, 0);
    if(std::sqrt(vel_x_*vel_x_+vel_y_*vel_y_)>1)
    {
      ball_vel.Set(vel_x_, vel_y_, 0);
      ball_model_->SetLinearVel(ball_vel);
//      ROS_WARN("vel_x_%f vel_y_:%f",vel_x_, vel_y_);
    }
}
