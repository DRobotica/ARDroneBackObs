/*
Jesús Santiaguillo Salinas
Ing. Eléctrica, Mecatrónica - CINVESTAV

Programa para aterrizar el AR.Drone 2.0
*/
#include <ros/ros.h>
#include <std_msgs/Empty.h>
	
int main(int argc, char** argv){
	ROS_INFO("ARdrone Aterrizar");
	ros::init(argc, argv,"ARDrone_aterrizarD1"); //inicia el nodo
	
	//Editor ROS
	ros::Publisher pub_empty;
	//Variables ROS
	ros::NodeHandle node; //nodo
	std_msgs::Empty emp_msg; //mensaje
	//Variables tiempo
	double start_time = 0.0;
	double land_time = 5.0;
	double t = 0;

	pub_empty = node.advertise<std_msgs::Empty>("/Drone1/ardrone/land", 1); //asocia el topic
	
	start_time = (double)ros::Time::now().toSec();
	ros::Rate loop_rate(50); //establece la frecuencia del nodo
 	while(ros::ok()){
		t = (double)ros::Time::now().toSec() - start_time;
		
		if(t <= land_time){
			pub_empty.publish(emp_msg); //publica el mensaje
			
			ROS_INFO("ARdrone Aterrizando");
		}else{
			ROS_INFO("ARdrone Aterrizado");
			
			break;
		}
		
		ros::spinOnce(); //refresca los datos
		loop_rate.sleep(); //espera a que se cumpla la frecuencia
	}
	
	ROS_INFO("AR.Drone Aterrizar Finalizado.");
	
	return 0;
}
