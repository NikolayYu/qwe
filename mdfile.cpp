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
int er(std::string file_name, std::string file_error){
		std::fstream file;
		file.exceptions(std::ifstream::badbit | std::ifstream::failbit);
		try{
		file.open(file_name);
		return 1;
		}catch(const std::exception & ex){
		std::string error = "error open file";
		errors(error, file_error);
		return 12;
		}
		}