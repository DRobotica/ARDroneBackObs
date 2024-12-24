#include <ros/ros.h>
#include <serial_port/Optidata.h>
#include <stdio.h>

void opti_callback(const serial_port::Optidata& msg){
	ROS_INFO("x = %lf, y = %lf, z = %lf\nroll = %lf, pitch = %lf, yaw = %lf\n",msg.x,msg.y,msg.z,msg.roll,msg.pitch,msg.yaw);
}

int main(int argc, char** argv){
    ros::init(argc, argv, "example_node2");
    ros::NodeHandle n;
    
    ros::Subscriber sub_opti;
    
    sub_opti = n.subscribe("/optitrack", 1, opti_callback);
    
    ros::spin();
    
    return 0;
}
