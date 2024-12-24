#include <ros/ros.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Twist.h>
#include <stdio.h>

// Mensajes
geometry_msgs::Twist optiD1_msg;
geometry_msgs::Twist optiD2_msg;
geometry_msgs::Twist optiD3_msg;

// Posición y ángulos (optitrack)
// Drone1
double xD1 = 0.0;
double yD1 = 0.0;
double zD1 = 0.0;
double q01 = 0.0;
double q11 = 0.0;
double q21 = 0.0;
double q31 = 0.0;
double rollD1 = 0.0;
double pitchD1 = 0.0;
double yawD1 = 0.0;
// Drone2
double xD2 = 0.0;
double yD2 = 0.0;
double zD2 = 0.0;
double q02 = 0.0;
double q12 = 0.0;
double q22 = 0.0;
double q32 = 0.0;
double rollD2 = 0.0;
double pitchD2 = 0.0;
double yawD2 = 0.0;
// Drone3
double xD3 = 0.0;
double yD3 = 0.0;
double zD3 = 0.0;
double q03 = 0.0;
double q13 = 0.0;
double q23 = 0.0;
double q33 = 0.0;
double rollD3 = 0.0;
double pitchD3 = 0.0;
double yawD3 = 0.0;

void optiD1_callback(const geometry_msgs::Pose& msg1){
	xD1 = -msg1.position.y;
	yD1 = msg1.position.x;
	zD1 = msg1.position.z;
	q11 = -msg1.orientation.y;
	q21 = msg1.orientation.x;
	q31 = msg1.orientation.z;
	q01 = msg1.orientation.w;
}

void optiD2_callback(const geometry_msgs::Pose& msg2){
	xD2 = -msg2.position.y;
	yD2 = msg2.position.x;
	zD2 = msg2.position.z;
	q12 = -msg2.orientation.y;
	q22 = msg2.orientation.x;
	q32 = msg2.orientation.z;
	q02 = msg2.orientation.w;
}

void optiD3_callback(const geometry_msgs::Pose& msg3){
	xD3 = -msg3.position.y;
	yD3 = msg3.position.x;
	zD3 = msg3.position.z;
	q13 = -msg3.orientation.y;
	q23 = msg3.orientation.x;
	q33 = msg3.orientation.z;
	q03 = msg3.orientation.w;
}

int main(int argc, char** argv){

	// ROS Publishers y Subscriber
	ros::Publisher pub_optiD1;
	ros::Publisher pub_optiD2;
	ros::Publisher pub_optiD3;
	ros::Subscriber sub_optiD1;
	ros::Subscriber sub_optiD2;
	ros::Subscriber sub_optiD3;
	
	ROS_INFO("Optitrack. Prueba net 3 Drones");
	ros::init(argc, argv,"Opti_net3");
    ros::NodeHandle n;
    
    sub_optiD1 = n.subscribe("/Drone1/pose", 1, optiD1_callback);
    sub_optiD2 = n.subscribe("/Drone2/pose", 1, optiD2_callback);
    sub_optiD3 = n.subscribe("/Drone3/pose", 1, optiD3_callback);
    pub_optiD1 = n.advertise<geometry_msgs::Twist>("/optiD1", 1);
    pub_optiD2 = n.advertise<geometry_msgs::Twist>("/optiD2", 1);
    pub_optiD3 = n.advertise<geometry_msgs::Twist>("/optiD3", 1);
    
    ROS_INFO("Iniciando prueba mocap...");
    
    ros::Rate loop_rate(100);
    while(ros::ok()){
		// Grados
		//roll1 = (atan2(((2*q21*q31)+(2*q01*q11)),((2*q01*q01)+(2*q31*q31)-1))*(180/3.14159));
		//pitch1 = (-asin((2*q11*q31)-(2*q01*q21))*(180/3.14159));
		//yaw1 = (atan2(((2*q11*q21)+(2*q01*q31)),((2*q01*q01)+(2*q11*q11)-1))*(180/3.14159));
		
		//roll2 = (atan2(((2*q22*q32)+(2*q02*q12)),((2*q02*q02)+(2*q32*q32)-1))*(180/3.14159));
		//pitch2 = (-asin((2*q12*q32)-(2*q012*q22))*(180/3.14159));
		//yaw2 = (atan2(((2*q12*q22)+(2*q02*q32)),((2*q02*q02)+(2*q12*q12)-1))*(180/3.14159));
		
		// Radianes
		rollD1 = (atan2(((2*q21*q31)+(2*q01*q11)),((2*q01*q01)+(2*q31*q31)-1)));
		pitchD1 = (-asin((2*q11*q31)-(2*q01*q21)));
		yawD1 = (atan2(((2*q11*q21)+(2*q01*q31)),((2*q01*q01)+(2*q11*q11)-1)));
		
		rollD2 = (atan2(((2*q22*q32)+(2*q02*q12)),((2*q02*q02)+(2*q32*q32)-1)));
		pitchD2 = (-asin((2*q12*q32)-(2*q02*q22)));
		yawD2 = (atan2(((2*q12*q22)+(2*q02*q32)),((2*q02*q02)+(2*q12*q12)-1)));
		
		rollD3 = (atan2(((2*q23*q33)+(2*q03*q13)),((2*q03*q03)+(2*q33*q33)-1)));
		pitchD3 = (-asin((2*q13*q33)-(2*q03*q23)));
		yawD3 = (atan2(((2*q13*q23)+(2*q03*q33)),((2*q03*q03)+(2*q13*q13)-1)));
		
		optiD1_msg.linear.x = xD1;
		optiD1_msg.linear.y = yD1;
		optiD1_msg.linear.z = zD1;
		optiD1_msg.angular.x = rollD1;
		optiD1_msg.angular.y = pitchD1;
		optiD1_msg.angular.z = yawD1;
		pub_optiD1.publish(optiD1_msg);
		
		optiD2_msg.linear.x = xD2;
		optiD2_msg.linear.y = yD2;
		optiD2_msg.linear.z = zD2;
		optiD2_msg.angular.x = rollD2;
		optiD2_msg.angular.y = pitchD2;
		optiD2_msg.angular.z = yawD2;
		pub_optiD2.publish(optiD2_msg);
		
		optiD3_msg.linear.x = xD3;
		optiD3_msg.linear.y = yD3;
		optiD3_msg.linear.z = zD3;
		optiD3_msg.angular.x = rollD3;
		optiD3_msg.angular.y = pitchD3;
		optiD3_msg.angular.z = yawD3;
		pub_optiD3.publish(optiD3_msg);

		//ROS_INFO("Datos recibidos:\n");
		//ROS_INFO("posición:\nx = %f\ny = %f\nz = %f\n\nOrientación:\nq0 = %f\nq1 = %f\nq2 = %f\nq3 = %f\n\n", x, y, z, q0, q1, q2, q3);
		printf("Datos del optitrack\n");
		//printf("x: %f \t y: %f \t z: %f \n q0: %f \t q1: %f \t q2: %f \t q3: %f \n", x, y, z, q0, q1, q2, q3);
		printf("Drone1:\n");
		printf("x1: %lf \t y1: %lf \t z1: %lf \n roll1: %lf \t pitch1: %lf \t yaw1: %lf \n", xD1, yD1, zD1, rollD1, pitchD1, yawD1);
		printf("Drone2:\n");
		printf("x2: %lf \t y2: %lf \t z2: %lf \n roll2: %lf \t pitch2: %lf \t yaw2: %lf \n", xD2, yD2, zD2, rollD2, pitchD2, yawD2);
		printf("Drone3:\n");
		printf("x3: %lf \t y3: %lf \t z3: %lf \n roll3: %lf \t pitch3: %lf \t yaw3: %lf \n", xD3, yD3, zD3, rollD3, pitchD3, yawD3);
		ros::spinOnce();
		loop_rate.sleep();
	}
	ROS_INFO("Prueba mocap finalizada.");
    
    return 0;
}
