#ifndef __UTIL_PROTOBUF_DEF__
#define __UTIL_PROTOBUF_DEF__


namespace UTIL_PROTOBUF
{
	/*
	@brief ������
	*/
	enum
	{
		/**< û�д���.*/
		UTIL_PROTOBUF_ERROR_SUCCESS = 0,
		/**< ��������.*/
		UTIL_PROTOBUF_ERROR_PAR = -1,
		/**< �����ڴ�ʧ��.*/
		UTIL_PROTOBUF_ERROR_MEMORY = -2,
		/**< �쳣.*/
		UTIL_PROTOBUF_ERROR_ABNORMAL = -3,
		/**< δ�ҵ�,Ŀ¼/�ļ�/.*/
		UTIL_PROTOBUF_ERROR_FIND = -4,
		/**< ����ʧ��.*/
		UTIL_PROTOBUF_ERROR_FAIL = -5,
		/**< ��ʱ.*/
		UTIL_PROTOBUF_ERROR_TIMEOUT = -6,
		/**< ��֧��.*/
		UTIL_PROTOBUF_ERROR_NOSUPPOERT = -7,
		/**< ������.*/
		UTIL_PROTOBUF_ERROR_EXISTS = -8,
		/**< ������̫С.*/
		UTIL_PROTOBUF_ERROR_BUFFER_SMALL = -9,
		/**< �����������ʧ��.*/
		UTIL_PROTOBUF_ERROR_DLL = -10,
		/**< û���ҵ���Ϣ��������.*/
		UTIL_PROTOBUF_ERROR_NOT_FIND_MSG = -11,
	};
}

#endif