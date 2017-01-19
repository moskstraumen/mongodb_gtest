#include <string>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "mongodbToy.h"
#include "dbClient.h"

using ::testing::Return;

class MongoDbMock : public mongodbToy
{
public:
    MOCK_METHOD1(init, std::string(const std::string addr));
};

class MongoDbTesting : public testing::Test
{
public:
	MongoDbMock mock;
	dbClient *client;

	void SetUp()
	{
		client = new dbClient(&mock);
	}
	void TearDown()
	{
		delete client;
	}

};

TEST_F(MongoDbTesting, UnitTest01)
{
    char *addr = "mongodb://localhost:27017/myproject";
  //  MongoDbMock mock;
  //  dbClient client(&mock);
    EXPECT_CALL(mock, init(::testing::_))
        .WillOnce(Return(std::string(addr)));
    std::string uri = client->createDatabase(std::string(addr));
    EXPECT_STREQ(addr, uri.c_str());
}

TEST_F(MongoDbTesting, UnitTest02)
{
	std::string addr = "mongodb://localhost:27017/myproject";
	mongodbToy m;
	EXPECT_NO_THROW(m.init("mongodb://localhost:27017/myproject"));
}

//TEST(MongoDbTest, OneLink)
//{
//    char *addr = "mongodb://localhost:27017/myproject";
//    MongoDbMock mock;
//    dbClient client(&mock);
//    EXPECT_CALL(mock, init(::testing::_))
//        .WillOnce(Return(std::string(addr)));
//    std::string uri = client.createDatabase(std::string(addr));
//    EXPECT_STREQ(addr, uri.c_str());
//}
//
//TEST(MongoDbTest, URILink)
//{
//	std::string addr = "mongodb://localhost:27017/myproject";
//	mongodbToy m;
//	EXPECT_NO_THROW(m.init("mongodb://localhost:27017/myproject"));
//}

int main(int argc, char *argv[])
{
	::testing::InitGoogleMock(&argc, argv);
	return RUN_ALL_TESTS();
}
