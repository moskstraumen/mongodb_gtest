#ifndef __DBCLIENT_H__
#define __DBCLIENT_H__
#include <string>
#include <vector>
#include "mongodbToy.h"

// A client program using mongoDB
class dbClient
{
public:
	dbClient(mongodbToy *m):_m(m){};
	~dbClient() {};

	// Generate a database object using mongocxx API
	// m: a mongodb class
	// uri: URI of database
	std::string createDatabase(const std::string uri)
	{
			std::string ret = _m->init(uri);

			return ret;

	}
private:
	mongodbToy *_m;
};
#endif
// __DBCLIENT_H__
