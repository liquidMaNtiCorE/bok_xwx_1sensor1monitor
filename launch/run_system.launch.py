from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='bok_xwx_1sensor1monitor',
            executable='sensor_node',
            name='sensor_node',
            output='screen'
        ),
        Node(
            package='bok_xwx_1sensor1monitor',
            executable='monitor_node',
            name='monitor_node',
            output='screen'
        ),
    ])