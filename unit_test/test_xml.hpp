#ifndef TEST_XML_HPP
#define TEST_XML_HPP

#include "xml/tinyxml2.h"
#include <iostream>
#include "common/common.h"

using namespace tinyxml2;
using namespace std;

void test_xml1()
{
    tinyxml2::XMLDocument doc;
    doc.LoadFile("./data/test.xml");
    const char* content = doc.FirstChildElement("Hello")->GetText();

    cout << "Hello " << content << endl;
}


void test_xml2()
{
    tinyxml2::XMLDocument doc;
    doc.LoadFile("../Cplusplus_PlatForm/data/test.xml");
    XMLElement *scene = doc.RootElement();
    XMLElement *surface = scene->FirstChildElement("node");

    while(surface)
    {
        XMLElement* surfaceChild = surface->FirstChildElement();
        const char* content;
        const XMLAttribute* attributeOfSurface = surface->FirstAttribute();
        cout << attributeOfSurface->Name() << " : " << attributeOfSurface->Value() << endl;

        while(surfaceChild)
        {
            content = surfaceChild->GetText();
            surfaceChild = surfaceChild->NextSiblingElement();
            cout << content << endl;
        }
        surface = surface->NextSiblingElement();
    }
}

//创建XML文件
void createXML(const char* xmlPath)
{
    const char* declaration = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>";
    tinyxml2::XMLDocument doc;
    doc.Parse(declaration);  // 会覆盖xml所有内容

     //添加申明可以使用如下两行
//    XMLDeclaration* declaration = doc.NewDeclaration();
//    doc.InsertFirstChild(declaration);

    XMLElement* root = doc.NewElement("DBUSER");
    doc.InsertEndChild(root);

    doc.SaveFile(xmlPath);
}

class User
{
public:
    User()
    {
        gender = 0;
    }

    User(const string& userName, const string& password, int gender, const string& mobile, const string& email)
    {
        this->userName = userName;
        this->password = password;
        this->gender = gender;
        this->mobile = mobile;
        this->email = email;
    }

    string userName;
    string password;
    int gender;
    string mobile;
    string email;
};



//增加xml文件的节点
//function:insert XML node
//param:xmlPath:xml文件路径; user:用户对象
//return:0:成功; 非0:失败
int insertXMLNode(const char* xmlPath,const User& user)
{
    tinyxml2::XMLDocument doc;
    int res = doc.LoadFile(xmlPath);
    if(res != 0)
    {
        cout << "load xml file filed " << endl;
        return res;
    }

    XMLElement* root = doc.RootElement();
    XMLElement* userNode = doc.NewElement("User");
    userNode->SetAttribute("Name",user.userName.c_str());
    userNode->SetAttribute("password",user.password.c_str());
    root->InsertEndChild(userNode);

    XMLElement* gender = doc.NewElement("Gender");
    XMLText* genderText = doc.NewText(int2string(user.gender).c_str());
    gender->InsertEndChild(genderText);
    userNode->InsertEndChild(gender);

    XMLElement* mobile = doc.NewElement("Mobile");
    mobile->InsertEndChild(doc.NewText(user.mobile.c_str()));
    userNode->InsertEndChild(mobile);

    XMLElement* email = doc.NewElement("Email");
    email->InsertEndChild(doc.NewText(user.email.c_str()));
    userNode->InsertEndChild(email);

    doc.SaveFile(xmlPath);
}

//查询xml文件的指定节点

//function:根据用户名获取用户节点
//param:root:xml文件根节点；userName：用户名
//return：用户节点
XMLElement* queryUserNodeByName(XMLElement* root,const string& userName)
{
    XMLElement* userNode = root->FirstChildElement("User");
    while(userNode != NULL)
    {
        if(userNode->Attribute("Name") == userName)
        {
            break;
        }
        userNode = userNode->NextSibilingElement();  // 下一个兄弟节点
    }
    return userNode;
}

User* queryUserByName(const char* xmlPath,const string& userName)
{
    XMLDocument doc;
    if(doc.LoadFile(xmlPath) != 0)
    {
        cout << "load xml file failed " << endl;
        return NULL;
    }

    XMLElement* root=doc.RootElement();
    XMLElement* userNode = queryUserNodeByName(root,userName);

    if(userNode != NULL) // searched successfully
    {
        User* user = new User();
        user->userName = userName;
        user->password = userNode->Attribute("Password");
        XMLElement* genderNode = userNode->FirstChildElement("Gender");
        user->gender = atoi(genderNode->GetText());
        XMLElement& mobileNode = userNode->FirstChildElement("Mobile");
        user->mobile = mobileNode.GetText();
        XMLElement* emailNode = userNode->FirstChildElement("Email");
        user->email = emailNode->GetText();
        return user;
    }
    return NULL;
}

// 修改xml文件的指定节点
//function:修改指定节点内容
//param:xmlPath:xml文件路径；user：用户对象
//return：bool
bool updateUser(const char* xmlPath,User* user)
{
    XMLDocument doc;
    if(doc.LoadFile(xmlPath) != 0)
    {
        cout <<"load xml file failed " <<endl;
        return false;
    }

    XMLElement* root = doc.RootElement();
    XMLElement* userNode = queryUserNodeByName(root,user->userName);

    if(userName != NULL)
    {

    }
}


void test_xml()
{
    test_xml1();
    test_xml2();

    createXML("../Cplusplus_PlatForm/data/test2.xml");

    User user("wuwenxue","123456",2,"123456789","123@123.com");

    insertXMLNode("../Cplusplus_PlatForm/data/test2.xml",user);
}

#endif // TEST_XML_HPP
