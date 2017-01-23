#include <string>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "mongodbToy.h"
#include "dbClient.h"

using ::testing::Return;

class MongoDbMock : public mongodbToy
{
public:
	MongoDbMock() {};
	MongoDbMock(int a) : mongodbToy(a) {};

    MOCK_METHOD1(init, std::string(const std::string addr));
};

class MongoDbTesting : public testing::Test
{
public:
	MongoDbMock *mock;
	dbClient *client;

	void SetUp()
	{
		mock = new MongoDbMock(1);
		client = new dbClient(mock);

	}
	void TearDown()
	{
		delete client;
		delete mock;
	}
};

TEST_F(MongoDbTesting, UnitTest01)
{
    std::string addr = "mongodb://localhost:27017/myproject";

    EXPECT_CALL(*mock, init(::testing::_))
        .WillOnce(Return(std::string(addr)));
    //mock->init(addr); // either this or the next statements will call init() and will pass the test
    std::string uri = client->createDatabase(addr);
    EXPECT_STREQ(addr.c_str(), uri.c_str());
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
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
