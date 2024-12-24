#include <ros/ros.h>
#include <cereal_port/CerealPort.h>
#include <serial_port/Optidata.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <math.h>

//serial_port::Optidata opti_msg;

#define LEN sizeof(double)
#define TIMEOUT 1

union data{
  double num;
  char bytes[LEN];
};

data x,y,z,roll,pitch,yaw;
data x2,y2,z2,roll2,pitch2,yaw2;
double q0,q1,q2,q3;

void obtener(){
	x.num = 2555.567892;
	y.num = -1768.764532;
	z.num = 1289.468790;
	q0 = 0.5;
	q1 = 0.5;
	q2 = 0.5;
	q3 = 0.5;

	roll.num = atan2(((2*q2*q3)+(2*q0*q1)),((2*q0*q0)+(2*q3*q3)-1));	
	pitch.num = (-asin((2*q1*q3)-(2*q0*q2)));
	yaw.num = atan2(((2*q1*q2)+(2*q0*q3)),((2*q0*q0)+(2*q1*q1)-1));
}

// This example opens the serial port and sends a request 'R' at 1Hz and waits for a reply.
int main(int argc, char** argv){
    ros::init(argc, argv, "example_node");
    ros::NodeHandle n;
    
    //ros::Publisher pub_opti;

    cereal::CerealPort device;
    //std::string *buffer;
    unsigned int i,j;

    char bufferi[LEN*6];
    char buffero[LEN*6];
    
    //pub_opti = n.advertise<serial_port::Optidata>("/optitrack", 1);

    // Change the next line according to your port name and baud rate
    try{ 
		device.open("/dev/ttyUSB0", 57600);
	}catch(cereal::Exception& e){
        ROS_FATAL("Error al abrir el puerto serie!!!");
        ROS_BREAK();
    }
    ROS_INFO("El puerto serie esta abierto.");
    
    obtener();
	j = 0;
	for(i = 0;i < LEN;i++){
		buffero[i] = x.bytes[j];
		j++;
	}
	j = 0;
	for(i = LEN;i < LEN*2;i++){
		buffero[i] = y.bytes[j];
		j++;
	}
	j = 0;
	for(i = LEN*2;i < LEN*3;i++){
		buffero[i] = z.bytes[j];
		j++;
	}
	j = 0;
	for(i = LEN*3;i < LEN*4;i++){
		buffero[i] = roll.bytes[j];
		j++;
	}
	j = 0;
	for(i = LEN*4;i < LEN*5;i++){
		buffero[i] = pitch.bytes[j];
		j++;
	}
	j = 0;
	for(i = LEN*5;i < LEN*6;i++){
		buffero[i] = yaw.bytes[j];
		j++;
	}

    ros::Rate r(50);
    while(ros::ok()){
        // Send over the serial port
        device.write(buffero,LEN*6);
		ROS_INFO("Datos enviados:\n");
		ROS_INFO("x = %lf, y = %lf, z = %lf\nroll = %lf, pitch = %lf, yaw = %lf\n",x.num,y.num,z.num,roll.num,pitch.num,yaw.num);
		
        // Get the reply, the last value is the timeout in ms
        try{
			device.readBytes(bufferi,LEN*6, TIMEOUT);
		}catch(cereal::TimeoutException& e){
            ROS_ERROR("Timeout!");
        }
        ROS_INFO("Se ha leido del puerto.\n");

		j = 0;
		for(i = 0;i < LEN;i++){
			x2.bytes[j] = bufferi[i];
			j++;
		}
		j = 0;
		for(i = LEN;i < LEN*2;i++){
			y2.bytes[j] = bufferi[i];
			j++;
		}
		j = 0;
		for(i = LEN*2;i < LEN*3;i++){
			z2.bytes[j] = bufferi[i];
			j++;
		}
		j = 0;
		for(i = LEN*3;i < LEN*4;i++){
			roll2.bytes[j] = bufferi[i];
			j++;
		}
		j = 0;
		for(i = LEN*4;i < LEN*5;i++){
			pitch2.bytes[j] = bufferi[i];
			j++;
		}
		j = 0;
		for(i = LEN*5;i < LEN*6;i++){
			yaw2.bytes[j] = bufferi[i];
			j++;
		}
		
		/*opti_msg.x = x2.num;
		opti_msg.y = y2.num;
		opti_msg.z = z2.num;
		opti_msg.roll = roll2.num;
		opti_msg.pitch = pitch2.num;
		opti_msg.yaw = yaw2.num;
		pub_opti.publish(opti_msg);*/

		ROS_INFO("Datos recibidos:\n");
		ROS_INFO("x = %lf, y = %lf, z = %lf\nroll = %lf, pitch = %lf, yaw = %lf\n",x2.num,y2.num,z2.num,roll2.num,pitch2.num,yaw2.num);

        ros::spinOnce();
        r.sleep();
    } 
    
    device.close();
    ROS_INFO("El puerto serie se ha cerrado.\n");
    
    return 0;
}
