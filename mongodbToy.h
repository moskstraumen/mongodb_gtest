/*
 * mongodbToy.h
 *
 *  Created on: Dec 23, 2016
 *      Author: wangj37
 */

#ifndef MONGODBTOY_H_
#define MONGODBTOY_H_

#include <iostream>
#include <string>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
//
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

class mongodbToy
{
public:
	mongodbToy(int a) {std::cout << "this is : " << a << std::endl;};
	mongodbToy() {};
	virtual ~mongodbToy() {};

	virtual std::string init(const std::string addr);

	void connection() ;

	void createCollection() ;

	void printOutCollection(mongocxx::collection coll);

private:
	std::string m_URI;

	mongocxx::client m_Client;

	mongocxx::collection m_Collection;
};

#endif /* MONGODBTOY_H_ */
