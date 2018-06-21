#include "../UtilProtoBuf/stdafx.h"
#include "../include/ProtoFileMgr.h"

template<> UTIL_PROTOBUF::CProtoFileMgr* UTILS::SingleTon<UTIL_PROTOBUF::CProtoFileMgr>::ms_Singleton = nullptr;

std::atomic_flag glock = ATOMIC_FLAG_INIT;
/**
* @brief 初始化启动进程使用Winsock DLL。
*	原子操作.
*/
void _InitProtoFileMgr(){
	if (!glock.test_and_set()){
		UTIL_PROTOBUF::CProtoFileMgr::Create();
	}
}

namespace UTIL_PROTOBUF
{
	CProtoFileMgr::CProtoFileMgr():
		m_Importer(nullptr),
		m_DiskSourceTree(nullptr),
		m_pMsgFactory(nullptr)
	{
		m_DiskSourceTree = new DiskSourceTree();
		m_Importer = new Importer(m_DiskSourceTree, nullptr);
		m_pMsgFactory = new DynamicMessageFactory();
	}

	CProtoFileMgr::~CProtoFileMgr()
	{
		if (m_Importer != nullptr){
			delete m_Importer;
		}
		if (m_DiskSourceTree != nullptr){
			delete m_DiskSourceTree;
		}
		if (m_pMsgFactory != nullptr){
			delete m_pMsgFactory;
		}
	}

	CProtoFileMgr* CProtoFileMgr::getSingletonPtr(void)
	{
		CProtoFileMgr* p = UTILS::SingleTon<CProtoFileMgr>::getSingletonPtr();
		if (p == nullptr){
			_InitProtoFileMgr();
			p = UTILS::SingleTon<CProtoFileMgr>::getSingletonPtr();
		}
		return p;
	}

	CProtoFileMgr& CProtoFileMgr::Create()
	{
		return *(new CProtoFileMgr());
	}

	void CProtoFileMgr::Destroy()
	{
		if (CProtoFileMgr::getSingletonPtr() == NULL)
		{
			return;
		}
		delete CProtoFileMgr::getSingletonPtr();
	}

	void CProtoFileMgr::SetMapPath(const char* pLookupFolder)
	{
		if (nullptr == pLookupFolder || strlen(pLookupFolder) <= 0){
			return;
		}
		if (nullptr == m_DiskSourceTree){
			return;
		}
		m_DiskSourceTree->MapPath("", pLookupFolder);
	}

	int CProtoFileMgr::ImportFile(const char* pProtoFile)
	{
		if (nullptr == pProtoFile || strlen(pProtoFile) <= 0){
			return UTIL_PROTOBUF_ERROR_PAR;
		}
		if (nullptr == m_Importer){
			return UTIL_PROTOBUF_ERROR_PAR;
		}
		if (m_Importer->Import(pProtoFile) != nullptr){
			return UTIL_PROTOBUF_ERROR_SUCCESS;
		}
		return UTIL_PROTOBUF_ERROR_FAIL;
	}
}