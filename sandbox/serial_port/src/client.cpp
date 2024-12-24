//--Librerias ROS--
#include <ros/ros.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Twist.h>
//--Librerias C--
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>
#include <sys/time.h>
//--Mensajes--
geometry_msgs::Twist optiD3_msg;
geometry_msgs::Twist optiD2_msg;

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
//--Socket--
    int sockfd, portno, n;
    char* robot_actual="robot1";
    char* robot_a_seguir="robot2";
    char* servidor="10.0.126.6";
    char* puerto="20001";
    struct sockaddr_in serv_addr;
    struct hostent *server;

//Estructura optitrack
    struct Objeto_optitrack{
	double xr,yr,zr;
	double phi,theta,psi;
	}ob1;
//    const char* ob1_char=(const char*)&ob1;
    char* ob1_char=(char*)&ob1;
    int ob1_length=sizeof(ob1);

    double xr1;
    const char* xr1_char=(const char*)&xr1;
    int xr1_length=sizeof(xr1);

    char buffer[256];
//variables de tiempo
     struct timeval start, end;
     long mtime, seconds, useconds; 
     start.tv_sec=0;
     start.tv_usec=0;
     end.tv_sec=0;
     end.tv_usec=0;
     int tmax=30*1000;
     int contador=0;

    portno = atoi(puerto);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(servidor);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

    gettimeofday(&start, NULL);
//--ROS--
    ros::Publisher pub_optiD3;
    ros::Publisher pub_optiD2;

    ROS_INFO("Optitrack. Prueba cliente servidor");
    ros::init(argc, argv,"Client_Server");
    ros::NodeHandle nodo;
    
    pub_optiD3 = nodo.advertise<geometry_msgs::Twist>("/optiD3", 1);
    pub_optiD2 = nodo.advertise<geometry_msgs::Twist>("/optiD2", 1);
    
    ROS_INFO("Iniciando prueba cliente servidor...");
//--Programa principal
ros::Rate loop_rate(100);
//while((int)mtime<tmax){
  while(ros::ok()){
//system("clear");
//gettimeofday(&start, NULL);
    strcpy(buffer,robot_actual);
    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0) 
         error("ERROR writing to socket");
//    bzero(buffer,256);
//    n = read(sockfd, buffer, 255);
    n = read(sockfd, ob1_char, ob1_length);
    if (n < 0) 
         error("ERROR reading from socket");
	
    optiD3_msg.linear.x =  ob1.xr;
    optiD3_msg.linear.y =  ob1.yr;
    optiD3_msg.linear.z = ob1.zr;
    optiD3_msg.angular.x = ob1.phi;
    optiD3_msg.angular.y = ob1.theta;
    optiD3_msg.angular.z = ob1.psi;
    pub_optiD3.publish(optiD3_msg);

    printf("x del robot: %f\n", ob1.xr);
    printf("y del robot: %f\n", ob1.yr);
    printf("z del robot: %f\n", ob1.zr);
    printf("pitch del robot: %f\n", ob1.phi);
    printf("roll  del robot: %f\n", ob1.theta);
    printf("yaw   del robot: %f\n\n", ob1.psi);
//Datos del robot a seguir--
    strcpy(buffer,robot_a_seguir);
    n = write(sockfd, buffer, strlen(buffer));
    if (n < 0) 
         error("ERROR writing to socket");
//    bzero(buffer,256);
//    n = read(sockfd, buffer, 255);
    n = read(sockfd, ob1_char, ob1_length);
    if (n < 0) 
         error("ERROR reading from socket");
    optiD2_msg.linear.x = ob1.xr;
    optiD2_msg.linear.y = ob1.yr;
    optiD2_msg.linear.z = ob1.zr;
    optiD2_msg.angular.x = ob1.phi;
    optiD2_msg.angular.y = ob1.theta;
    optiD2_msg.angular.z = ob1.psi;
    pub_optiD2.publish(optiD2_msg);
	
    printf("x del lider: %f\n", ob1.xr);
    printf("y del lider: %f\n", ob1.yr);
    printf("z del lider: %f\n", ob1.zr);
    printf("pitch del lider: %f\n", ob1.phi);
    printf("roll  del lider: %f\n", ob1.theta);
    printf("yaw   del lider: %f\n", ob1.psi);

    gettimeofday(&end, NULL);

    seconds  = end.tv_sec  - start.tv_sec;
    useconds = end.tv_usec - start.tv_usec;

    mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;

    printf("Elapsed time: %ld milliseconds\n", mtime);
    contador=contador+1;

    ros::spinOnce();
    loop_rate.sleep();
}
   close(sockfd);
   printf("Contador: %ld\n",contador);
    return 0;
}
