/*
--Node description: 
This node subscribes to the "the_answer" topic and prints all received PoseArray messages to the terminal using Logger.
*/ 

/*
--Software changes:
one line per change 
(1) created 31.3.2025: developer-Tilmann Koster reviewer(s)-Niek Ottens 
(2) changed 01.4.2025: updated to subscribe to PoseArray : developer-Tilmann Koster reviewer(s)-Niek Ottens 
*/

//-- tester: Sander Gieling

//--general includes 
#include <cstdlib>
#include "rclcpp/rclcpp.hpp"

//--custom includes 
#include "geometry_msgs/msg/pose_array.hpp" // Keep this include
#include "my_robot_interfaces/msg/hardware_status.hpp"

//--using 
using namespace std::placeholders;

//--Node class 
class TemplateSubscriber : public rclcpp::Node
{
  public:
  //-- constuctor: 
  TemplateSubscriber(): Node("templatesubscriber_node")
  {
     //--communication and timer objects: 
    subscriber_theanswer_ = this->create_subscription<geometry_msgs::msg::PoseArray>(
      "the_answer", 10,
      std::bind(&TemplateSubscriber::subscriber_theanswer_callback, this, _1));
  }

  //-- communication and timer functions 
  void subscriber_theanswer_callback(const geometry_msgs::msg::PoseArray::SharedPtr msg)
  { 
    RCLCPP_INFO(this->get_logger(), "Received PoseArray with %zu poses (frame_id: %s)", 
                msg->poses.size(), msg->header.frame_id.c_str());
    for (size_t i = 0; i < msg->poses.size(); ++i) {
      const auto & pose = msg->poses[i];
      RCLCPP_INFO(this->get_logger(), 
        "Pose %zu: position=(%.2f, %.2f, %.2f) orientation=(%.2f, %.2f, %.2f, %.2f)",
        i,
        pose.position.x, pose.position.y, pose.position.z,
        pose.orientation.x, pose.orientation.y, pose.orientation.z, pose.orientation.w
      );
    }
  }
  // ...existing code...
private:
  //--rclcpp variables:
  rclcpp::Subscription<geometry_msgs::msg::PoseArray>::SharedPtr subscriber_theanswer_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<TemplateSubscriber>();
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}