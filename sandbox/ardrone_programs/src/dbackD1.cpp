/*
Jesús Santiaguillo Salinas
Ing. Eléctrica, Mecatrónica - CINVESTAV

Programa para realizar seguimiento de trayectoria usando Backstepping
*/
#include <ros/ros.h>
#include <std_msgs/Empty.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Imu.h>
#include <ardrone_autonomy/Navdata.h>
#include <stdio.h>

//Ángulos, velocidades y aceleraciones del Drone1 (sensores)
double phiD1 = 0.0;
double thetaD1 = 0.0;
double psiD1 = 0.0;
double vxD1 = 0.0;
double vyD1 = 0.0;
double vzD1 = 0.0;
double phiD1p = 0.0;
double thetaD1p = 0.0;
double psiD1p = 0.0;
double axD1 = 0.0;
double ayD1 = 0.0;
double azD1 = 0.0;
double altdD1 = 0.0;
double velvientoD1 = 0.0;
double angvientoD1 = 0.0;
double cangvientoD1 = 0.0;

//Posición y ángulos del Drone1 (optitrack)
double xD1 = 0.0;
double yD1 = 0.0;
double zD1 = 0.0;
double rollD1 = 0.0;
double pitchD1 = 0.0;
double yawD1 = 0.0;

//Función que obtiene datos del ardrone			
void nav_callback(const ardrone_autonomy::Navdata& msg_in){
	phiD1 = msg_in.rotX;
	thetaD1 = msg_in.rotY;
	psiD1 = msg_in.rotZ;
	vxD1 = msg_in.vx;
	vyD1 = msg_in.vy;	
	vzD1 = msg_in.vz;
	altdD1 = msg_in.altd;	
	velvientoD1 = msg_in.wind_speed;
	angvientoD1 = msg_in.wind_angle;
	cangvientoD1 = msg_in.wind_comp_angle;
}

//Función que obtiene datos del ardrone IMU
void senimu_callback(const sensor_msgs::Imu& msg){
	axD1 = msg.linear_acceleration.x;
	ayD1 = msg.linear_acceleration.y;
	azD1 = msg.linear_acceleration.z;
	phiD1p = msg.angular_velocity.x;
	thetaD1p = msg.angular_velocity.y;
	psiD1p = msg.angular_velocity.z;
}

//Función que obtiene datos del optitrack
void opti_callback(const geometry_msgs::Twist& msg){
	xD1 = msg.linear.x;
	yD1 = msg.linear.y;
	zD1 = msg.linear.z;
	rollD1 = msg.angular.x;
	pitchD1 = msg.angular.y;
	yawD1 = msg.angular.z;
}

int main(int argc, char** argv){
	ROS_INFO("ARDrone. Control Backstepping");
	ros::init(argc, argv,"ARDrone_Back"); //inicia el nodo
	
	//Editores y suscriptores ROS
	ros::Publisher pub_empty_takeoff;
	ros::Publisher pub_empty_land;
	ros::Publisher pub_twist;
	//ros::Publisher pub_velaceD1;
	ros::Subscriber nav_sub;
	ros::Subscriber opti_sub;
	ros::Subscriber senimu_sub;
	//Variables ROS
	ros::NodeHandle node; //nodo
	geometry_msgs::Twist twist_msg; //mensaje
	//geometry_msgs::Twist velaceD1_msg; //mensaje
	std_msgs::Empty emp_msg; //mensaje
	//Definiciones
	double pi = 3.141592;
	double g = 9.81;
	double sat = 1.0;
	double yawmax = 1.75;
	double anglemax = 0.087;
	double zmax = 700;
	
	//Variables para derivadas
	double newxD1 = 0.0;
	double newyD1 = 0.0;
	double newzD1 = 0.0;
	double newphiD1 = 0.0;
	double newthetaD1 = 0.0;
	//double newpsiD1 = 0.0;
	double newyawD1 = 0.0;
	double newt = 0.0;
	
	double oldxD1 = 0.0;
	double oldyD1 = 0.0;
	double oldzD1 = 0.0;
	double oldphiD1 = 0.0;
	double oldthetaD1 = 0.0;
	//double oldpsiD1 = 0.0;
	double oldyawD1 = 0.0;
	double oldt = 0.0;
	
	double xD1p = 0.0;
	double yD1p = 0.0;
	double zD1p = 0.0;
	double rotXD1p = 0.0;
	double rotYD1p = 0.0;
	//double rotZD1p = 0.0;
	double yawD1p = 0.0;
	double deltat = 0.0;
	
	double vxD1r = 0.0;
	double vyD1r = 0.0;
	double vzD1r = 0.0;
	//Observador
	double xobs = 0.0;
	double xpobs = 0.0;
	double xppobs = 0.0;
	
	double yobs = 0.0;
	double ypobs = 0.0;
	double yppobs = 0.0;
	
	double zobs = 0.0;
	double zpobs = 0.0;
	double zppobs = 0.0;
	
	double thetaobs = 0.0;
	double thetapobs = 0.0;
	double thetappobs = 0.0;
	
	double phiobs = 0.0;
	double phipobs = 0.0;
	double phippobs = 0.0;
	
	double psiobs = 0.0;
	double psipobs = 0.0;
	double psippobs = 0.0;
	//Ganancias observador
	double lx11 = 2.0;//2.0;//12.6457;
	/*double lx12 = -1.9632;
	double lx13 = -3.8934;
	double lx14 = 0.1591;*/
	
	double ly11 = 2.0;//2.0;//2.4509;
	/*double ly12 = 10.2912;
	double ly13 = 0.703;
	double ly14 = -4.6335;*/
	
	double lx21 = 2.0;//2.0;//72.2324;
	/*double lx22 = 2.7490;
	double lx23 = 12.3109;
	double lx24 = -0.2927;*/
	
	double ly21 = 2.0;//2.0;//2.547;
	/*double ly22 = 47.4874;
	double ly23 = 7.7686;
	double ly24 = -16.7766;*/
	
	double lz1 = 4.837;
	double lz2 = 16.7006;
	
	double lthe11 = 15.698;//2.6974;
	/*double lthe12 = 0.672;
	double lthe13 = 6.5824;
	double lthe14 = 2.5174;*/
	
	double lphi11 = 11.698;//13.458;//-0.0892;
	/*double lphi12 = 1.418;
	double lphi13 = -1.262;
	double lphi14 = 7.6367;*/
	
	double lthe21 = 104.1772;//-10.2215;
	/*double lthe22 = 2.0649;
	double lthe23 = -3.9382;
	double lthe24 = -7.1897;*/
	
	double lphi21 = 49.3852;//86.4578;//0.3623;
	/*double lphi22 = -14.0635;
	double lphi23 = 12.2513;
	double lphi24 = 20.2132;*/
	
	double lpsi1 = 11.771;//7.771;//3.771;
	double lpsi2 = 78.2204;//39.1364;//16.0524;
	//Ganancias de control
	double k1p = 0.057;
	double k1d = 26;
	double k11 = 1.15;
	double k12 = 0.648;
	double k2p = 0.0514;
	double k2d = 31.0;
	double k21 = 1.05;
	double k22 = 0.646;
	double kz1 = 6.5;
	double kz2 = 5.0;
	double kya1 = 8.5;
	double kya2 = 5.5;
	//Constantes modelo
	double a1 = 3.613;
	double a3 = 3.384;
	double b1 = 6.542;
	double b2 = 25.5;
	double b3 = -67.3;
	double c1 = 4.302;
	double c2 = 28.29;
	double c3 = 60.4;
	double d1 = 4.229;
	double d3 = 3.828;
	//Valores de P
	double at = (k1p*k1p + k1d*k1d + 1)/(k1p*k1d);
	double bt = 1/k1p;
	double ct = (k1p + 1)/(k1p*k1d);
	double ap = (k2p*k2p + k2d*k2d + 1)/(k2p*k2d);
	double bp = 1/k2p;
	double cp = (k2p + 1)/(k2p*k2d);
	//Valores deseados y trayectoria
	double xd = 0.0;
	double xdp = 0.0;
	double xdpp = 0.0;
	double xdppp = 0.0;
	double xdpppp = 0.0;
	double yd = 0.0;
	double ydp = 0.0;
	double ydpp = 0.0;
	double ydppp = 0.0;
	double ydpppp = 0.0;
	double zd = 0.0;
	double zdp = 0.0;
	double zdpp = 0.0;
	double thetad = 0.0;
	double thetadp = 0.0;
	double thetadpp = 0.0;
	double phid = 0.0;
	double phidp = 0.0;
	double phidpp = 0.0;
	double psid = 0.0;
	double psidp = 0.0;
	double psidpp = 0.0;
	//Operadores para la trayectoria
	double opx = 2*pi/60;
	double opy = 4*pi/60;
	double op = 2*pi/60;
	//float opz = 2*pi/30;
	double lx = 1.0;
	double ly = 0.5;
	//Errores
	double ex = 0.0;
	double ey = 0.0;
	double ez = 0.0;
	double ethe = 0.0;
	double ephi = 0.0;
	double epsi = 0.0;
	double exp = 0.0;
	double eyp = 0.0;
	double ezp = 0.0;
	double ethep = 0.0;
	double ephip = 0.0;
	double epsip = 0.0;
	double y21 = 0.0;
	double y22 = 0.0;
	double y31 = 0.0;
	double y32 = 0.0;
	//Variables de control
	double rxD1 = 0.0;
	double ryD1 = 0.0;
	double alpha1the = 0.0;
	double alpha1phi = 0.0;
	double alpha1thep = 0.0;
	double alpha1phip = 0.0;
	double alpha2the = 0.0;
	double alpha2phi = 0.0;
	double alpha2thep = 0.0;
	double alpha2phip = 0.0;
	double w1 = 0.0;
	double w2 = 0.0;
	double vthe = 0.0;
	double vphi = 0.0;
	double uthetaD1 = 0.0;
	double uthetaesc = 0.0;
	double uphiD1 = 0.0;
	double uphiesc = 0.0;
	double vpsi = 0.0;
	double upsiD1 = 0.0;
	double upsiesc = 0.0;
	double vz = 0.0;
	double uzD1 = 0.0;
	double uzesc = 0.0;
	//Variables tiempo
	double takeoff_time = 5.0;
	double hover_time = 4.0;
	double fly_time = 75.0;
	double land_time = 5.0;
	
	double start_time = 0.0;
	double t = 0.0;
	double te = 0.0;
	
	//Variable Archivo
	FILE *destino;
	//FILE *destino2;
	
	double zpp = 0;

	nav_sub = node.subscribe("/Drone1/ardrone/navdata", 1, nav_callback); //asocia el topic para leer los datos del AR.Drone
	senimu_sub = node.subscribe("/Drone1/ardrone/imu", 1, senimu_callback); //asocia el topic para leer datos de la Imu
	opti_sub = node.subscribe("/optiD1", 1, opti_callback); //asocia el topic para leer datos del OptiTrack
	pub_twist = node.advertise<geometry_msgs::Twist>("/Drone1/cmd_vel", 1); //asocia el topic para enviar el control al AR.Drone
	pub_empty_takeoff = node.advertise<std_msgs::Empty>("/Drone1/ardrone/takeoff", 1); //asocia el topic para despegar el AR.Drone
	pub_empty_land = node.advertise<std_msgs::Empty>("/Drone1/ardrone/land", 1); //asocia el topic para aterrizar el AR.Drone
	//pub_velaceD1 = node.advertise<geometry_msgs::Twist>("/velaceD1", 1); //asocia el topic para enviar velocidades y aceleraciones del AR.Drone
	
	destino = fopen("datdback.txt","w"); //abrir archivo
	//destino2 = fopen("valLider.txt","w"); //abrir archivo 2
	
	ROS_INFO("Iniciando programa backstepping...");
	
	start_time =(double)ros::Time::now().toSec();
	ros::Rate loop_rate(100); //establece la frecuencia del nodo
	while(ros::ok()){
		t = (double)ros::Time::now().toSec() - start_time;
		
		newt = t;
		newxD1 = xD1;
		newyD1 = yD1;
		newzD1 = zD1;
		newphiD1 = phiD1*pi/180;
		newthetaD1 = thetaD1*pi/180;
		//newpsiD1 = psiD1;
		newyawD1 = yawD1;
		
		//despegar
		if(t <= takeoff_time){
			pub_empty_takeoff.publish(emp_msg); //publica el mensaje para despegar el drone
			printf("Despegando\n");
		}
		//hover 1
		if((t > takeoff_time) && (t <= (takeoff_time + hover_time))){
			twist_msg.linear.x = 0.0; 
			twist_msg.linear.y = 0.0;
			twist_msg.linear.z = 0.0;
			twist_msg.angular.x = 0.0; 
			twist_msg.angular.y = 0.0;
			twist_msg.angular.z = 0.0;
			 
			pub_twist.publish(twist_msg); //publica el mensaje para poner en hover al drone
			printf("En hover\n");
			
			xobs = newxD1;
			yobs = newyD1;
			zobs = newzD1;
			thetaobs = newthetaD1;
			phiobs = newphiD1;
			psiobs = newyawD1;
		}
		//vuelo
		if((t > (takeoff_time + hover_time)) && (t <= (takeoff_time + hover_time + fly_time))){
			te = t - (takeoff_time + hover_time);
			//trayectoria deseada en X
			xd = 0.5 + lx*cos(opx*te);
			xdp = -lx*opx*sin(opx*te);
			xdpp = -lx*opx*opx*cos(opx*te);
			xdppp = lx*opx*opx*opx*sin(opx*t);
			xdpppp = lx*opx*opx*opx*opx*cos(opx*t);
			
			//trayectoria deseada en Y
			yd = -0.5 + ly*sin(opy*te);
			ydp = ly*opy*cos(opy*te);
			ydpp = -ly*opy*opy*sin(opy*te);
			ydppp = -ly*opy*opy*opy*cos(opy*t);
			ydpppp = ly*opy*opy*opy*opy*sin(opy*t);
			
			//trayectoria deseada en Z
			zd = 1.0;//1.3 + 0.3*sin(op*te + 270*pi/180);//1.0 + 0.25*cos((opz*te) + (pi));
			zdp = 0.0;//0.3*op*cos(op*te + 270*pi/180);//-0.25*opz*sin((opz*te) + (pi));
			zdpp = 0.0;//-0.3*op*op*sin(op*te + 270*pi/180);
			
			//ángulo deseado de yaw
			psid = 0.0;//sin(op*te);//atan2(ydp,xdp);//pi/4;//sin(op*te);
			/*if(psid < -2){
				psid = psid + 2*pi;
			}
			psid = psid - pi/2;*/
			psidp = 0.0;//op*cos(op*te);//((ydpp*xdp) - (ydp*xdpp))/((ydp*ydp) + (xdp*xdp));//opx*cos(op*te);
			psidpp = 0.0;//-op*op*sin(op*te);//((((ydp*ydp) + (xdp*xdp))*(((ydpp*xdpp) + (xdp*ydppp)) - ((ydp*xdppp) + (xdpp*ydpp)))) - (((ydpp*xdp) - (ydp*xdpp))*((2*ydp*ydpp) + (2*xdp*xdpp))))/(((ydp*ydp) + (xdp*xdp))*((ydp*ydp) + (xdp*xdp)));//-op*op*sin(op*te);
		
			//valor deseado en theta y phi
			thetad = (1/g)*(cos(psid)*xdpp + sin(psid)*ydpp);
			phid = (1/g)*(sin(psid)*xdpp - cos(psid)*ydpp);
			thetadp = (1/g)*(cos(psid)*xdppp + sin(psid)*ydppp);
			phidp = (1/g)*(sin(psid)*xdppp - cos(psid)*ydppp);
			thetadpp = (1/g)*(cos(psid)*xdpppp + sin(psid)*ydpppp);
			phidpp = (1/g)*(sin(psid)*xdpppp - cos(psid)*ydpppp);
			
			deltat = 0.01;//newt - oldt;
			
			//velocidad del drone (derivada 1er orden)
			xD1p = (newxD1 - oldxD1)/deltat;
			yD1p = (newyD1 - oldyD1)/deltat;
			zD1p = (newzD1 - oldzD1)/deltat;
			rotXD1p = (newphiD1 - oldphiD1)/deltat;
			rotYD1p = (newthetaD1 - oldthetaD1)/deltat;
			//rotZD1p = (newpsiD1 - oldpsiD1)/deltat;
			yawD1p = (newyawD1 - oldyawD1)/deltat;
			
			//velocidad del drone (sensores)
			vxD1r = (cos(newyawD1)*(vxD1/1000)) - (sin(newyawD1)*(vyD1/1000));
			vyD1r = (sin(newyawD1)*(vxD1/1000)) + (cos(newyawD1)*(vyD1/1000));
			vzD1r = (vzD1/1000);
			
			//phiD1 = phiD1*pi/180;
			//thetaD1 = thetaD1*pi/180;
			//errores
			ex = xD1 - xd;
			ey = yD1 - yd;
			ez = zD1 - zd;
			ephi = (phiD1*pi/180) - phid;
			ethe = (thetaD1*pi/180) - thetad;
			epsi = yawD1 - psid;
			
			exp = xpobs - xdp;//vxD1r - xdp;//xD1p - xdp;
			eyp = ypobs - ydp;//vyD1r - ydp;//yD1p - ydp;
			ezp = zpobs - zdp;//zD1p - zdp;
			ephip = phiobs - phidp;//phiD1p - phidp;
			ethep = thetaobs - thetadp;//thetaD1p - thetadp;
			epsip = psipobs - psidp;//psiD1p - psidp;
			
			//estrategia de control
			//control de altura
			vz = -kz1*ez - kz2*ezp + zdpp;
			uzD1 = ((1/a3)*((a1*zpobs) + vz));
			
			zpp = -a1*zpobs + a3*uzD1;
			
			//control psi
			vpsi = -kya1*epsi - kya2*epsip + psidpp;
			upsiD1 = (1/d3)*((d1*psipobs) + vpsi);//psiD1p
			
			//control plano
			rxD1 = -k1p*ex - k1d*exp;
			ryD1 = -k2p*ey - k2d*eyp;
			
			alpha1the = (1/g)*(cos(yawD1)*rxD1 + sin(yawD1)*ryD1);
			alpha1phi = (1/g)*(sin(yawD1)*rxD1 - cos(yawD1)*ryD1);
			
			y21 = ethe - alpha1the;
			y22 = ephi - alpha1phi;
			
			alpha1thep = -k1p*(1/g)*(cos(yawD1)*exp + sin(yawD1)*eyp) - k1d*ethe;
			alpha1phip = -k2p*(1/g)*(sin(yawD1)*exp - cos(yawD1)*eyp) - k2d*ephi;
			
			alpha2the = alpha1thep - bt*g*(cos(yawD1)*ex + sin(yawD1)*ey) - ct*g*(cos(yawD1)*exp + sin(yawD1)*eyp) - k11*y21;
			alpha2phi = alpha1phip - bp*g*(sin(yawD1)*ex - cos(yawD1)*ey) - cp*g*(sin(yawD1)*exp - cos(yawD1)*eyp) - k21*y22;
			
			y31 = ethep - alpha2the;
			y32 = ephip - alpha2phi;
			
			alpha2thep = -(bt*g*g + k11*k1p)*(1/g)*(cos(yawD1)*exp + sin(yawD1)*eyp) - (k1p + k11*k1d + ct*g*g)*ethe - (k1d + k11)*ethep;
			alpha2phip = -(bp*g*g + k21*k2p)*(1/g)*(sin(yawD1)*exp - cos(yawD1)*eyp) - (k2p + k21*k2d + cp*g*g)*ephi - (k2d + k21)*ephip;
			
			w1 = alpha2thep - y21 - k12*y31;
			w2 = alpha2phip - y22 - k22*y32;
			
			// ----- Control por Backstepping -----
			vthe = w1 + thetadpp;
			vphi = w2 + phidpp;
			
			uphiD1 = (1/b3)*((b1*ephip) + (b2*ephi) + vphi + b1*phidp + b2*phid);//(1/b3)*((b1*phiD1p) + (b2*phiD1) + vphi);
			uthetaD1 = (1/c3)*((c1*ethep) + (c2*ethe) + vthe + c1*thetadp + c2*thetad);
			// -----
			
			/*// ----- Control directo sin dinámica -----
			double k1 = 9;
			double k2 = 15;
			double k3 = 0.9;
			double k4 = 0.4;
			
			vthe = -k1*(1/g)*(cos(yawD1)*ex + sin(yawD1)*ey) - k2*(1/g)*(cos(yawD1)*exp + sin(yawD1)*eyp) - k3*ethe - k4*ethep + thetadpp;//w1 + thetadpp;
			vphi = -k1*(1/g)*(sin(yawD1)*ex - cos(yawD1)*ey) - k2*(1/g)*(sin(yawD1)*exp - cos(yawD1)*eyp) - k3*ephi - k4*ephip + phidpp;//w2 + phidpp;
			
			uphiD1 = -vphi;
			uthetaD1 = vthe;
			// -----*/
			
			/*// ----- Control directo con dinámica -----
			double k11 = 543.6;
			double k12 = 906;
			double k13 = 82.65;
			double k14 = 28.462;
			
			double k21 = 605.7;
			double k22 = 1009.5;
			double k23 = 86.1;
			double k24 = 32.7;
			
			vthe = -k11*(1/g)*(cos(yawD1)*ex + sin(yawD1)*ey) - k12*(1/g)*(cos(yawD1)*exp + sin(yawD1)*eyp) - k13*ethe - k14*ethep + thetadpp;//w1 + thetadpp;
			vphi = -k21*(1/g)*(sin(yawD1)*ex - cos(yawD1)*ey) - k22*(1/g)*(sin(yawD1)*exp - cos(yawD1)*eyp) - k23*ephi - k24*ephip + phidpp;//w2 + phidpp;
			
			uphiD1 = (1/b3)*((b1*ephip) + (b2*ephi) + vphi + b1*phidp + b2*phid);//(1/b3)*((b1*phiD1p) + (b2*phiD1) + vphi);
			uthetaD1 = (1/c3)*((c1*ethep) + (c2*ethe) + vthe + c1*thetadp + c2*thetad);
			// -----*/
			
			upsiesc = upsiD1;//(upsiD1*sat)/yawmax; //escalamiento del control de yaw
			uzesc = uzD1;//(uzD1*sat)/zmax; //escalamiento del control de Z
			uthetaesc = uthetaD1;//(uthetaD1*sat)/anglemax; //escalamiento del control de X
			uphiesc = uphiD1;//(uphiD1*sat)/anglemax; //escalamiento del control Y
			
			//saturación de los controles
			if(upsiesc > sat){ upsiesc = sat;}
			if(upsiesc < -sat){ upsiesc = -sat;}
			if(uzesc > sat){ uzesc = sat;}
			if(uzesc < -sat){ uzesc = -sat;}
			if(uthetaesc > sat){ uthetaesc = sat;}
			if(uthetaesc < -sat){ uthetaesc = -sat;}
			if(uphiesc > sat){ uphiesc = sat;}
			if(uphiesc < -sat){ uphiesc = -sat;}
			
			//observador
			xpobs = xpobs + lx11*(xD1 - xobs);//+ lx11*(xD1 - xobs) + lx12*(yD1 - yobs) + lx13*(thetaD1 - thetaobs) + lx14*(phiD1 - phiobs);
			xppobs = g*(thetaobs*cos(yawD1) + phiobs*sin(yawD1)) + lx21*(xD1 - xobs);//+ lx21*(xD1 - xobs) + lx22*(yD1 - yobs) + lx23*(thetaD1 - thetaobs) + lx24*(phiD1 - phiobs);
			
			ypobs = ypobs + ly11*(yD1 - yobs);//+ ly11*(xD1 - xobs) + ly12*(yD1 - yobs) + ly13*(thetaD1 - thetaobs) + ly14*(phiD1 - phiobs);
			yppobs = g*(thetaobs*sin(yawD1) - phiobs*cos(yawD1)) + ly21*(yD1 - yobs);//+ ly21*(xD1 - xobs) + ly22*(yD1 - yobs) + ly23*(thetaD1 - thetaobs) + ly24*(phiD1 - phiobs);
			
			zpobs = zpobs + lz1*(zD1 - zobs);
			zppobs = -a1*zpobs + a3*uzesc + lz2*(zD1 - zobs);
			
			thetapobs = thetapobs + lthe11*((thetaD1*pi/180) - thetaobs);//+ lthe11*(xD1 - xobs) + lthe12*(yD1 - yobs) + lthe13*(thetaD1 - thetaobs) + lthe14*(phiD1 - phiobs);
			thetappobs = -c2*thetaobs - c1*thetapobs + c3*uthetaesc + lthe21*((thetaD1*pi/180) - thetaobs);//+ lthe21*(xD1 - xobs) + lthe22*(yD1 - yobs) + lthe23*(thetaD1 - thetaobs) + lthe24*(phiD1 - phiobs);
			
			phipobs = phipobs + lphi11*((phiD1*pi/180) - phiobs);//+ lphi11*(xD1 - xobs) + lphi12*(yD1 - yobs) + lphi13*(thetaD1 - thetaobs) + lphi14*(phiD1 - phiobs);
			phippobs = -b2*phiobs - b1*phipobs + b3*uphiesc + lphi21*((phiD1*pi/180) - phiobs);//+ lphi21*(xD1 - xobs) + lphi22*(yD1 - yobs) + lphi23*(thetaD1 - thetaobs) + lphi24*(phiD1 - phiobs);
			
			psipobs = psipobs + lpsi1*(yawD1 - psiobs);
			psippobs = -d1*psipobs + d3*upsiesc + lpsi2*(yawD1 - psiobs);
			
			//velocidad del drone (observador)
			xobs = xobs + xpobs*deltat;
			xpobs = xpobs + xppobs*deltat;
			
			yobs = yobs + ypobs*deltat;
			ypobs = ypobs + yppobs*deltat;
			
			zobs = zobs + zpobs*deltat;
			zpobs = zpobs + zppobs*deltat;
			
			thetaobs = thetaobs + thetapobs*deltat;
			thetapobs = thetapobs + thetappobs*deltat;
			
			phiobs = phiobs + phipobs*deltat;
			phipobs = phipobs + phippobs*deltat;
			
			psiobs = psiobs + psipobs*deltat;
			psipobs = psipobs + psippobs*deltat;
			
			twist_msg.linear.x = uthetaesc; 
			twist_msg.linear.y = uphiesc;
			twist_msg.linear.z = uzesc;
			twist_msg.angular.x = 0.0001; 
			twist_msg.angular.y = 0.0001;
			twist_msg.angular.z = upsiesc;
			
			/*//Para prealimentación de las velocidades y aceleraciones del líder
			velaceD1_msg.linear.x = xD1p;
			velaceD1_msg.linear.y = yD1p;
			velaceD1_msg.linear.z = zD1p;
			velaceD1_msg.angular.x = xD1pp;
			velaceD1_msg.angular.y = yD1pp;
			velaceD1_msg.angular.z = yawD1p;*/
			
			//Para prealimentación de las velocidades del líder y aceleraciones de la trayectoria
			/*velaceD1_msg.linear.x = xD1p;
			velaceD1_msg.linear.y = yD1p;
			velaceD1_msg.linear.z = zD1p;
			velaceD1_msg.angular.x = xdpp;
			velaceD1_msg.angular.y = ydpp;
			velaceD1_msg.angular.z = yawdp;*/
			
			pub_twist.publish(twist_msg); //publica el mensaje para el control del drone
			//pub_velaceD1.publish(velaceD1_msg); //publica el mensaje de las velocidades y aceleraciones
			printf("Volando\n");
			
			// Guardar datos
			fprintf(destino,"%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n", newxD1, xd, newyD1, yd, newzD1, zd, phiD1*pi/180, phid, thetaD1*pi/180, thetad, newyawD1, psid, upsiD1, upsiesc, uzD1, uzesc, uthetaD1, uthetaesc, uphiD1, uphiesc, t, vxD1r, vyD1r, zD1p, phiD1p, thetaD1p, psiD1p, altdD1, zobs, zpobs, psiobs, psipobs, xobs, xpobs, yobs, ypobs, thetaobs, thetapobs, phiobs, phipobs);
			//fprintf(destino2,"%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n", newxD1, newyD1, newzD1, newyawD1, xD1p, yD1p, zD1p, yawD1p, xD1pp, yD1pp, yawD1pp, t, velvientoD1, angvientoD1, cangvientoD1);
		}
		//hover 2
		if((t > (takeoff_time + hover_time + fly_time)) && (t <= (takeoff_time + (hover_time*2) + fly_time))){
			twist_msg.linear.x = 0.0; 
			twist_msg.linear.y = 0.0;
			twist_msg.linear.z = 0.0;
			twist_msg.angular.x = 0.0; 
			twist_msg.angular.y = 0.0;
			twist_msg.angular.z = 0.0;
			
			pub_twist.publish(twist_msg); //publica el mensaje para poner en hover al drone
			printf("En hover\n");
		}
		//aterrizar
		if((t > (takeoff_time + (hover_time*2) + fly_time)) && (t <= (takeoff_time + (hover_time*2) + fly_time + land_time))){
			pub_empty_land.publish(emp_msg); //publica el mensaje para aterrizar el drone
			printf("Aterrizando\n");
		}
		//salir del ciclo
		if(t > (takeoff_time + (hover_time*2) + fly_time + land_time)){
			break;
		}
		
		oldxD1 = newxD1;
		oldyD1 = newyD1;
		oldzD1 = newzD1;
		oldphiD1 = newphiD1;
		oldthetaD1 = newthetaD1;
		//oldpsiD1 = newpsiD1;
		oldyawD1 = newyawD1;
		oldt = newt;
		
		//printf("Datos de los sensores:\n");
		//printf("rotX: %f \t rotY: %f \t rotZ: %f \t vx: %f \t vy: %f \t vz: %f \t altd: %f \n",rotX,rotY,rotZ,vx,vy,vz,altd);
		printf("Datos del optitrack\n");
		printf("x: %lf \t y: %lf \t z: %lf \n roll: %lf \t pitch: %lf \t yaw: %lf \n", xD1, yD1, zD1, rollD1, pitchD1, yawD1);
		printf("upsiesc: %lf \t uzesc: %lf \t uthetaesc: %lf \t uphiesc: %lf\n", upsiesc, uzesc, uthetaesc, uphiesc);
		printf("upsi: %lf \t uz: %lf \t utheta: %lf \t uphi: %lf\n", upsiD1, uzD1, uthetaD1, uphiD1);
		
		ros::spinOnce(); //refresca los datos
		loop_rate.sleep(); //espera a que se cumpla la frecuencia
	}
	
	fclose(destino); //cerrar archivo
	//fclose(destino2); //cerrar archivo
	
	ROS_INFO("Programa backstepping finalizado.");
	
	return 0;
}
