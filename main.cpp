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
#include <cryptopp/hex.h> // HexEncoder
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include <cryptopp/md5.h> // MD%, для другого алгоритма - другой заголовочный файл
using namespace CryptoPP;
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

//CryptoPP::AutoSeededRandomPool obj

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
		char ok[] = "OK\0";
        uint32_t kolvo;
        uint32_t numb;
        uint32_t vect;
		//Авторизация
        recv(work_sock, &msg, sizeof(msg), 0);
		std::string login, hashq;
		std::ifstream file("base.txt");
		getline (file, login, ':');
		getline (file, hashq);
		std::string message = msg;
		char salt[50] = "2D2D2D2D2D2D2D22";
		char err[] = "ERR";
		if(message != login){
			std::cout << "err log" << std::endl;
			send(work_sock, err, sizeof(err), 0);
			close(s);
		}else{
		//соль отправленная клиенту 
		send(work_sock, salt, sizeof(salt), 0);
		}
		recv(work_sock, msg, sizeof(msg), 0);
		// Создаем объект-"хэширователь" для MD5
		Weak::MD5 hash;
		// Что будем хэшировать

		// куда запишем результат
		std::string digest;
		std::string sah = salt + hashq;
		// создаем цепочку преобразования
		StringSource(sah, true,  new HashFilter(hash, new HexEncoder(new StringSink(digest))));  // строка-приемник
		if(digest != msg){
			std::cout << "err hash" << std::endl;
			close(s);
		}else{
		std::cout << "Autorized client!" << std::endl;
		send(work_sock, ok, sizeof(ok), 0);
		}
		
		
		recv(work_sock, &kolvo, sizeof(kolvo), 0);
        std::cout << "Кол-во векторов: " << kolvo  << std::endl;

		//цикл векторов
        for(int j=0; j<kolvo; j++){
			recv(work_sock, &numb, sizeof(numb), 0);//прием длинны для первого вектора
			std::cout << "NUMB: " << numb << std::endl;
		
			send(work_sock, msg, sizeof(msg), 0);
			std::cout << "Вектор " << j+1 << ':'<< std::endl;
			long int sum = 0;
			
		//цикл значений	
		for(int i=0; i<numb; i++){
			recv(work_sock, &vect, sizeof(vect), 0);
			
			send(work_sock, msg, sizeof(msg), 0);
			sum = sum + vect*vect;
		}
		uint32_t mfc;
		mfc = sum;
		
		std::cout << "Сумма элементов вектора " << mfc << std::endl;
		
		send(work_sock, &mfc, sizeof(mfc), 0);
		}
		
		std::cout << "Завершение работы программы" << std::endl;
        close(s);

}
return 0;
}
}