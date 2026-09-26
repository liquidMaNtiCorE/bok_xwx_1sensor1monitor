from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='<repo_neved>',
            executable='temp_sensor_node',
            name='sensor_node',
            output='screen'
        ),
        Node(
            package='<repo_neved>',
            executable='temp_monitor_node',
            name='monitor_node',
            output='screen'
        ),
    ])