#ifndef __UTIL_PROTOBUF_FILE_MGR__
#define __UTIL_PROTOBUF_FILE_MGR__

#include <UtilProtoBuf\include\UtilProtoBuf.h>

namespace UTIL_PROTOBUF
{

	/**
	@brief proto�ļ�����.
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
		@brief ����proto�ļ�����Ŀ¼.
		\param pLookupFolder
			�ڵ�ǰĿ¼�в���.proto�ļ�,�ļ����� '\'�� '/'��β.
			������һ������·��������ڵ�ǰĿ¼
		*/
		void SetMapPath(const char* pLookupFolder);
		/**
		@brief ����proto�ļ�.
			PROTO�ļ�.ʹ�����·��.

		e.g
			pLookupFolder = 'e:/proto/'
			pProtoFile = 'msg.proto'
			�����ȳ��Դ�'e:/proto/msg.proto'
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