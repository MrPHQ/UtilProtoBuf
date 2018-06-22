// Demo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include <UtilProtoBuf\include\UtilProtoBuf.h>
#include <UtilProtoBuf\include\ProtoFileMgr.h>
#include <UtilProtoBuf\include\ProtoBuf.h>

#pragma comment(lib, "UtilProtoBuf/lib/UtilProtoBuf.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	std::cin.ignore();
	BYTE buff[1024];
	int iDataLen = 0;

	UTIL_PROTOBUF::CProtoFileMgr::Create();
	UTIL_PROTOBUF::CProtoFileMgr::getSingletonPtr()->SetMapPath("./");
	UTIL_PROTOBUF::CProtoFileMgr::getSingletonPtr()->SetMapPath("E:/GitRep/UtilProtoBuf/vs/bin");
	UTIL_PROTOBUF::CProtoFileMgr::getSingletonPtr()->ImportFile("demo.proto");

	{
		UTIL_PROTOBUF::CProtoMessage msg("Pair");

		msg.SetUInt32("id", 123);
		UTIL_PROTOBUF::CProtoMessage* p = msg.GetNestedMsg("p1");
		p->SetUInt32("value", 123123);
		p->SetString("key", "mykeyxx ddx");
		delete p;
		p = nullptr;
		p = msg.GetNestedMsg("p2");
		p->SetInt32("value", 123123123);
		p->SetString("key", "p2xxxxxxxx");
		p->SetBool("bv", false);
		delete p;

		int len = msg.SerializeToArray(buff, 1024, nullptr);
		iDataLen = len;
		std::cout << "序列化后的数据大小:" << len << std::endl;
	}
	std::cin.ignore();
	{
		UTIL_PROTOBUF::CProtoMessage msg("Pair");
		msg.Parse(buff, iDataLen);
		std::cout << msg.GetUInt32("id") << std::endl;

		UTIL_PROTOBUF::CProtoMessage* p = msg.GetNestedMsg("p1");
		std::cout << p->GetString("key") << std::endl;
		std::cout << p->GetUInt32("value") << std::endl;
		delete p;
		p = msg.GetNestedMsg("p2");
		std::cout << p->GetString("key") << std::endl;
		std::cout << p->GetInt32("value") << std::endl;
		std::cout << p->GetBool("bv") << std::endl;
		delete p;
	}
	std::cin.ignore();
	return 0;
}

