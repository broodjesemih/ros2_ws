// ...existing code...
#include <cstdlib>
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/pose_array.hpp" // Keep this include
// ...existing code...

class TemplatePublisher : public rclcpp::Node
{
    public:
    TemplatePublisher() : Node("templatepublisher_node")
    {	
        publisher_theanswer_ = this->create_publisher<geometry_msgs::msg::PoseArray>("the_answer", 10);
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
    }

    private:
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