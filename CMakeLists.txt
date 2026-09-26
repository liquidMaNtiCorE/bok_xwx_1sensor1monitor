cmake_minimum_required(VERSION 3.8)
project(bok_xwx_1sensor1monitor)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(std_msgs REQUIRED)

add_executable(sensor_node sensor_node.cpp)
ament_target_dependencies(sensor_node rclcpp sensor_msgs)

add_executable(monitor_node monitor_node.cpp)
ament_target_dependencies(monitor_node rclcpp sensor_msgs std_msgs)

install(TARGETS
  sensor_node
  monitor_node
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

ament_package()