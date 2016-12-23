/*
 * mongodbToy.cpp
 *
 *  Created on: Dec 23, 2016
 *      Author: wangj37
 */
#include "mongodbToy.h"

void mongodbToy::init(std::string addr)
{
	mongocxx::instance inst{};
	this->m_URI = addr;
};

void  mongodbToy::connection()
{

	this->m_Client = mongocxx::client{mongocxx::uri{this->m_URI}};
};

void  mongodbToy::createCollection()
{

};

void  mongodbToy::printOutCollection(mongocxx::collection coll)
{

};



