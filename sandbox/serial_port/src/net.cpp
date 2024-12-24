#include <ros/ros.h>
#include <geometry_msgs/Pose.h>
#include <serial_port/Optidata.h>
#include <stdio.h>

// Mensajes
//geometry_msgs::Pose pose_msg;
serial_port::Optidata opti_msg;

// Posición y ángulos (optitrack)
float x = 0.0;
float y = 0.0;
float z = 0.0;
float q0 = 0.0;
float q1 = 0.0;
float q2 = 0.0;
float q3 = 0.0;
float roll = 0.0;
float pitch = 0.0;
float yaw = 0.0;

void opti_callback(const geometry_msgs::Pose& msg){
	//pose_msg = msg;
	x = -msg.position.y;
	y = msg.position.x;
	z = msg.position.z;
	q1 = -msg.orientation.y;
	q2 = msg.orientation.x;
	q3 = msg.orientation.z;
	q0 = msg.orientation.w;
	//ROS_INFO("x = %lf, y = %lf, z = %lf\nroll = %lf, pitch = %lf, yaw = %lf\n",msg.x,msg.y,msg.z,msg.roll,msg.pitch,msg.yaw);
}

int main(int argc, char** argv){

	// ROS Publishers y Subscriber
	ros::Publisher pub_opti;
	ros::Subscriber sub_opti;
	
	ROS_INFO("Optitrack. Prueba net");
	ros::init(argc, argv,"Opti_net");
    ros::NodeHandle n;
    
    sub_opti = n.subscribe("/Drone1/pose", 1, opti_callback);
    pub_opti = n.advertise<serial_port::Optidata>("/optitrack", 1);
    
    ROS_INFO("Iniciando prueba mocap...");
    
    ros::Rate loop_rate(100);
    while(ros::ok()){
		// Grados
		//roll = (float)(atan2(((2*q2*q3)+(2*q0*q1)),((2*q0*q0)+(2*q3*q3)-1))*(180/3.14159));
		//pitch = (float)(-asin((2*q1*q3)-(2*q0*q2))*(180/3.14159));
		//yaw = (float)(atan2(((2*q1*q2)+(2*q0*q3)),((2*q0*q0)+(2*q1*q1)-1))*(180/3.14159));
		
		// Radianes
		roll = (float)(atan2(((2*q2*q3)+(2*q0*q1)),((2*q0*q0)+(2*q3*q3)-1)));
		pitch = (float)(-asin((2*q1*q3)-(2*q0*q2)));
		yaw = (float)(atan2(((2*q1*q2)+(2*q0*q3)),((2*q0*q0)+(2*q1*q1)-1)));
		
		opti_msg.x = x;
		opti_msg.y = y;
		opti_msg.z = z;
		opti_msg.roll = roll;
		opti_msg.pitch = pitch;
		opti_msg.yaw = yaw;
		pub_opti.publish(opti_msg);

		//ROS_INFO("Datos recibidos:\n");
		//ROS_INFO("posición:\nx = %f\ny = %f\nz = %f\n\nOrientación:\nq0 = %f\nq1 = %f\nq2 = %f\nq3 = %f\n\n", x, y, z, q0, q1, q2, q3);
		printf("Datos del optitrack\n");
		//printf("x: %f \t y: %f \t z: %f \n q0: %f \t q1: %f \t q2: %f \t q3: %f \n", x, y, z, q0, q1, q2, q3);
		printf("x: %f \t y: %f \t z: %f \n roll: %f \t pitch: %f \t yaw: %f \n", x, y, z, roll, pitch, yaw);
		ros::spinOnce();
		loop_rate.sleep();
	}
	ROS_INFO("Prueba mocap finalizada.");
    
    return 0;
}
