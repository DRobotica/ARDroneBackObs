#include <ros/ros.h>
#include <cereal_port/CerealPort.h>
#include <serial_port/Optidata.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <math.h>

serial_port::Optidata opti_msg;

#define LEN sizeof(float)
#define TIMEOUT 500

union data{
  float num;
  char bytes[LEN];
};

data x,y,z,roll,pitch,yaw;
//data x2,y2,z2,roll2,pitch2,yaw2;
//double q0,q1,q2,q3;

//float x, y, z, phi, theta, psi;
//int xp1, xp2, yp1, yp2, zp1, zp2, phip1, phip2, thetap1, thetap2, psip1, psip2;

/*float unir(int p1, int p2){
	float n = 0.0;
	
	n = (float)p1 + (((float)p2)/100);
	n = (float)n/10;
				
	if(n >= 10.0){
		n = (n - 10.0)*(-1);
	}
	return n;
}*/

/*void obtener(){
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
}*/

// This example opens the serial port and sends a request 'R' at 1Hz and waits for a reply.
int main(int argc, char** argv){
    ros::init(argc, argv, "example_node");
    ros::NodeHandle n;
    
    ros::Publisher pub_opti;

    cereal::CerealPort device;
    //std::string *buffer;
    unsigned int i = 0, j = 0;

    char buffer[LEN*6];
    //char buffero[REPLY_SIZE];
    
    pub_opti = n.advertise<serial_port::Optidata>("/optitrack", 1);

    // Change the next line according to your port name and baud rate
    try{ 
		device.open("/dev/ttyUSB0", 57600);
	}catch(cereal::Exception& e){
        ROS_FATAL("Error al abrir el puerto serie!!!");
        ROS_BREAK();
    }
    ROS_INFO("El puerto serie esta abierto.");
    
    /*obtener();
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
	}*/

    ros::Rate r(100);
    while(ros::ok()){
        // Send over the serial port
        //device.write(buffero,LEN*6);
		//ROS_INFO("Datos enviados:\n");
		//ROS_INFO("x = %lf, y = %lf, z = %lf\nroll = %lf, pitch = %lf, yaw = %lf\n",x.num,y.num,z.num,roll.num,pitch.num,yaw.num);
		
        // Get the reply, the last value is the timeout in ms
        try{
			device.readBytes(buffer,LEN*6, TIMEOUT);
			
			ROS_INFO("Se ha leido del puerto.\n");
			
			/*xp1 = (int)buffer[0];
			xp2 = (int)buffer[1];
			yp1 = (int)buffer[2];
			yp2 = (int)buffer[3];
			zp1 = (int)buffer[4];
			zp2 = (int)buffer[5];
			phip1 = (int)buffer[6];
			phip2 = (int)buffer[7];
			thetap1 = (int)buffer[8];
			thetap2 = (int)buffer[9];
			psip1 = (int)buffer[10];
			psip2 = (int)buffer[11];
			
			x = unir(xp1, xp2);
			y = unir(yp1, yp2);
			z = unir(zp1, zp2);
			phi = unir(phip1, phip2);
			theta = unir(thetap1, thetap2);
			psi = unir(psip1, psip2);*/

			j = 0;
			for(i = 0;i < LEN;i++){
				x.bytes[j] = buffer[i];
				j++;
			}
			j = 0;
			for(i = LEN;i < LEN*2;i++){
				y.bytes[j] = buffer[i];
				j++;
			}
			j = 0;
			for(i = LEN*2;i < LEN*3;i++){
				z.bytes[j] = buffer[i];
				j++;
			}
			j = 0;
			for(i = LEN*3;i < LEN*4;i++){
				roll.bytes[j] = buffer[i];
				j++;
			}
			j = 0;
			for(i = LEN*4;i < LEN*5;i++){
				pitch.bytes[j] = buffer[i];
				j++;
			}
			j = 0;
			for(i = LEN*5;i < LEN*6;i++){
				yaw.bytes[j] = buffer[i];
				j++;
			}
			
			//positivos();
			
			opti_msg.x = x.num;
			opti_msg.y = y.num;
			opti_msg.z = z.num;
			opti_msg.roll = roll.num;
			opti_msg.pitch = pitch.num;
			opti_msg.yaw = yaw.num;
			pub_opti.publish(opti_msg);

			ROS_INFO("Datos recibidos:\n");
			ROS_INFO("x = %f, y = %f, z = %f\nroll = %f, pitch = %f, yaw = %f\n", x.num, y.num, z.num, roll.num, pitch.num, yaw.num);
		}catch(cereal::TimeoutException& e){
            ROS_ERROR("Timeout!");
        }
        

        ros::spinOnce();
        r.sleep();
    } 
    
    device.close();
    ROS_INFO("El puerto serie se ha cerrado.\n");
    
    return 0;
}
