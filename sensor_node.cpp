#include <chrono>
#include <memory>

#include <random>
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/temperature.hpp"

using namespace std;

class TempSensorNode : public rclcpp::Node {
public:
    TempSensorNode() : Node("sensor_node"), gen_(rd_()), dist_(18.0, 35.0) {
        publisher_ = this->create_publisher<sensor_msgs::msg::Temperature>("/temperature", 10);
        timer_ = this->create_wall_timer(1000ms, std::bind(&TempSensorNode::publish_temp, this));
        RCLCPP_INFO(this->get_logger(), "Sensor node started.");
    }

private:
    void publish_temp() {
        auto msg = sensor_msgs::msg::Temperature();
        msg.header.stamp = this->now();
        msg.header.frame_id = "temp_sensor_link";
        msg.temperature = dist_(gen_);
        msg.variance = 0.1;

        RCLCPP_INFO(this->get_logger(), "The temperature: %.2f  °C", msg.temperature);
        publisher_->publish(msg);
    }

    rclcpp::Publisher<sensor_msgs::msg::Temperature>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    std::random_device rd_;
    std::mt19937 gen_;
    std::uniform_real_distribution<double> dist_;
};

int main(int argc, char* argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<TempSensorNode>());
    rclcpp::shutdown();
    return 0;
}