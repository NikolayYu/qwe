#include "mdfile.h"

std::string MD(std::string sah){
Weak::MD5 hash;
	std::string digest;
	StringSource(sah, true,  new HashFilter(hash, new HexEncoder(new StringSink(digest))));  // строка-приемник
  	return digest;
 }
void errors(std::string error, std::string name){
	std::ofstream file;
	file.open(name, std::ios::app);
	if(file.is_open()){
		time_t seconds = time(NULL);
		tm* timeinfo = localtime(&seconds);
		file<<error<<':'<<asctime(timeinfo)<<std::endl;
	std::cin.get();
	}
}