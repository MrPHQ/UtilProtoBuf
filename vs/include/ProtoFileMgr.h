#ifndef __UTIL_PROTOBUF_FILE_MGR__
#define __UTIL_PROTOBUF_FILE_MGR__

#include <UtilProtoBuf\include\UtilProtoBuf.h>

namespace UTIL_PROTOBUF
{

	/**
	@brief proto文件管理.
	*/

	class UTIL_PROTOBUF_CPPAPI CProtoFileMgr :
		public UTILS::SingleTon<CProtoFileMgr>
	{
	private:
		CProtoFileMgr();
		~CProtoFileMgr();
	public:
		static CProtoFileMgr* getSingletonPtr(void);
		static CProtoFileMgr& Create();
		static void Destroy();
	public:

		/**
		@brief 设置proto文件查找目录.
		\param pLookupFolder
			在当前目录中查找.proto文件,文件夹以 '\'或 '/'结尾.
			可以是一个绝对路径或相对于当前目录
		*/
		void SetMapPath(const char* pLookupFolder);
		/**
		@brief 导入proto文件.
			PROTO文件.使用相对路径.

		e.g
			pLookupFolder = 'e:/proto/'
			pProtoFile = 'msg.proto'
			将首先尝试打开'e:/proto/msg.proto'
		*/
		int ImportFile(const char* pProtoFile);

		/**
		@brief .
		*/
		const DescriptorPool* GetDescriptorPool() const { 
			if (m_Importer != nullptr){
				return m_Importer->pool();
			}
			return nullptr;
		}
		/**
		@brief .
		*/
		DynamicMessageFactory* GetDynamicMessageFactory() const {
			return m_pMsgFactory;
		}
	private:

		/**< .*/
		Importer* m_Importer;
		DiskSourceTree* m_DiskSourceTree;
		DynamicMessageFactory* m_pMsgFactory;
	};
}
#endif