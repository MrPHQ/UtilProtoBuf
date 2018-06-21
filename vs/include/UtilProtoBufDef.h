#ifndef __UTIL_PROTOBUF_DEF__
#define __UTIL_PROTOBUF_DEF__


namespace UTIL_PROTOBUF
{
	/*
	@brief 错误码
	*/
	enum
	{
		/**< 没有错误.*/
		UTIL_PROTOBUF_ERROR_SUCCESS = 0,
		/**< 参数错误.*/
		UTIL_PROTOBUF_ERROR_PAR = -1,
		/**< 分配内存失败.*/
		UTIL_PROTOBUF_ERROR_MEMORY = -2,
		/**< 异常.*/
		UTIL_PROTOBUF_ERROR_ABNORMAL = -3,
		/**< 未找到,目录/文件/.*/
		UTIL_PROTOBUF_ERROR_FIND = -4,
		/**< 操作失败.*/
		UTIL_PROTOBUF_ERROR_FAIL = -5,
		/**< 超时.*/
		UTIL_PROTOBUF_ERROR_TIMEOUT = -6,
		/**< 不支持.*/
		UTIL_PROTOBUF_ERROR_NOSUPPOERT = -7,
		/**< 不存在.*/
		UTIL_PROTOBUF_ERROR_EXISTS = -8,
		/**< 缓存区太小.*/
		UTIL_PROTOBUF_ERROR_BUFFER_SMALL = -9,
		/**< 第三方库加载失败.*/
		UTIL_PROTOBUF_ERROR_DLL = -10,
		/**< 没有找到消息类型名称.*/
		UTIL_PROTOBUF_ERROR_NOT_FIND_MSG = -11,
	};
}

#endif