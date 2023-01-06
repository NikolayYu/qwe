#include <netinet/in.h>
#include <iostream>
#include <arpa/inet.h>
#include <cstdlib>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <string>
#include <cryptopp/cryptlib.h>
#include <iostream>
#include <vector>
#include <getopt.h>
#include <cryptopp/hex.h> // HexEncoder
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <cryptopp/md5.h> // MD%, для другого алгоритма - другой заголовочный файл
using namespace CryptoPP;
int main(int argc, char *argv[]) {
	if(argc == 1){
		std::cout << "Kalculator" << std::endl;
		std::cout << "-h info" << std::endl;
		std::cout << "-s operations" << std::endl;
	}
	int opt;
	while ((opt = getopt(argc, argv, "hs" ))!=-1 ){
	switch(opt){
		case 'h':
		std::cout << "Kalculator" << std::endl;
		std::cout << "-h info" << std::endl;
		std::cout << "-s operations" << std::endl;
		break;
		case 's':
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
			//Успешное подключение к серверу
			std::cout << "Successfull client connection!\n";
			char msg[255];
			char *buffer = new char[4096];
			uint32_t kolvo;
			uint32_t numb;
			uint32_t vect;
			std::string ok = "OK";
			std::string salt = "2D2D2D2D2D2D2D22";
			
			std::string err = "ERR";
			//Авторизация
			recv(work_sock, &msg, sizeof(msg), 0);
			
			std::string login, hashq;
			std::ifstream file("base.txt");
			getline (file, login, ':');
			getline (file, hashq);
			std::string message = msg;
			if(message != login){
			std::strcpy(buffer, err.c_str());
			send(work_sock, buffer, err.length(), 0);
				close(s);
			}else{
			//соль отправленная клиенту 
			std::strcpy(buffer, salt.c_str());
			send(work_sock, buffer, salt.length(), 0);
			recv(work_sock, msg, sizeof(msg), 0);
			// Создаем объект-"хэширователь" для MD5
			Weak::MD5 hash;
			std::string digest;
			std::string sah = salt + hashq;
			StringSource(sah, true,  new HashFilter(hash, new HexEncoder(new StringSink(digest))));  // строка-приемник
			if(digest != msg){
				std::strcpy(buffer, err.c_str());
			send(work_sock, buffer, err.length(), 0);
				close(s);
			}else{
				std::strcpy(buffer, ok.c_str());
			send(work_sock, buffer, ok.length(), 0);
			recv(work_sock, &kolvo, sizeof(kolvo), 0);
			std::cout << "Кол-во векторов: " << '"' << kolvo << '"' << std::endl;
			//цикл векторов
			for(int j=0; j<kolvo; j++){
				recv(work_sock, &numb, sizeof(numb), 0);//прием длинны для первого вектора
				std::cout << "Вектор " << j+1 << ':'<< std::endl;
				long int sum = 0;
			//цикл значений	
			for(int i=0; i<numb; i++){
				recv(work_sock, &vect, sizeof(vect), 0);
				sum = sum + vect*vect;
			}
			uint32_t mfc;
			mfc = sum;
			std::cout << "Сумма элементов вектора " << mfc << std::endl;
			send(work_sock, &mfc, sizeof(mfc), 0);
			}
			}
			}
			std::cout << "Завершение работы программы";
			close(s);
	}
	return 0;
	}
	}
	break;
}
}