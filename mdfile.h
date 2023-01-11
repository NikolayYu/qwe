#include <netinet/in.h>
#include <iostream>
#include <arpa/inet.h>
#include <cstdlib>
#include <unistd.h>
#include <ctime>
#include <fstream>
#include <sstream>
#include <string>
#include <cryptopp/cryptlib.h>
#include <iostream>
#include <vector>
#include <getopt.h>
#include <cryptopp/hex.h> // HexEncoder
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
using namespace CryptoPP;
#include <cryptopp/md5.h> // MD%, для другого алгоритма - другой заголовочный файл
std::string MD(std::string sah);
void errors(std::string error, std::string name);