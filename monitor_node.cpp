#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/temperature.hpp"
#include "std_msgs/msg/string.hpp"

class TempMonitorNode : public rclcpp::Node {
public:
    TempMonitorNode() : Node("monitor_node") {
        subscription_ = this->create_subscription<sensor_msgs::msg::Temperature>(
            "/temperature", 10,
            std::bind(&TempMonitorNode::temp_callback, this, std::placeholders::_1));
        alert_pub_ = this->create_publisher<std_msgs::msg::String>("/warning", 10);
        RCLCPP_INFO(this->get_logger(), "Monitor node started.");
    }

private:
    void temp_callback(const sensor_msgs::msg::Temperature::SharedPtr msg) {
        if (msg->temperature > 31.2) {
            auto alert = std_msgs::msg::String();
            alert.data = "Magas Homerseklet " + std::to_string(msg->temperature) + " °C!";
            RCLCPP_WARN(this->get_logger(), "%s", alert.data.c_str());
            alert_pub_->publish(alert);
        }
    }

    rclcpp::Subscription<sensor_msgs::msg::Temperature>::SharedPtr subscription_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr alert_pub_;
};

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<TempMonitorNode>());
    rclcpp::shutdown();
    return 0;
}