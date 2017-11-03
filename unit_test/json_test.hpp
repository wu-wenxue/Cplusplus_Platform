#ifndef JSON_TEST_HPP
#define JSON_TEST_HPP
#include <fstream>
#include <json/json.h>
#include <cassert>
#include <iostream>

#include "logger/wxlogger.h"

using namespace std;

void json_test()
{
    ifstream ifs;
    ifs.open("data/testjson.json");
    assert(ifs.is_open());

    Json::Reader reader;
    Json::Value root;
    if(!reader.parse(ifs,root,false))
    {
        return ;
    }

    std::string name = root["name"].asString();
    int age = root["age"].asInt();

    Wxlogger* logger = Wxlogger::getInstance();
    WXLOG_INFO(logger, "name : " << name);
    WXLOG_INFO(logger, "age : " << age);

}

void json_array_test()
{
    ifstream ifs;
    ifs.open("data/testjsonarray.json");
    assert(ifs.is_open());

    Json::Reader reader;
    Json::Value root;
    if(!reader.parse(ifs,root,false))
    {
        return ;
    }

    Wxlogger* logger = Wxlogger::getInstance();

    string name;
    int age;
    int size = root.size();
    for(int i = 0;i< size;i++)
    {
        name = root[i]["name"].asString();
        age = root[i]["age"].asInt();

        WXLOG_INFO(logger,"name : " << name << "\t" << "age : " << age);
    }

    return;
}

void json_write_test()
{
    Json::Value root;
    Json::FastWriter writer;
    Json::Value person;

    person["name"] = "hello world";
    person["age"] = 100;
    root.append(person);
    root.append(person);

    string json_file = writer.write(root);

    ofstream ofs;
    ofs.open("data/testjsonwrite.json");
    assert(ofs.is_open());
    ofs<< json_file;

    return ;
}

//void jsonarray2_test()
//{
//    Json::value::Members member;
//    for(Json::Value::iterator itr = objArray.begin();itr != obArray.end();itr++)
//    {
//        member = (*itr).getMemberNames();
//        for(Json::Value::Members::iterator iter = member.begin();iter != member.end();iter++)

//            string str_temp = (*itr)[(*iter)].asString();
//    }
//}

void jsontest()
{
    json_test();
    json_write_test();
    json_array_test();
}

#endif // JSON_TEST_HPP
