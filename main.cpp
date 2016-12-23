/*
 * main.cpp
 *
 *  Created on: Dec 23, 2016
 *      Author: wangj37
 */
#include <gmock/gmock.h>
#include <gtest/gtest.h>


int main(int argc, char *argv[])
{
        ::testing::InitGoogleMock(&argc, argv);
        return RUN_ALL_TESTS();
}


