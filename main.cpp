#include <netinet/in.h>
#include <iostream>
#include <arpa/inet.h>
#include <cstdlib>
#include <unistd.h>

#include <sstream>
#include <cryptopp/cryptlib.h>

int main(int argc, char *argv[]) {
struct sockaddr_in {
 short sin_family;
 unsigned short sin_port;
 struct in_addr sin_addr;
 char sin_zero[8];
};
struct in_addr {
 unsigned long s_addr;
};
int s = socket(AF_INET, SOCK_STREAM, 0);
sockaddr_in * self_addr = new (sockaddr_in);
self_addr->sin_family = AF_INET;
self_addr->sin_port = htons(33333);
self_addr->sin_addr.s_addr = inet_addr("127.0.0.1");
std::cout << "Wait for connect client...\n";
int b = bind(s,(const sockaddr*) self_addr,sizeof(sockaddr_in));
if(b == -1) {
    std::cout << "Binding error\n";
    return 1;
}
listen(s, SOMAXCONN);
while(true) {
    sockaddr_in * client_addr = new sockaddr_in;
    socklen_t len = sizeof (sockaddr_in);
    int work_sock = accept(s, (sockaddr*)(client_addr), &len);
    if(work_sock == -1) {
        std::cout << "Error #2\n";
    }
    else {
        std::cout << "Successfull client connection!\n";
        char msg[255];
        uint32_t kolvo;
        uint32_t numb;
        uint32_t vect;
		
        recv(work_sock, msg, sizeof(msg), 0);
        std::cout << "login: " << '"' << msg << '"' << std::endl;
        
		send(work_sock, msg, sizeof(msg), 0);
		 
		recv(work_sock, msg, sizeof(msg), 0);
        std::cout << "soult nad hash: " << '"' << msg << '"' << std::endl;
        
		send(work_sock, msg, sizeof(msg), 0);
		
		recv(work_sock, &kolvo, sizeof(kolvo), 0);
        std::cout << "ÐÐ¾Ð»-Ð²Ð¾ Ð²ÐµÐºÑÐ¾ÑÐ¾Ð²: " << '"' << kolvo << '"' << std::endl;
        
		send(work_sock, msg, sizeof(msg), 0);
		
		
		//ÑÐ¸ÐºÐ» Ð²ÐµÐºÑÐ¾ÑÐ¾Ð²
        for(int j=0; j<kolvo; j++){
			recv(work_sock, &numb, sizeof(numb), 0);//Ð¿ÑÐ¸ÐµÐ¼ Ð´Ð»Ð¸Ð½Ð½Ñ Ð´Ð»Ñ Ð¿ÐµÑÐ²Ð¾Ð³Ð¾ Ð²ÐµÐºÑÐ¾ÑÐ°
			send(work_sock, msg, sizeof(msg), 0);
			std::cout << "ÐÐµÐºÑÐ¾Ñ " << j+1 << ':'<< std::endl;
			long int sum = 0;
			
		//ÑÐ¸ÐºÐ» Ð·Ð½Ð°ÑÐµÐ½Ð¸Ð¹	
		for(int i=0; i<numb; i++){
			recv(work_sock, &vect, sizeof(vect), 0);
			std::cout << "ÐÐ½Ð°ÑÐµÐ½Ð¸Ðµ " << i+1 << "  : " 
			<< '"' << vect*vect << '"' << std::endl;
			send(work_sock, msg, sizeof(msg), 0);
			sum = sum + vect*vect;
		}	
		std::cout << "Ð¡ÑÐ¼Ð¼Ð° ÑÐ»ÐµÐ¼ÐµÐ½ÑÐ¾Ð² Ð²ÐµÐºÑÐ¾ÑÐ° " << sum << std::endl;
		}
		std::cout << "ÐÐ°Ð²ÐµÑÑÐµÐ½Ð¸Ðµ ÑÐ°Ð±Ð¾ÑÑ Ð¿ÑÐ¾Ð³ÑÐ°Ð¼Ð¼Ñ";
        close(s);
    }
return 0;
}
}
/*
 for(int i=0; i<strlen(msg); i++){
 if(msg[i] != ' '){
 std::cout << msg[i] << std::endl;
 num = num + msg[i];
}
else{
 std::cout << num << " - num" << std::endl;
 num = ' ';
}}
 
 
 int k;
 for (int i = 0; i < k; i++) {
     char mesg[256] = "";
     std::cin >> mesg;
     send(s, mesg, sizeof(mesg), 0);
     std::cout << "Message from client: " << '"' << mesg << '"' << std::endl;
 }
 
 
 */
