// ...existing code...
#include <cstdlib>
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/pose_array.hpp" // Keep this include
#include "my_robot_interfaces/msg/hardware_status.hpp"
// ...existing code...


class TemplatePublisher : public rclcpp::Node
{
public:
    TemplatePublisher() : Node("templatepublisher_node")
    {
        hardware_status_publisher_ = this->create_publisher<my_robot_interfaces::msg::HardwareStatus>("hardware_status", 10);
        timer_theanswer_ = this->create_wall_timer(
         std::chrono::milliseconds(1000), std::bind(&TemplatePublisher::timer_theanswer_function, this));
    }

    void timer_theanswer_function()
    {
        geometry_msgs::msg::PoseArray pose_array_msg;
        pose_array_msg.header.stamp = this->now();
        pose_array_msg.header.frame_id = "map";

        geometry_msgs::msg::Pose pose;
        pose.position.x = x_;
        pose.position.y = y_;
        pose.position.z = z_;
        pose.orientation.x = 0.0;
        pose.orientation.y = 0.0;
        pose.orientation.z = 0.0;
        pose.orientation.w = 1.0;

        pose_array_msg.poses.push_back(pose);

        publisher_theanswer_->publish(pose_array_msg);

        // Increment position for next message
        x_ += 1.0;
        y_ += 1.0;
        z_ += 1.0;
        // Publish hardware status
        auto msg = my_robot_interfaces::msg::HardwareStatus();
        msg.temperature = 34.5;
        msg.are_motors_ready = true;
        msg.debug_message = "Motors ready!";
        hardware_status_publisher_->publish(msg);
    };

private:
    rclcpp::Publisher<my_robot_interfaces::msg::HardwareStatus>::SharedPtr hardware_status_publisher_;
            rclcpp::Publisher<geometry_msgs::msg::PoseArray>::SharedPtr publisher_theanswer_;
        rclcpp::TimerBase::SharedPtr timer_theanswer_;
        double x_ = 1.0;
        double y_ = 2.0;
        double z_ = 0.0;
};

int main(int argc,char *argv[])
{
    rclcpp::init(argc,argv);
    auto node = std::make_shared<TemplatePublisher>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}