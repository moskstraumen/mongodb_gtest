#include "dbClient.h"
std::string dbClient::createDatabase(const std::string uri)
{
	std::string ret = this->_m->init(uri);
	return ret;
}
